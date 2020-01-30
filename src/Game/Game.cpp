#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Game/Game.h>
#include <Management/InputManager.h>
#include <World/World.h>
#include <Entity/Entity.h>

#define HEIGHT 768
#define WIDTH 1024

Game::Game()
{
	m_window.create(sf::VideoMode(WIDTH, HEIGHT), "WhistleMan") ;
	m_window.setVerticalSyncEnabled(true) ;
	m_inputManager.launch() ;
	m_timeStamp = sf::Time::Zero ;
}

Game::~Game()
{
	m_inputManager.stop() ;
}

void Game::run()
{
	while(m_window.isOpen())
	{
		handleEvent() ;
		update() ;
		render() ;
	}
}

void Game::handleEvent()
{

	sf::Event event ;
	while(m_window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		{
			m_window.close() ;
		}
	}

	float input ;
	if(m_inputManager.pollInput(&input))
	{
		m_world.handleEvent(input) ;
	}
}

void Game::update()
{
	sf::Time time = m_clock.getElapsedTime() ;
	sf::Time elapsed = time - m_timeStamp ;
	m_timeStamp = time ;
	m_world.update(elapsed) ;
}

void Game::render()
{
	m_window.clear() ;
	m_window.draw(m_world) ;
	m_window.display() ;
}
