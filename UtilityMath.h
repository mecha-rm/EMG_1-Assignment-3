// My personal math library
#ifndef  UTILITYMATH_H
#define UTILITYMATH_H

#include "Entity.h"

#include "cocos2d.h"
#include <cmath>

// namespace util
	
typedef class UtilityMath
{
public:
	// Returns true if two objects are colliding, false if they are not.
	static bool collision(Entity * e1, Entity * e2);

	// rotates a vector based on passed coordinate points.
	static cocos2d::Vec2 rotate(cocos2d::Vec2 points, cocos2d::Vec2 centre, float theta);
	// gets the four corners, the centre, and the rotation factor. The rotation factor is assuming the object is at an angle of 0.
	static void rotate(cocos2d::Vec2 * corners, cocos2d::Vec2 &centre, float theta); 

	// Returns a random number starting form 'lbound' upto ubound.
	// If 'includeUbound' is set to 'true', it's upto and including ubound; if false, it's upto but not including ubound. False by default.
	static int randInt(int lBound, int uBound, bool includeUBound = false);

protected:

private:

} umath;




#endif // ! USERMATH_H
