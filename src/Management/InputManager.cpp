#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <fftw3.h>

#include <Management/InputManager.h>

InputManager::InputManager(float gradMin, float gradMax, sf::Time timeCapture) :
	m_gradMin(gradMin), m_gradMax(gradMax), m_timeCapture(timeCapture), m_thread(&InputManager::threadInput, this), m_inputQueue(NULL), m_exit(true) {}

InputManager::~InputManager()
{
	stop() ;
	del<float>(&m_inputQueue) ;
}

void InputManager::launch()
{
	m_thread.launch() ;
}

void InputManager::stop()
{
	m_exit = false ;
}

Sample InputManager::getSample()
{
	sf::Clock clock ;
	m_recorder.start() ;
	while(clock.getElapsedTime() < m_timeCapture) {}
	m_recorder.stop() ;

	const sf::SoundBuffer& buffer = m_recorder.getBuffer() ;
	const sf::Int16* content = buffer.getSamples() ;
	unsigned long length = buffer.getSampleCount() ;

	Sample sample ;
	sample.content = content ;
	sample.length = length ;

	return sample ;
}

unsigned int InputManager::getFundamental(Sample& sample)
{
	if(sample.content != NULL)
	{
		fftw_complex *out ;
		double *in ;
		
		unsigned long length = sample.length ;

		out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * length) ;
		in = (double*) fftw_malloc(sizeof(double) * length) ;

		for(unsigned long i = 0 ; i < length ; i++)
		{
			in[i] = (double)sample.content[i] ;
		}

		fftw_plan p ;
		p = fftw_plan_dft_r2c_1d(length, in, out, FFTW_ESTIMATE) ;
		fftw_execute(p) ;
		fftw_destroy_plan(p) ;

		double amplitude = 0 ;
		double amplitudeMax = 0 ;
		unsigned int freqMax = 0 ;

		for(unsigned long i = 0 ; i < length ; i++)
		{
			amplitude = out[i][0] * out[i][0] + out[i][1] * out[i][1] ;
			if(amplitude > amplitudeMax)
			{
				amplitudeMax = amplitude ;
				freqMax = i ;
			}
		}

		freqMax = freqMax * 88200 / length ;
		return(freqMax) ;
	}
	else
	{
		return 0. ;
	}
}

void InputManager::store(unsigned int input)
{
	m_storedInputs[0] = m_storedInputs[1] ;
	m_storedInputs[1] = m_storedInputs[2] ;

	if(input > 50)
	{
		m_storedInputs[2] = input ;
	}
}

float InputManager::differenciate()
{
	float newAverage = (m_storedInputs[0] + m_storedInputs[1] + m_storedInputs[2]) / 3. ;
	float grad = newAverage - m_storedAverage ;
	m_storedAverage = newAverage ;

	if((grad < m_gradMax && grad > m_gradMin) || (grad > - m_gradMax && grad < - m_gradMin))
	{
		return(grad * 0.01) ;
	}
	else
	{
		return 0. ;
	}
}

void InputManager::threadInput()
{
	sf::Clock clock ;
	while(m_exit)
	{
		Sample sample = getSample() ;
		int input = getFundamental(sample) ;
		store(input) ;
		push<float>(&m_inputQueue, differenciate()) ;
	}
}



bool InputManager::pollInput(float* input)
{
	if(m_inputQueue != NULL)
	{
		*input = pop<float>(&m_inputQueue) ;
		return(*input != 0.) ;
	}
	else
	{
		return false ;
	}
}
