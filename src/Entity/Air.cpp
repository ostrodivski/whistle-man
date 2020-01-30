#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include <Physic/Friction.h>
#include <Entity/Air.h>

Air::Air(sf::Vector2f position, sf::Vector2f defaultVelocity, float friction) :
	Entity(position, defaultVelocity, sf::Vector2f(0, 0), 0, 0)
{
	m_forces.push_back(new Friction(friction)) ;
}

Air::~Air()
{
	delete(m_forces[0]) ;
}

void Air::onCollision(Entity* entity) {}

void Air::update(sf::Time elapsed) {}

void Air::draw(sf::RenderTarget& target, sf::RenderStates states) const {}
