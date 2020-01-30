#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

#include <Entity/Entity.h>
#include <Entity/Air.h>
#include <Entity/Wall.h>
#include <Entity/Vortex.h>
#include <Entity/WhistleMan.h>

#include <World/World.h>

string World::m_LoadersPath = "./" ;

World::World(float velocityMax) : m_velocityMax(velocityMax)
{
	load("test") ;
	
	m_camera.attach(m_mainInstance) ;
	
	m_collisions = (unsigned int**)malloc(m_instances.size() * sizeof(unsigned int*)) ;
	for(unsigned int i = 0 ; i < m_instances.size() ; i++)
	{
		m_collisions[i] = (unsigned int*)malloc(m_instances.size() * sizeof(unsigned int)) ;
		for(unsigned int j = 0 ; j < m_instances.size() ; j++)
		{
			m_collisions[i][j] = 0 ;
		}
	}
}

World::~World()
{
	for(unsigned int i=0 ; i < m_instances.size() ; i++)
	{
		delete(m_instances[i]) ;
		free(m_collisions[i]) ;
	}
	free(m_collisions) ;
}

void World::load(string fileName)
{
	ifstream file ;
	file.open(m_LoadersPath + fileName, ios::in) ; 

	vector<string> argv ;
	unsigned int argc ;
	string buffer ;
	Entity* instance ;
	while(getline(file, buffer))
	{
		argv.erase(argv.begin(), argv.end()) ;
		while(buffer != ";;")
		{
			argv.push_back(buffer) ;
			getline(file, buffer) ;
		}

		argc = argv.size() - 1 ;
		switch(stoi(argv[0]))
		{
			case(0) : switch(argc)
			{
				case(0) : instance = new Air() ; break ;
				case(2) : instance = new Air(sf::Vector2f(stof(argv[1]), stof(argv[2]))) ; break ;
				case(4) : instance = new Air(sf::Vector2f(stof(argv[1]), stof(argv[2])), sf::Vector2f(stof(argv[3]), stof(argv[4]))) ; break ;
				case(5) : instance = new Air(sf::Vector2f(stof(argv[1]), stof(argv[2])), sf::Vector2f(stof(argv[3]), stof(argv[4])), stof(argv[5])) ; break ;
				default : cerr << "wrong arguments" << endl ; exit(1) ; break ;
			} break ;

			case(1) : switch(argc)
			{
				case(2) : instance = new WhistleMan(sf::Vector2f(stof(argv[1]), stof(argv[2]))) ; break ;
				case(4) : instance = new WhistleMan(sf::Vector2f(stof(argv[1]), stof(argv[2])), sf::Vector2f(stof(argv[3]), stof(argv[4]))) ; break ;
				case(6) : instance = new WhistleMan(sf::Vector2f(stof(argv[1]), stof(argv[2])), sf::Vector2f(stof(argv[3]), stof(argv[4])), stof(argv[5]), sf::milliseconds(stof(argv[6]))) ; break ;
				default : cerr << "wrong arguments" << endl ; exit(1) ; break ;
			} break ;

			case(2) : switch(argc)
			{
				case(2) : instance = new Vortex(sf::Vector2f(stof(argv[1]), stof(argv[2]))) ; break ;
				case(5) : instance = new Vortex(sf::Vector2f(stof(argv[1]), stof(argv[2])), sf::Vector2f(stof(argv[3]), stof(argv[4])), stof(argv[5])) ; break ;
				case(6) : instance = new Vortex(sf::Vector2f(stof(argv[1]), stof(argv[2])), sf::Vector2f(stof(argv[3]), stof(argv[4])), stof(argv[5]), stof(argv[6])) ; break ;
				default : cerr << "wrong arguments" << endl ; exit(1) ; break ;
			} break ;

			case(3) : switch(argc)
			{
				case(4) : instance = new Wall(sf::Vector2f(stof(argv[1]), stof(argv[2])), sf::Vector2f(stof(argv[3]), stof(argv[4]))) ; break ;
				default : if(argc > 4 && argc % 2 == 0)
				{
					vector<sf::Vector2f> bounds ;
					for(unsigned int i=5 ; i < argc ; i += 2)
					{
						bounds.push_back(sf::Vector2f(stof(argv[i]), stof(argv[i+1]))) ;
					}
					instance = new Wall(sf::Vector2f(stof(argv[1]), stof(argv[2])), sf::Vector2f(stof(argv[3]), stof(argv[4])), bounds) ;
				}
				else
				{
					cerr << "wrong arguments" << endl ;
					exit(1) ;
				}
				break ;
			} break ;
			default : cerr << "wrong ID" << endl ; exit(1) ; break ;
		}
		
		if(instance != NULL)
		{
			m_instances.push_back(instance) ;
		}
		m_mainInstance = m_instances[0] ;
	}
}

void World::calcVelocity(Entity* instance, sf::Time elapsed)
{
	sf::Vector2f acceleration ;
	for(unsigned int i=0 ; i < m_instances.size() ; i++)
	{
		acceleration += m_instances[i] -> getResultantForce(instance) ;
	}
	acceleration /= instance -> getMass() ;

	sf::Vector2f newVelocity = sf::Vector2f(instance -> getEffectiveVelocity() + acceleration * elapsed.asSeconds()) ;
	float norm = newVelocity.x * newVelocity.x + newVelocity.y * newVelocity.y ;
	if(norm > m_velocityMax)
	{
		instance -> setVelocity(newVelocity * m_velocityMax / norm) ;
	}
	else
	{
		instance -> setVelocity(newVelocity) ;
	}
}

void World::calcPosition(Entity* instance, sf::Time elapsed)
{
	instance -> setPosition(instance -> getPosition() + instance -> getEffectiveVelocity() * elapsed.asSeconds()) ;
}

bool World::collisionCheck(Entity* instance, unsigned int index)
{
	bool exit = false ;
	unsigned int j, k ;
	vector<Bound*> boundsA ;
	vector<Bound*> boundsB ;
	sf::Vector2f normal = sf::Vector2f(0, 0) ;
	sf::Vector2f tangent = sf::Vector2f(0, 0) ;

	for(unsigned int i=0 ; i < m_instances.size() && !exit ; i++)
	{
		if(i != index && m_collisions[index][i] == 0)
		{
			m_collisions[index][i] = 1 ;
			m_collisions[i][index] = 1 ;
			boundsA = instance -> getGlobalBounds() ;
			boundsB = m_instances[i] -> getGlobalBounds() ;
			
			for(j=0 ; j < boundsA.size() && !exit ; j++)
			{
				for(k=0 ; k < boundsB.size() && !exit ; k++)
				{
					exit = boundsA[j] -> collisionCheck(boundsB[k], &tangent, &normal) ;
				}
			}
		}
	}

	if(exit)
	{
		instance -> setVelocity(tangent * (instance -> getVelocity().x * tangent.x + instance -> getVelocity().y * tangent.y) -
		normal * (instance -> getVelocity().x * normal.x + instance -> getVelocity().y * normal.y)) ;
	}
	
	return exit ;
}

void World::handleEvent(float input)
{
	m_mainInstance -> setVelocity(m_mainInstance -> getVelocity() - sf::Vector2f(0, input)) ;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.setView(m_camera) ;
	for(unsigned int i=0 ; i < m_instances.size() ; i++)
	{
		m_instances[i] -> draw(target, states) ;
	}
}

void World::update(sf::Time elapsed)
{
	for(unsigned int i=0 ; i < m_instances.size() ; i++)
	{
		if(m_instances[i] -> getMass() != 0)
		{
			calcVelocity(m_instances[i], elapsed) ;
		}

		calcPosition(m_instances[i], elapsed) ;
		collisionCheck(m_instances[i], i) ;
		m_instances[i] -> update(elapsed) ;
	}

	for(unsigned int i=0 ; i < m_instances.size() ; i++)
	{
		for(unsigned int j=0 ; j < m_instances.size() ; j++)
		{
			m_collisions[i][j] = 0 ;
		}
	}
}
