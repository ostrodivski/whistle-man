#include <Physic/Friction.h>

Friction::Friction(float friction) : m_friction(friction) {}

sf::Vector2f Friction::calcForce(sf::Vector2f position, sf::Vector2f velocity)
{
	return(- m_friction * velocity) ;
}
