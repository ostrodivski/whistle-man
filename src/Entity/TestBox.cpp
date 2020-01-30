#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Entity/TestBox.h>

TestBox::TestBox(sf::Vector2f position, sf::Vector2f defaultVelocity) : Entity(position, defaultVelocity, sf::Vector2f(50, 50), 0, 0)
{
	m_bounds.push_back(new AABB(sf::Vector2f(0, 0), sf::Vector2f(200, 200))) ;
}

TestBox::~TestBox()
{
	delete(m_bounds[0]) ;
}

void TestBox::update(sf::Time elapsed)
{
}

void TestBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform() ;
	sf::RectangleShape rectangle(sf::Vector2f(200, 200)) ;
	rectangle.setFillColor(sf::Color(255, 0, 0)) ;
	target.draw(rectangle, states) ;
}

void TestBox::onCollision(Entity* entity) {}
