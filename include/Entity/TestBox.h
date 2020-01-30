#ifndef TESTBOX_H
#define TESTBOX_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Entity/Entity.h>

class TestBox : public Entity
{
	public:
		TestBox(sf::Vector2f position, sf::Vector2f defaultVelocity);
		~TestBox() ;

		virtual void onCollision(Entity* entity) ;

		virtual void update(sf::Time elapsed) ;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;
};

#endif
