#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include <Entity/Vortex.h>
#include <Physic/Force.h>
#include <Physic/Attractor.h>

Vortex::Vortex(sf::Vector2f position, sf::Vector2f defaultVelocity, float attraction, float pulsation) :
	Entity(position, defaultVelocity, sf::Vector2f(80, 80), 100000000, 2) 
{
	m_texture.loadFromFile(m_texturesPath + "vortex.png") ;

	setOrigin(m_dimensions / (float)2) ;
	setPosition(getPosition() + getOrigin()) ;
	m_bounds.push_back(new Point(getOrigin())) ;
	
	m_vertex[0].position = sf::Vector2f(0, 0) ;
	m_vertex[1].position = sf::Vector2f(m_dimensions.x, 0) ;
	m_vertex[2].position = sf::Vector2f(m_dimensions.x, m_dimensions.y) ;
	m_vertex[3].position = sf::Vector2f(0, m_dimensions.y) ;
	m_vertex[0].texCoords = sf::Vector2f(0, 0) ;
	m_vertex[1].texCoords = sf::Vector2f(m_dimensions.x, 0) ;
	m_vertex[2].texCoords = sf::Vector2f(m_dimensions.x, m_dimensions.y) ;
	m_vertex[3].texCoords = sf::Vector2f(0, m_dimensions.y) ; ;
	
	m_pulsation = pulsation ;

	m_forces.push_back(new Attractor(attraction)) ;
}

Vortex::~Vortex()
{
	delete(m_forces[0]) ;
	delete(m_bounds[0]) ;
}

void Vortex::onCollision(Entity* entity)
{
	delete(entity) ;
}

void Vortex::update(sf::Time elapsed)
{
	rotate(m_pulsation * elapsed.asSeconds()) ;
}

void Vortex::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_texture ;
	states.transform *= getTransform() ;
	target.draw(m_vertex, 4, sf::Quads, states) ;
}

