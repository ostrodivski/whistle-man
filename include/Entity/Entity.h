#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include <Physic/Force.h>
#include <Physic/Bound.h>

using namespace std ;

class Entity : public sf::Drawable, public sf::Transformable
{
	protected :
		static std::string m_texturesPath ;

		sf::Vector2f m_dimensions ;
		sf::Vector2f m_velocity ;
		sf::Vector2f m_defaultVelocity ;
		float m_mass ;
		unsigned int m_id ;

		vector<Bound*> m_bounds ;
		vector<Force*> m_forces ;

	public :
		Entity(sf::Vector2f position, sf::Vector2f defaultVelocity, sf::Vector2f dimensions, float mass, unsigned int id) ;
		~Entity() ;
		
		sf::Vector2f getVelocity() ;
		sf::Vector2f getDefaultVelocity() ;
		sf::Vector2f getEffectiveVelocity() ;
		float getMass() ;
		sf::Vector2f getDimensions() ;
		unsigned int getId() ;

		vector<Bound*> getGlobalBounds() ;

		void setVelocity(sf::Vector2f velocity) ;

		sf::Vector2f getResultantForce(Entity* entity) ;
		
		virtual void onCollision(Entity* entity) = 0 ;

		virtual void update(sf::Time elapsed) = 0 ;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0 ;
} ;

#endif
