#ifndef VORTEX_H
#define VORTEX_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include <Entity/Entity.h>
#include <Physic/Attractor.h>

class Vortex : public Entity
{
	private :
		sf::Vertex m_vertex[4] ;
		sf::Texture m_texture ;
		float m_pulsation ;
		
	public :
		Vortex(sf::Vector2f position, sf::Vector2f defaultVelocity = sf::Vector2f(0, 0), float attraction = 1500000, float pulsation = 40) ;

		~Vortex() ;
		
		virtual void onCollision(Entity* entity) ;
		
		virtual void update(sf::Time elapsed) ;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;
} ;

#endif
