#ifndef WHISTLEMAN_H
#define WHISTLEMAN_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include <Entity/Entity.h>

class WhistleMan : public Entity
{
	private :
		sf::Time m_lifeTime ;
		sf::Time m_period ;
		unsigned int m_nbWaves ;
		
		sf::Texture m_texture ;
		sf::Vertex* m_vertex ;
		sf::Time* m_lifeTimes ;
		unsigned int m_wavesCounter ;
		sf::Time m_elapsed ;
		
	public :
		WhistleMan(sf::Vector2f position, sf::Vector2f defaultVelocity = sf::Vector2f(0.01, 0), unsigned int nbWaves = 3, sf::Time lifeTime = sf::milliseconds(500)) ;
		
		~WhistleMan() ;

		void addWave() ;
		void deleteWave() ;

		virtual void onCollision(Entity* entity) ;

		virtual void update(sf::Time elapsed) ;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;
} ;

#endif
