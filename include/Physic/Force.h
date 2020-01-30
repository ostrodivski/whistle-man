#ifndef FORCE_H
#define FORCE_H

#include <SFML/Graphics.hpp>

class Force
{
	public :
		virtual sf::Vector2f calcForce(sf::Vector2f position, sf::Vector2f velocity) = 0 ;
} ;

#endif
