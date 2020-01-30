#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <Management/InputManager.h>
#include <World/World.h>
#include <Entity/Entity.h>
#include <Camera/Camera.h>

class Game
{
	private :
		sf::RenderWindow m_window ;
		InputManager m_inputManager ;
		sf::Clock m_clock ;
		sf::Time m_timeStamp ;
		World m_world ;
		
	public :
		Game() ;
		~Game() ;
		
		void run() ;
		void handleEvent() ;
		void update() ;
		void render() ;
} ;

#endif
