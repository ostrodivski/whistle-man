#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include <Entity/Wall.h>
#include <poly2tri.h>

using namespace std ;

Wall::Wall(sf::Vector2f position, sf::Vector2f defaultVelocity, std::vector<sf::Vector2f> bounds) :
	Entity(position, defaultVelocity, sf::Vector2f(0, 0), INFINITY, 3)
{
	m_thickness = 10 ;
	m_texture.loadFromFile(m_texturesPath + "wall.png") ;
	m_borderTexture.loadFromFile(m_texturesPath + "border.png") ;
	m_texture.setRepeated(true) ;
	m_borderTexture.setRepeated(true) ;

	triangulate(bounds) ;
	addBorders(bounds) ;
	calcDimensions(bounds) ;
	calcBarycentre(bounds) ;
	
	for(unsigned int i=0 ; i < bounds.size() ; i++)
	{
		m_bounds.push_back(new Segment(bounds[i], bounds[(i+1) % bounds.size()])) ;
	}
}

Wall::Wall(sf::Vector2f position, sf::Vector2f size) :
	Wall(position, sf::Vector2f(0, 0), {sf::Vector2f(0, 0), sf::Vector2f(size.x, 0), size, sf::Vector2f(0, size.y)}) {}

Wall::~Wall()
{
	delete(m_borders) ;
	delete(m_triangulation) ;
	for(unsigned int i=0 ; i < m_bounds.size() ; i++)
	{
		delete(m_bounds[i]) ;
	}
}

void Wall::calcDimensions(vector<sf::Vector2f> bounds)
{
	sf::Vector2f dimensions ;
	
	for(unsigned int i=0 ; i < bounds.size() ; i++)
	{
		if(bounds[i].x > dimensions.x) {dimensions.x = bounds[i].x ;}
		if(bounds[i].y > dimensions.y) {dimensions.y = bounds[i].y ;}
	}
	
	m_dimensions = dimensions ;
}

void Wall::calcBarycentre(vector<sf::Vector2f> bounds)
{
	sf::Vector2f barycentre ;
	for(unsigned int i=0 ; i < bounds.size() ; i++)
	{
		barycentre += bounds[i] ;
	}
	
	barycentre /= (float)bounds.size() ;
	setOrigin(barycentre) ;
	setPosition(getPosition() + getOrigin()) ;
}

void Wall::triangulate(vector<sf::Vector2f> bounds)
{
        std::vector<p2t::Point*> polyline ;
        std::vector<p2t::Triangle*> triangles ;

        for(unsigned int i=0 ; i < bounds.size() ; i++)
        {
                polyline.push_back(new p2t::Point()) ;
                polyline[i] -> x = bounds[i].x ;
                polyline[i] -> y = bounds[i].y ;
        }

        p2t::CDT cdt(polyline) ;
        cdt.Triangulate() ;
        triangles = cdt.GetTriangles() ;

        m_nbTriangles = triangles.size() ;
        m_triangulation = (sf::Vertex*)malloc(3 * m_nbTriangles * sizeof(sf::Vertex)) ;
 
       for(unsigned int i=0 ; i < m_nbTriangles ; i++)
        {
                m_triangulation[3 * i].position.x = (triangles[i] -> GetPoint(0)) -> x ; 
                m_triangulation[3 * i + 1].position.x = (triangles[i] -> GetPoint(1)) -> x ;
                m_triangulation[3 * i + 2].position.x = (triangles[i] -> GetPoint(2)) -> x ;

                m_triangulation[3 * i].position.y = (triangles[i] -> GetPoint(0)) -> y ; 
                m_triangulation[3 * i + 1].position.y = (triangles[i] -> GetPoint(1)) -> y ;
                m_triangulation[3 * i + 2].position.y = (triangles[i] -> GetPoint(2)) -> y ;

                m_triangulation[3 * i].color = sf::Color(255, 255, 255, 255) ;
                m_triangulation[3 * i + 1].color = sf::Color(255, 255, 255, 255) ;
                m_triangulation[3 * i + 2].color = sf::Color(255, 255, 255, 255) ;
				
				m_triangulation[3 * i].texCoords = m_triangulation[3 * i].position ;
                m_triangulation[3 * i + 1].texCoords = m_triangulation[3 * i + 1].position ;
                m_triangulation[3 * i + 2].texCoords = m_triangulation[3 * i + 2].position ;
        }

        for(unsigned int i=0 ; i < bounds.size() ; i++)
        {
                delete(polyline[i]) ;
        }
}

void Wall::addBorders(vector<sf::Vector2f> bounds)
{
		m_borders = (sf::Vertex*)malloc(bounds.size() * 4 * sizeof(sf::Vertex)) ;

        float xA, xB, yA, yB ;
        float dx, dy ;
        float norm ;
        for(unsigned int i=0 ; i < bounds.size() ; i++)
        {
                xA = bounds[i].x ;
                xB = bounds[(i + 1) % bounds.size()].x ;
                yA = bounds[i].y ;
                yB = bounds[(i + 1) % bounds.size()].y ;
                dx = xB - xA ;
                dy = yB - yA ;
                norm = sqrt(dx * dx + dy * dy) ;

                m_borders[4 * i].position.x = bounds[i].x ;
				m_borders[4 * i].position.y = bounds[i].y ;
                m_borders[4 * i + 1].position.x = bounds[(i + 1) % bounds.size()].x ;
				m_borders[4 * i + 1].position.y = bounds[(i + 1) % bounds.size()].y ;

                m_borders[4 * i + 3].position.x = xA - m_thickness * dy / norm ;
                m_borders[4 * i + 3].position.y = yA + m_thickness * dx / norm ;
                m_borders[4 * i + 2].position.x = m_borders[4 * i + 3].position.x + dx ;
                m_borders[4 * i + 2].position.y = m_borders[4 * i + 3].position.y + dy ;

                m_borders[4 * i].texCoords = sf::Vector2f(0, 0) ;
                m_borders[4 * i + 1].texCoords = sf::Vector2f(1, 0) ;
                m_borders[4 * i + 2].texCoords = sf::Vector2f(1, m_thickness) ;
                m_borders[4 * i + 3].texCoords = sf::Vector2f(0, m_thickness) ;

                m_borders[4 * i].color = sf::Color(255, 255, 255, 255) ;
                m_borders[4 * i + 1].color = sf::Color(255, 255, 255, 255) ;
                m_borders[4 * i + 2].color = sf::Color(255, 255, 255, 255) ;
                m_borders[4 * i + 3].color = sf::Color(255, 255, 255, 255) ;
        }
}

void Wall::onCollision(Entity* entity) {}

void Wall::update(sf::Time elapsed)
{
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_texture ;
	states.transform *= getTransform() ;
	target.draw(m_triangulation, 3 * m_nbTriangles, sf::Triangles, states) ;
	
	states.texture = &m_borderTexture ;
	target.draw(m_borders, 4 * m_bounds.size(), sf::Quads, states) ;
}
