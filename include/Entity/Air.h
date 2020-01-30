#ifndef AIR_H
#define AIR_H

#include <Physic/Friction.h>
#include <Entity/Entity.h>

class Air : public Entity
{
	public:
		Air(sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f defaultVelocity = sf::Vector2f(0, 0), float friction = 35) ;
		
		~Air() ;
		
		virtual void onCollision(Entity* entity) ;
		
		virtual void update(sf::Time elapsed) ;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;
} ;

#endif
