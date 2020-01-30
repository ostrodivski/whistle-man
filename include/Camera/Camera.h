#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

#include <Entity/Entity.h>

class Camera : public sf::View
{
	private :
		Entity* m_actor ;
		sf::Vector2f m_defaultPosition ;

	public :
		Camera() ;

		void attach(Entity* actor) ;
		void update() ;
};

#endif
