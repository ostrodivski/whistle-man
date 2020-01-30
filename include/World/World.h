#ifndef WORLD_H
#define WORLD_H

#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include <Entity/Entity.h>
#include <Camera/Camera.h>

using namespace std ;

class World : public sf::Drawable
{
	private :	
		static std::string m_LoadersPath ;
		sf::Vector2f m_size ;

		vector<Entity*> m_instances ;
		Entity* m_mainInstance ;
		Camera m_camera ;
	
		float m_velocityMax ;
		void calcVelocity(Entity* instance, sf::Time elapsed) ;
		void calcPosition(Entity* instance, sf::Time elapsed) ;

		unsigned int** m_collisions ;
		bool collisionCheck(Entity* instance, unsigned int id) ;


	public :
		World(float velocityMax = 30) ;
		~World();

		void load(string filename) ;
		void handleEvent(float input) ;
		void update(sf::Time elapsed) ;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const ;
};

#endif
