#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include <Physic/Force.h>
#include <Entity/Entity.h>

using namespace std ;

string Entity::m_texturesPath = "textures/" ;

Entity::Entity(sf::Vector2f position,
	sf::Vector2f defaultVelocity,
	sf::Vector2f dimensions,
	float mass,
	unsigned int id) :
	m_velocity(sf::Vector2f(0, 0)), m_defaultVelocity(defaultVelocity), m_dimensions(dimensions), m_mass(mass), m_id(id)
{
	setPosition(position) ;
}

Entity::~Entity()
{
}		

sf::Vector2f Entity::getVelocity()
{
	return m_velocity ;
}

sf::Vector2f Entity::getDefaultVelocity()
{
	return m_defaultVelocity ;
}

sf::Vector2f Entity::getEffectiveVelocity()
{
	return m_velocity + m_defaultVelocity ;
}

vector<Bound*> Entity::getGlobalBounds()
{
	for(unsigned int i=0 ; i < m_bounds.size() ; i++)
	{
		m_bounds[i] -> transform(getOrigin(), getPosition(), getRotation(), getScale()) ;
	}
	return m_bounds ;
}

float Entity::getMass()
{
	return m_mass ;
}

unsigned int Entity::getId()
{
	return m_id ;
}

sf::Vector2f Entity::getDimensions()
{
	return m_dimensions ;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity ;
}

sf::Vector2f Entity::getResultantForce(Entity* entity)
{
	for(unsigned int i=0 ; i < m_forces.size() ; i++)
	{
		return(m_forces[i] -> calcForce(entity -> getPosition() - getPosition(), entity -> getEffectiveVelocity() - getEffectiveVelocity())) ;
	}

	return(sf::Vector2f(0, 0)) ;
}
