#include <SFML/System.hpp>
#include <Game/Game.h>

int main()
{
	Game* game = new Game ;
	sf::Thread main_thread(&Game::run, game) ;
	main_thread.launch() ;
	main_thread.wait() ;
	delete game ;
	return 0 ;
}
