#ifndef ATTRACTOR_H
#define ATTRACTOR_H

#include <Physic/Force.h>

class Attractor : public Force
{
	private :
		float m_attraction ;
	public :
		Attractor(float attraction) ;
		virtual sf::Vector2f calcForce(sf::Vector2f position, sf::Vector2f velocity) ;
} ;

#endif
