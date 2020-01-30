#ifndef BOUND_H
#define BOUND_H

#include <stdlib.h>
#include <SFML/Graphics.hpp>

struct Point ;
struct AABB ;
struct Circle ;
struct Segment ;

struct Bound
{	
	virtual ~Bound() = default ;
	
	virtual bool collisionCheck(Bound* bound, sf::Vector2f* tangent, sf::Vector2f* normal) = 0 ;
	virtual bool collisionCheck(Point* point, sf::Vector2f* tangent, sf::Vector2f* normal) = 0 ;
	virtual bool collisionCheck(AABB* aabb, sf::Vector2f* tangent, sf::Vector2f* normal) = 0 ;
	virtual bool collisionCheck(Circle* circle, sf::Vector2f* tangent, sf::Vector2f* normal) = 0 ;
	virtual bool collisionCheck(Segment* segment, sf::Vector2f* tangent, sf::Vector2f* normal) = 0 ;
	
	virtual void transform(sf::Vector2f origin, sf::Vector2f translation, float rotation, sf::Vector2f scale) = 0 ;
} ;

struct Point : public Bound
{
	Point(sf::Vector2f p_position = sf::Vector2f(0, 0)) ;
	
	sf::Vector2f position ;
	sf::Vector2f globalPosition ;
	
	virtual bool collisionCheck(Bound* bound, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(Point* point, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(AABB* aabb, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(Circle* circle, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(Segment* segment, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	
	virtual void transform(sf::Vector2f origin, sf::Vector2f translation, float rotation, sf::Vector2f scale) ;

} ;

struct AABB : public Bound
{
	AABB(sf::Vector2f p_position = sf::Vector2f(0, 0), sf::Vector2f p_dimensions = sf::Vector2f(0, 0)) ;
	
	sf::Vector2f position ;
	sf::Vector2f dimensions ;
	sf::Vector2f globalPosition ;
	sf::Vector2f globalDimensions ;
	
	virtual bool collisionCheck(Bound* bound, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(Point* point, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(AABB* aabb, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(Circle* circle, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(Segment* segment, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	
	virtual void transform(sf::Vector2f origin, sf::Vector2f translation, float rotation, sf::Vector2f scale) ;
} ;

struct Circle : public Bound
{
	Circle(sf::Vector2f p_center = sf::Vector2f(0, 0), float p_radius = 0.) ;
	
	sf::Vector2f center ;
	float radius ;
	sf::Vector2f globalCenter ;
	float globalRadius ;
	
	virtual bool collisionCheck(Bound* bound, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(Point* point, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(AABB* aabb, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(Circle* circle, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(Segment* segment, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	
	virtual void transform(sf::Vector2f origin, sf::Vector2f translation, float rotation, sf::Vector2f scale) ;
} ;

struct Segment : public Bound
{
	Segment(sf::Vector2f p_start = sf::Vector2f(0, 0), sf::Vector2f p_end = sf::Vector2f(0, 0)) ;
	
	sf::Vector2f start ;
	sf::Vector2f end ;
	sf::Vector2f globalStart ;
	sf::Vector2f globalEnd ;
	
	virtual bool collisionCheck(Bound* bound, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(Point* point, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(AABB* aabb, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(Circle* circle, sf::Vector2f* tangent, sf::Vector2f* normal) ;
	virtual bool collisionCheck(Segment* segment, sf::Vector2f* tangent, sf::Vector2f* normal) ;

	virtual void transform(sf::Vector2f origin, sf::Vector2f translation, float rotation, sf::Vector2f scale) ;
} ;

#endif
