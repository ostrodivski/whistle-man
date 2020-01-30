#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <Entity/WhistleMan.h>
#include <Physic/Force.h>

WhistleMan::WhistleMan(sf::Vector2f position, sf::Vector2f defaultVelocity, unsigned int nbWaves, sf::Time lifeTime) :
	Entity(position, defaultVelocity, sf::Vector2f(20, 20), 30, 1)
{
	setOrigin(m_dimensions / (float)2) ;
	setPosition(getPosition() + getOrigin()) ;
	m_bounds.push_back(new Circle(getOrigin(), 10.)) ;
	
	m_texture.loadFromFile(m_texturesPath + "whistleman.png") ;
	m_nbWaves = nbWaves ;
	m_lifeTime = lifeTime ;
	m_vertex = (sf::Vertex*)malloc(4 * (m_nbWaves + 1) * sizeof(sf::Vertex)) ;
	m_lifeTimes = (sf::Time*)malloc(4 * sizeof(sf::Time)) ;
	m_wavesCounter = 0 ;
	m_period = m_lifeTime / (float)m_nbWaves ;
	
	for(unsigned int i=0 ; i < m_nbWaves + 1 ; i++)
	{
		m_vertex[4 * i].color = sf::Color(255, 255, 255, 255) ;
		m_vertex[4 * i + 1].color = sf::Color(255, 255, 255, 255) ;
		m_vertex[4 * i + 2].color = sf::Color(255, 255, 255, 255) ;
		m_vertex[4 * i + 3].color = sf::Color(255, 255, 255, 255) ;

		m_vertex[4 * i].position = sf::Vector2f(0, 0) ;
		m_vertex[4 * i + 1].position = sf::Vector2f(m_dimensions.x, 0) ;
		m_vertex[4 * i + 2].position = sf::Vector2f(m_dimensions.x, m_dimensions.y) ;
		m_vertex[4 * i + 3].position = sf::Vector2f(0, m_dimensions.y) ;

		m_vertex[4 * i].texCoords = sf::Vector2f(0, 0) ;
		m_vertex[4 * i + 1].texCoords = sf::Vector2f(m_dimensions.x, 0) ;
		m_vertex[4 * i + 2].texCoords = sf::Vector2f(m_dimensions.x, m_dimensions.y) ;
		m_vertex[4 * i + 3].texCoords = sf::Vector2f(0, m_dimensions.y) ;
	}
}

WhistleMan::~WhistleMan()
{
	free(m_vertex) ;
	free(m_lifeTimes) ;
	delete(m_bounds[0]) ;
}

void WhistleMan::onCollision(Entity* entity) {  ;}

void WhistleMan::addWave()
{
	m_wavesCounter++ ;
	for(unsigned int i=0 ; i < 4 ; i++)
	{
		m_vertex[4 * m_wavesCounter + i].position = m_vertex[i].position ;
		m_vertex[4 * m_wavesCounter + i].color.a = 255;
	}
	m_lifeTimes[m_wavesCounter] = m_lifeTime ;
}

void WhistleMan::deleteWave()
{
	for(unsigned int i=1 ; i < m_wavesCounter ; i++)
	{
		for(unsigned int j=0 ; j < 4 ; j++)
		{
			m_vertex[4 * i + j].position = m_vertex[4 * (i+1) + j].position ;
			m_vertex[4 * i + j].color = m_vertex[4 * (i+1) + j].color ;
		}
		m_lifeTimes[i] = m_lifeTimes[i+1] ;
	}

	m_wavesCounter-- ;
}

void WhistleMan::update(sf::Time elapsed)
{
	setPosition(getPosition() + m_velocity + m_defaultVelocity) ;
	m_elapsed += elapsed ;
	
	if(m_wavesCounter >= 1 && m_lifeTimes[1] <= sf::Time::Zero) { deleteWave() ;}

	for(unsigned int i=1 ; i <= m_wavesCounter ; i++)
	{
		m_lifeTimes[i] -= elapsed ;

		for(unsigned int j=0 ; j < 4 ; j++)
		{
			m_vertex[4 * i + j].position -= m_velocity + m_defaultVelocity ;
			m_vertex[4 * i + j].color.a = fmax(0, (m_lifeTimes[i].asSeconds() / m_lifeTime.asSeconds()) * 255);
		}
	}

	if(m_elapsed >= m_period && m_wavesCounter < m_nbWaves)
	{
		m_elapsed = sf::Time::Zero ;
		addWave() ;
	}
}

void WhistleMan::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_texture ;
	states.transform *= getTransform() ;
	target.draw(m_vertex, 4 * (m_wavesCounter + 1), sf::Quads, states) ;
}
