#ifndef FRICTION_H
#define FRICTION_H

#include <SFML/Graphics.hpp>

#include <Physic/Force.h>

class Friction : public Force
{
	private :
		float m_friction ;
	public :
		Friction(float friction) ;

		virtual sf::Vector2f calcForce(sf::Vector2f position, sf::Vector2f velocity) ;
} ;

#endif
