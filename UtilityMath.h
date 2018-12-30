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
	// Returns true if two objects are colliding or touching, false if they are not.
	// The 'touch' parameter is used to determine if two objects that are touching but not colliding trigger a 'true' result.
	static bool collision(Entity * e1, Entity * e2);

	// Calculates collision between two circles. Pos1 and r1 refer to one object, with pos2 and r2 referring to the second one.
	// The 'touch' parameter is used to determine if two objects that are touching but not colliding trigger a 'true' result.
	static bool collision(Vec2 pos1, float r1, Vec2 pos2, float r2);

	// rotates a vector; uses radians for rotations.
	static cocos2d::Vec2 rotate(cocos2d::Vec2 points, float theta);
	
	// gets the four corners, the centre, and the rotation factor. The rotation factor is assuming the object is at an angle of 0. Uses radians for rotations.
	static void rotate(cocos2d::Vec2 * corners, cocos2d::Vec2 &centre, float theta);

	// Rotates an object in 3d based on the passed axis. Pass 'x', 'y', or 'z' (non-case sensitive). Invalid passes will result in a 'Z' rotation. Uses radians for rotations.
	static cocos2d::Vec3 rotate(cocos2d::Vec3 points, float theta, char axis = 'z');

	// returns the angle between two points in radians. This uses the dot product angle theorem.
	static float dotAngle(cocos2d::Vec2 v1, cocos2d::Vec2 v2);

	// conversion from degrees to radians. 1 degree = pi/180 radians. 
	static float degreesToRadians(float degrees);
	// conversion from radians to degrees. 1 radian = 180/pi degrees.
	static float radiansToDegrees(float radians);

	// Returns a random number starting form 'lbound' upto ubound.
	// If 'includeUbound' is set to 'true', it's upto and including ubound; if false, it's upto but not including ubound. False by default.
	static int randInt(int lBound, int uBound, bool includeUBound = false);

protected:

private:

} umath;




#endif // ! USERMATH_H
