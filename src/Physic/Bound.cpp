#include <math.h>

#include <Physic/Bound.h>

#define PI 3.14159265

Point::Point(sf::Vector2f p_position) : position(p_position) {}
AABB::AABB(sf::Vector2f p_position, sf::Vector2f p_dimensions) : position(p_position), dimensions(p_dimensions) {}
Circle::Circle(sf::Vector2f p_center, float p_radius) : center(p_center), radius(p_radius) {}
Segment::Segment(sf::Vector2f p_start, sf::Vector2f p_end) : start(p_start), end(p_end) {}

bool Point::collisionCheck(Bound* bound, sf::Vector2f* tangent, sf::Vector2f* normal) { return bound -> collisionCheck(this, tangent, normal) ;}
bool Point::collisionCheck(Point* point, sf::Vector2f* tangent, sf::Vector2f* normal) { return false ;}
bool Point::collisionCheck(AABB* aabb, sf::Vector2f* tangent, sf::Vector2f* normal)
{
	float xA, yA, x_leftB, x_rightB, y_topB, y_bottomB ;
	xA = globalPosition.x ;
	yA = globalPosition.y ;

	x_leftB = aabb -> globalPosition.x ;
	x_rightB = x_leftB + aabb -> globalDimensions.x ;
	y_topB = aabb -> globalPosition.y ;
	y_bottomB = y_topB + aabb -> globalDimensions.y ;

	return((xA >= x_leftB) && (xA <= x_rightB) && (yA >= y_topB) && (yA <= y_bottomB)) ;
}

bool Point::collisionCheck(Circle* circle, sf::Vector2f* tangent, sf::Vector2f* normal)
{
	float x, y, x_c, y_c, dist_2, globalRadius_2 ;

	x = globalPosition.x ;
	y = globalPosition.y ;
	x_c = circle -> globalCenter.x ;
	y_c = circle -> globalCenter.y ;
	dist_2 = (x - x_c) * (x - x_c) + (y - y_c) * (y - y_c) ;
	globalRadius_2 = circle -> globalRadius * circle -> globalRadius ;

	return(dist_2 < globalRadius_2) ;
}

bool Point::collisionCheck(Segment* segment, sf::Vector2f* tangent, sf::Vector2f* normal) { return false ;}

bool AABB::collisionCheck(Bound* bound, sf::Vector2f* tangent, sf::Vector2f* normal) { return(bound -> collisionCheck(this, tangent, normal)) ;}
bool AABB::collisionCheck(Point* point, sf::Vector2f* tangent, sf::Vector2f* normal) { return(point -> collisionCheck(this, tangent, normal)) ;}

bool AABB::collisionCheck(AABB* aabb, sf::Vector2f* tangent, sf::Vector2f* normal)
{
	Point cornerA, cornerB ;
	cornerA.globalPosition = globalPosition ;
	cornerB.globalPosition = aabb -> globalPosition ;
	if(collisionCheck(&cornerB, NULL, NULL) || aabb -> collisionCheck(&cornerA, NULL, NULL))
	{
		return true ;
	}
	
	float x_leftA, x_leftB, x_rightA, x_rightB, y_bottomA, y_bottomB, y_topA, y_topB ;

	x_leftA = globalPosition.x ;
	x_leftB = aabb -> globalPosition.x ;
	x_rightA = x_leftA + globalDimensions.x ;
	x_rightB = x_leftB + aabb -> globalDimensions.x ;
	y_topA = globalPosition.y ;
	y_topB = aabb -> globalPosition.y ;
	y_bottomA = y_topA + globalDimensions.y ;
	y_bottomB = y_topB + aabb -> globalDimensions.y ;

	bool span_left, span_right, span_below, span_above ;

	span_right = x_leftA >= x_leftB && x_leftA <= x_rightB ;
	span_left = x_rightA >= x_leftB && x_rightA <= x_rightB ;
	span_below = y_topA >= y_topB && y_topA <= y_bottomB ;
	span_above = y_bottomA >= y_topB && y_bottomA <= y_bottomB ;

	return((span_right && span_above) || (span_right && span_below) || (span_left && span_above) || (span_left && span_below)) ;	
}

bool AABB::collisionCheck(Circle* circle, sf::Vector2f* tangent, sf::Vector2f* normal)
{
	AABB box ;
	box.globalPosition = circle -> globalCenter - sf::Vector2f(1, 1) * (float)(circle -> globalRadius) ;
	box.globalDimensions = sf::Vector2f(1, 1) * (float)(2 * circle -> globalRadius) ;

	if(!collisionCheck(&box, NULL, NULL))
	{
		return false ;
	}

	Point corners[4] ;
	corners[0].globalPosition = globalPosition ;
	corners[1].globalPosition = globalPosition + globalDimensions ;
	corners[2].globalPosition = globalPosition + sf::Vector2f(globalDimensions.x, 0) ;
	corners[3].globalPosition = globalPosition + sf::Vector2f(0, globalDimensions.y) ;

	if(collisionCheck(&corners[0], NULL, NULL) || collisionCheck(&corners[1], NULL, NULL) || collisionCheck(&corners[2], NULL, NULL) || collisionCheck(&corners[3], NULL, NULL))
	{
		return true ;
	}
	
	if(corners -> collisionCheck(circle, NULL, NULL))
	{
		return true ;
	}
	
	Point center ;
	center.position = circle -> center ;
	if(collisionCheck(&center, NULL, NULL))
	{
		return true ;
	}

	float x_u, y_u, x_v, y_v, x_w, y_w, u_proj, v_proj ;

	x_u = globalDimensions.x ;
	y_u = globalPosition.y ;
	x_v = globalPosition.x ;
	y_v = globalDimensions.y ;
	x_w = globalPosition.x - circle -> globalCenter.x ;
	y_w = globalPosition.y - circle -> globalCenter.y ;
	u_proj = x_u * x_w + y_u * y_w ;
	v_proj = x_v * x_w + y_v * y_w ;

	return ((u_proj < 0 || fabs(u_proj) < globalDimensions.x) || (v_proj < 0 || fabs(v_proj) < globalDimensions.y)) ;
}

bool AABB::collisionCheck(Segment* segment, sf::Vector2f* tangent, sf::Vector2f* normal)
{
	Segment left_side, right_side, top_side, bottom_side ;
	top_side.globalStart = globalPosition ;
	top_side.globalEnd = globalPosition + sf::Vector2f(globalDimensions.x, 0) ;
	bottom_side.globalStart = globalPosition + sf::Vector2f(0, globalDimensions.y) ;
	bottom_side.globalEnd = globalPosition + globalDimensions ;
	left_side.globalStart = globalPosition ;
	left_side.globalEnd = globalPosition + sf::Vector2f(0, globalDimensions.y) ;
	right_side.globalStart = globalPosition + sf::Vector2f(globalDimensions.x, 0) ;
	right_side.globalEnd = globalPosition + globalDimensions ;

	return(segment -> collisionCheck(&left_side, NULL, NULL) || segment -> collisionCheck(&right_side, NULL, NULL) ||
		segment -> collisionCheck(&top_side, NULL, NULL) || segment -> collisionCheck(&bottom_side, NULL, NULL)) ;
}

bool Circle::collisionCheck(Bound* bound, sf::Vector2f* tangent, sf::Vector2f* normal) { return bound -> collisionCheck(this, tangent, normal) ;}
bool Circle::collisionCheck(Point* point, sf::Vector2f* tangent, sf::Vector2f* normal) { return point -> collisionCheck(this, tangent, normal) ;}
bool Circle::collisionCheck(AABB* aabb, sf::Vector2f* tangent, sf::Vector2f* normal) { return aabb -> collisionCheck(this, tangent, normal) ;}

bool Circle::collisionCheck(Circle* circle, sf::Vector2f* tangent, sf::Vector2f* normal)
{
	float dist = sqrt((circle -> globalCenter.x - globalCenter.x) * (circle -> globalCenter.x - globalCenter.x) + (circle -> globalCenter.y - globalCenter.y) * (circle -> globalCenter.y - globalCenter.y)) ;

	return(dist < globalRadius + circle -> globalRadius) ;
}

bool Circle::collisionCheck(Segment* segment, sf::Vector2f* tangent, sf::Vector2f* normal)
{
	float x_c, y_c, x_u, y_u, x_v, y_v, uv_det, u_c, v_c, uv_dist_2, uv_rad_2 ;
	
	x_c = globalCenter.x - segment -> globalStart.x ;
	y_c = globalCenter.y - segment -> globalStart.y ;

	x_u = segment -> globalEnd.x - segment -> globalStart.x ;
	y_u = segment -> globalEnd.y - segment -> globalStart.y ;
	x_v = - y_u ;
	y_v = x_u ;
	
	uv_det = x_u * y_v - x_v * y_u ;

	u_c = 1/uv_det * (y_v * x_c - x_v * y_c) ;
	v_c = 1/uv_det * (- y_u * x_c + x_u * y_c) ;
	
	uv_dist_2 = v_c * v_c ;
	uv_rad_2 = globalRadius * globalRadius / (x_u * x_u + y_u * y_u) ;

	if(uv_dist_2 > uv_rad_2)
	{
		return false ;
	}
	else
	{
		float u_int = sqrt(uv_rad_2 * uv_rad_2 - uv_dist_2 * uv_dist_2) ;
		bool exit = u_c < 1 + u_int && u_c > 0 ;
		
		if(exit)
		{
			float norm = sqrt(x_u * x_u + y_u * y_u) ;
			*tangent = sf::Vector2f(x_u, y_u) / norm ;
			*normal = sf::Vector2f(x_v, y_v) / norm ;
		}

		return exit ;
	}	
}

bool Segment::collisionCheck(Bound* bound, sf::Vector2f* tangent, sf::Vector2f* normal) { return bound -> collisionCheck(this, tangent, normal) ;}
bool Segment::collisionCheck(Point* point, sf::Vector2f* tangent, sf::Vector2f* normal) { return point -> collisionCheck(this, tangent, normal) ;}
bool Segment::collisionCheck(AABB* aabb, sf::Vector2f* tangent, sf::Vector2f* normal) { return aabb -> collisionCheck(this, tangent, normal) ;}
bool Segment::collisionCheck(Circle* circle, sf::Vector2f* tangent, sf::Vector2f* normal) { return circle -> collisionCheck(this, tangent, normal) ;}

bool Segment::collisionCheck(Segment* segment, sf::Vector2f* tangent, sf::Vector2f* normal)
{
	float x_u, y_u, x_v, y_v, x_w, y_w, uw_det, vw_det ;
	
	x_u = segment -> globalStart.x - globalStart.x ;
	y_u = segment -> globalStart.y - globalStart.y ;
	x_v = segment -> globalEnd.x - globalStart.x ;
	y_v = segment -> globalEnd.y - globalStart.y ;
	x_w = segment -> globalEnd.x - globalStart.x ;
	y_w = segment -> globalEnd.y - globalStart.y ;
	
	uw_det = x_u * y_w - x_w * y_u ; 
	vw_det = x_v * y_w - x_w * y_v ;

	if(uw_det * vw_det >= 0)
	{
		return false ;
	}
	
	float x_P, y_P, uv_det, u_comT_P, v_comT_P, u_I, v_I ;
	bool inA, inB ;
	
	x_u = globalEnd.x - globalStart.x ;
	y_u = globalEnd.y - globalStart.y ;
	x_v = segment -> globalEnd.x - segment -> globalStart.x ;
	y_v = segment -> globalEnd.y - segment -> globalStart.y ;
	x_P = segment -> globalStart.x - globalStart.x ;
	y_P = segment -> globalStart.y - globalStart.y ;

	uv_det = - x_u * y_v + y_u * x_v ;
	u_comT_P = - y_v * x_P + x_v * y_P ;
	v_comT_P = - y_u * x_P + x_u * y_P ;
	
	u_I = 1/uv_det * u_comT_P ;
	v_I = 1/uv_det * v_comT_P ;
	
	inA = u_I < 1 && u_I > 0 ;
	inB = v_I < 1 && v_I > 0 ;

	return (inA && inB) ;
}


void Point::transform(sf::Vector2f origin, sf::Vector2f translation, float rotation, sf::Vector2f scale)
{
	globalPosition.x = (position.x - origin.x) * cos(rotation * PI / 180) - (position.y - origin.y) * sin(rotation * PI / 180) ;
	globalPosition.y = (position.x - origin.x) * sin(rotation * PI / 180) + (position.y - origin.y) * cos(rotation * PI / 180) ;
	globalPosition.x *= scale.x ;
	globalPosition.y *= scale.y ;
	globalPosition += translation ;
}

void AABB::transform(sf::Vector2f origin, sf::Vector2f translation, float rotation, sf::Vector2f scale)
{
	sf::Vector2f center ;
	center.x = position.x + dimensions.x / 2 ;
	center.y = position.y + dimensions.y / 2 ;
	globalPosition.x = (center.x - origin.x) * cos(rotation * PI / 180) - (center.y - origin.y) * sin(rotation * PI / 180) - dimensions.x / 2 ;
	globalPosition.y = (center.x - origin.x) * sin(rotation * PI / 180) + (center.y - origin.y) * cos(rotation * PI / 180) - dimensions.y / 2 ;
	globalPosition.x *= scale.x ;
	globalPosition.y *= scale.y ;
	globalDimensions.x = dimensions.x * scale.x ;
	globalDimensions.y = dimensions.y * scale.y ;
	globalPosition += translation ;
}

void Circle::transform(sf::Vector2f origin, sf::Vector2f translation, float rotation, sf::Vector2f scale)
{
	globalCenter.x = (center.x - origin.x) * cos(rotation * PI / 180) - (center.y - origin.y) * sin(rotation * PI / 180) ;
	globalCenter.y = (center.x - origin.x) * sin(rotation * PI / 180) - (center.y - origin.y) * cos(rotation * PI / 180) ;
	globalCenter *= scale.x ;
	globalRadius = radius * scale.x ;
	globalCenter += translation ;
}

void Segment::transform(sf::Vector2f origin, sf::Vector2f translation, float rotation, sf::Vector2f scale)
{
	globalStart.x = (start.x - origin.x) * cos(rotation * PI / 180) - (start.y - origin.y) * sin(rotation * PI / 180) ;
	globalStart.y = (start.x - origin.x) * sin(rotation * PI / 180) + (start.y - origin.y) * cos(rotation * PI / 180) ;
	globalEnd.x = (end.x - origin.x) * cos(rotation * PI / 180) - (end.y - origin.y) * sin(rotation * PI / 180) ;
	globalEnd.y = (end.x - origin.x) * sin(rotation * PI / 180) + (end.y - origin.y) * cos(rotation * PI / 180) ;
	globalStart.x *= scale.x ;
	globalStart.y *= scale.y ;
	globalEnd.x *= scale.x ;
	globalEnd.y *= scale.y ;
	globalStart += translation ;
	globalEnd += translation ;
}
