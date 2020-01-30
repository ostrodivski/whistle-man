#ifndef WALL_H
#define WALL_H

#include <stdlib.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Entity/Entity.h>

using namespace std ;

class Wall : public Entity
{
	protected :
		sf::Texture m_texture ;
		sf::Vertex* m_triangulation ;
		unsigned int m_nbTriangles ;
		
		sf::Texture m_borderTexture ;
		sf::Vertex* m_borders ;
		float m_thickness ;

		void triangulate(vector<sf::Vector2f> bounds) ;
		void addBorders(vector<sf::Vector2f> bounds) ;
		void calcDimensions(vector<sf::Vector2f> bounds) ;
		void calcBarycentre(vector<sf::Vector2f> bounds) ;

	public:
		Wall(sf::Vector2f position, sf::Vector2f defaultVelocity, vector<sf::Vector2f> bounds) ;
		Wall(sf::Vector2f position, sf::Vector2f size) ;
		
		~Wall();

		virtual void onCollision(Entity* entity) ;

		virtual void update(sf::Time elapsed) ;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;
};

#endif
