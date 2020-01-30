#include <SFML/Graphics.hpp>
#include <math.h>

#include <Physic/Attractor.h>

#define PI 3.14178

Attractor::Attractor(float attraction) : m_attraction(attraction) {}

sf::Vector2f Attractor::calcForce(sf::Vector2f position, sf::Vector2f velocity)
{
	float th ;

	if(position.x >= 0) {
		th = atan((position.y)/(position.x)) ;
	}
	else if(position.x <= 0)
	{
		th = PI + atan((position.y)/(position.x)) ;
	}
	else
	{
		th = 0 ;
	}

	if(position.x == 0 && position.y == 0)
	{
		return(sf::Vector2f(0, 0)) ;
	} else {
		float ForceNorm = - m_attraction / (position.x * position.x + position.y * position.y) ;
		return(sf::Vector2f(ForceNorm * cos(th), ForceNorm * sin(th))) ;
	}
}
