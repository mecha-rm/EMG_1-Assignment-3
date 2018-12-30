// Math functions
#include "spine/extension.h" // allows the use of pi
// #define PI 3.1415926535897932385f

#include "UtilityMath.h"
#include "Matrix.h" // also includes personal Vector.h
#include <math.h>

// calculates collision between two entities
bool UtilityMath::collision(Entity * e1, Entity * e2)
{
	float dist(0); // distance between entities
	float sumRadii = e1->getScaledRadius() + e2->getScaledRadius(); // adds together the radii of the entities at their scale

	// The position is based on the centre of the sprite.
	dist = sqrt(pow(e2->getPosition().x - e1->getPosition().x, 2) + pow(e2->getPosition().y - e1->getPosition().y, 2));	
	
	return (dist <= sumRadii); // if the entities are intersecting or touching, there is collision.
}

// calculates collision between two circles
bool UtilityMath::collision(Vec2 pos1, float r1, Vec2 pos2, float r2)
{
	int dist = sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2)); // calculates the distance between the two circles.
	return (dist <= r1 + r2);
}

// Rotates a 2D vector using its x and y points.
cocos2d::Vec2 UtilityMath::rotate(cocos2d::Vec2 points, float theta)
{
	// The setup in Matrix4 is the following:
	// 00, 01, 02, 03
	// 04, 05, 06, 07
	// 08, 09, 10, 11
	// 12, 13, 14, 15

	// degrees to radians - 1 degree = pi/180 radians. 
	// radians to degrees - 1 radian = 180/pi degrees.

	float cosTheta(cosf(theta)); // gets the cos of the angle
	float sinTheta(sinf(theta)); // gets the sin of the angle
	
	// Matrix4 rMatrix(cosTheta, -sinTheta, sinTheta, cosTheta);
	// Because the class uses a 4 x 4 matrix, the rest of the values are set to 0. We offset it by the world's centre to bring it to 0, 0, which we will add back later.
	// These values get stored as a 4 element Vec4 matrix, with the values being x, y, z, and w respectively.

	// The rotation matrix
	// cos(a), -sin(a) 
	// sin(a), cos(a)
	Matrix4 rMatrix(cosTheta, -sinTheta, 0, 0,
					sinTheta, cosTheta, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);

	// The points to be rotated
	Matrix4 pMatrix(points.x, 0, 0, 0,
				   points.y, 0, 0, 0,
				   0, 0, 1, 0,
				   0, 0, 0, 1);

	pMatrix = rMatrix * pMatrix;

	return cocos2d::Vec2(pMatrix[0][0], pMatrix[1][0]);
}

// gets the four corners, the centre, and the rotation factor. This is old, and should not be used.
void UtilityMath::rotate(cocos2d::Vec2 * corners, cocos2d::Vec2 &centre, float theta)
{
	// degrees to radians - 1 degree = pi/180 radians. 
	// radians to degrees - 1 radian = 180/pi degrees.
	float cosTheta(cos(theta * (PI / 180))); // gets the cos of the angle
	float sinTheta(sin(theta * (PI / 180))); // gets the sin of the angle

	
	// The setup in Matrix4 is the following:
	// 00, 01, 02, 03
	// 04, 05, 06, 07
	// 08, 09, 10, 11
	// 12, 13, 14, 15

	// Matrix4 rMatrix(cosTheta, -sinTheta, sinTheta, cosTheta);
	// Because the class uses a 4 x 4 matrix, the rest of the values are set to 0. We offset it by the world's centre to bring it to 0, 0, which we will add back later.
	// These values get stored as a 4 element Vec4 matrix, with the values being x, y, z, and w respectively.

	// The rotation matrix
	// cos(a), -sin(a) 
	// sin(a), cos(a)
	Matrix4 rMatrix(cosTheta, -sinTheta, 0, 0,
					sinTheta, cosTheta, 0, 0,
					0, 0, 0, 0,
					0, 0, 0, 0);
	
	// These can be initalized as either Vector4s, or as floats.
	Matrix4 c1Matrix(Vector4((corners[0] - centre).x, 0.0F, 0.0F, 0.0F),
		Vector4((corners[0] - centre).y, 0.0F, 0.0F, 0.0F),
		Vector4(0.0F, 0.0F, 0.0F, 0.0F),
		Vector4(0.0F, 0.0F, 0.0F, 0.0F));

	// Corner 2 (Top Right)
	Matrix4 c2Matrix((corners[1] - centre).x, 0, 0, 0,
		(corners[1] - centre).y, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);

	// Corner 3 (Bottom Left)
	Matrix4 c3Matrix((corners[2] - centre).x, 0, 0, 0,
		(corners[2] - centre).y, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);
	// Corner 4 (Bottom Right)
	Matrix4 c4Matrix((corners[3] - centre).x, 0, 0, 0,
		(corners[3] - centre).y, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);

	// Rotates the coordinates by multiplying them all by the rotation factor.
	c1Matrix *= rMatrix;
	c2Matrix *= rMatrix;
	c3Matrix *= rMatrix;
	c4Matrix *= rMatrix;

	// Because these get stored in vectors, we need to pick out the specific values we need. 
	// Both the 'x' value and 'y' value of the corner are stored within the first indexes of their given Vector4 sections of the overall matrix.
	// Vector4 (x, y, z, w) - each row has this setup.
	// 00, 01, 02, 03
	// 04, 05, 06, 07
	// 08, 09, 10, 11
	// 12, 13, 14, 15

	// Storing the values, and bringing them back to where the should be.
	// Corner 1 (Top Left)
	corners[0].x = c1Matrix[0].x + centre.x; // x's value is stored in the 'x' member variable of the first Vector 4 (index 0)
	corners[0].y = c1Matrix[1].x + centre.y; // y's value is stored in the 'x' member variable of the second Vector 4 (index 1)

	// Corner 2 (Top Right)
	corners[1].x = c1Matrix[0].x + centre.x;
	corners[1].y = c1Matrix[1].x + centre.y;

	// Corner 3 (Bottom Left)
	corners[2].x = c1Matrix[0].x + centre.x;
	corners[2].y = c1Matrix[1].x + centre.y;

	// Corner 4 (Bottom Right)
	corners[3].x = c1Matrix[0].x + centre.x;
	corners[3].y = c1Matrix[1].x + centre.y;
}

// rotates an entity in 3D using the supplied axis.
cocos2d::Vec3 UtilityMath::rotate(cocos2d::Vec3 points, float theta, char axis)
{
	axis = tolower(axis); // makes the axis lowercase for checking purposes

	float cosTheta(cosf(theta)); // gets the cos of the angle
	float sinTheta(sinf(theta)); // gets the sin of the angle

	// Matrix4 rMatrix(cosTheta, -sinTheta, sinTheta, cosTheta);
	// Because the class uses a 4 x 4 matrix, the rest of the values are set to 0. We offset it by the world's centre to bring it to 0, 0, which we will add back later.
	// These values get stored as a 4 element Vec4 matrix, with the values being x, y, z, and w respectively.
	
	Matrix4 rMatrix;

	switch (axis)
	{
	case 'x': // x-axis rotation
		rMatrix = Matrix4(
			1, 0, 0, 0,
			0, cosTheta, -sinTheta, 0,
			0, sinTheta, cosTheta, 0,
			0, 0, 0, 1
		);
		break;

	case 'y': // y-axis rotation
		rMatrix = Matrix4(
			cosTheta, 0, sinTheta, 0,
			0, 1, 0, 0,
			-sinTheta, 0, cosTheta, 0,
			0, 0, 0, 1
		);
		break;

	case 'z':
	default:
		rMatrix = Matrix4(
			cosTheta, -sinTheta, 0, 0,
			sinTheta, cosTheta, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}
	

	// The points to be rotated
	Matrix4 pMatrix(points.x, 0, 0, 0,
					points.y, 0, 0, 0,
					points.z, 0, 0, 0,
					0, 0, 0, 1);

	pMatrix = rMatrix * pMatrix; // calculation

	return cocos2d::Vec3(pMatrix[0][0], pMatrix[1][0], pMatrix[2][0]); // returns the points
}

// finds the dot product angle between two points
float UtilityMath::dotAngle(cocos2d::Vec2 v1, cocos2d::Vec2 v2)
{
	// Equation: (cos ^ -1)(v1 . v2 / (||v1||)(||v2||))
	return acosf(v1.dot(v2) / (v1.length() * v2.length()));
}

// conversion from degrees to radians. 1 degree = pi/180 radians. 
float UtilityMath::degreesToRadians(float degrees) { return degrees * (PI / 180); }

// conversion from radians to degrees. 1 radian = 180/pi degrees.
float UtilityMath::radiansToDegrees(float radians) { return radians * (180 / PI); }

// random range from lbound to ubound, upto but not including ubound if 'includeUBound' is false.
int UtilityMath::randInt(int lBound, int uBound, bool includeUBound)
{
	int tempInt(0);
	int randInt(0);
	// If the upper and lower bounds on the same, it returns the lBound
	if (lBound == uBound)
	{
		return lBound;
	}
	// If the lower bound is greater than the upper bound, they are swapped
	else if (lBound > uBound)
	{
		tempInt = lBound;
		lBound = uBound;
		uBound = tempInt;
	}

	// If the upperbound is positive, the values can be used as is.
	// If the upperbound and lowerbound are both negative, then a randomizer is run to get their absoluted range, then another randomizer is run to make it positive or negative.

	randInt = (uBound > 0) ? rand() % (uBound - lBound + includeUBound) + lBound : (abs(uBound) - abs(lBound) + includeUBound) + abs(lBound);

	// If the number must be negative, it is multiplied by -1 to make it so.
	if (lBound < 0 & uBound < 0)
		randInt *= -1;
	randInt = rand() % (uBound - lBound + includeUBound) + lBound;

	return randInt;
}