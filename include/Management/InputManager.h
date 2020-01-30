#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <Management/Queue.h>
#include <Management/Sample.h>

class InputManager
{
	private :
		Queue<float>* m_inputQueue ;
		sf::SoundBufferRecorder m_recorder ;
		sf::Time m_timeCapture ;

		int m_storedInputs[3] ;
		float m_storedAverage ;

		float m_gradMax ;
		float m_gradMin ;

		sf::Thread m_thread ;
		bool m_exit ;
		
		Sample getSample() ;
		void store(unsigned int input) ;
		unsigned int getFundamental(Sample& sample) ;
		float differenciate() ;
		void threadInput() ;
		
	public :
		InputManager(float gradMin = 50, float gradMax = 400, sf::Time timeCapture = sf::milliseconds(100)) ;
		~InputManager() ;

		void launch() ;
		void stop() ;
		
		bool pollInput(float* input) ;
} ;

#endif
