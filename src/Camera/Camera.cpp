#include <SFML/Graphics.hpp>

#include <Camera/Camera.h>
#include <Entity/Entity.h>

#define WIDTH 1024
#define HEIGHT 768

Camera::Camera()
{
	setSize(WIDTH, HEIGHT) ;
	m_defaultPosition = sf::Vector2f(WIDTH/3, 0) ;
}

void Camera::attach(Entity* actor)
{
	m_actor = actor ;
	setCenter(m_actor -> getPosition() + m_defaultPosition) ;
}

void Camera::update()
{
	move(m_actor -> getPosition() + m_defaultPosition - getCenter()) ;
}
