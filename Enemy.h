// Entity class that all other objects inherit
#pragma once
#include "Entity.h"
#include <vector>

class Enemy : public Entity
{
public:
	// The enemy's type and file path. The rest of the factors are decided upon initalization.
	// 1. Small Asteroid 
	// 2. Large Asteroid
	// 3. Black Hole
	// 4. Planets
	// 5. Enemy Ship - Shooter
	// 6. Enemy Ship - Kamikaze
	// 7. Boss
	Enemy(unsigned short int type);

	void initEnemy(unsigned short int type);

	// returns the enemy type
	unsigned short int getType();

	// sets the secondary radius of the enemy. This is the second radius of the enemy at the enemy's default size.
	void setSecondRadius(float radius2);

	// gets the secondary radius of the enemy. This is the second radius of the enemy at the enemy's default size.
	float getSecondRadius();

	// gets the second radius with the scale factor applied. This is the radius of the enemy at the enemy's current scale.
	void setScaledSecondRadius(float scaledRadius);

	// sets the second radius with the scale factor applied. This is the radius of the enemy at the enemy's current scale.
	float getScaledSecondRadius();

	// gets the second force that an enemy has. This force ISN'T used for movement, but something else.
	Vec2 getForce2();

	// gets a secondary force. This force is reserved for operations regarding the enemy, movement not withstanding.
	void setForce2(Vec2 force2);

	// Returns a random enemy object; the chances are different for each type.
	static Enemy * getRandEnemy();
	
	// Gets the spawn rate of a given enemy.
	// 1. Small Asteroid , 2. Large Asteroid, 3. Black Hole, 4. Planets, 5. Enemy Ship - Shooter, 6. Enemy Ship - Kamikaze, 7. Boss
	static int getSpawnRate(const unsigned int enemy);

	// gets all enemy spawn rates as an array
	// 1. Small Asteroid , 2. Large Asteroid, 3. Black Hole, 4. Planets, 5. Enemy Ship - Shooter, 6. Enemy Ship - Kamikaze, 7. Boss
	static int* getAllSpawnRatesArray();

	// gets all enemy spawn rates as a vector
	// 1. Small Asteroid , 2. Large Asteroid, 3. Black Hole, 4. Planets, 5. Enemy Ship - Shooter, 6. Enemy Ship - Kamikaze, 7. Boss
	static std::vector<int> getAllSpawnRatesVector();

	// Changes the spawn rates of the given enemy. The boss's spawn rate cannot be changed, since it's gotten upon collecting 10 energy cubes.
	// If a negative number is provided, the enemy's spawn rate is diminished. An enemy cannot have a smaller spawn rate than '0'.
	static void addToSpawnRates(int smlAsteroids = 0, int lgeAsteroids = 0, int blackHoles = 0, int planets = 0, int shooters = 0, int kamikazes = 0);

	void update(float deltaTime);

protected:

private:
	unsigned short int type = 0; // the type of the enemy

	int shield = 0; // the enemy's shield
	float radius2 = 0; // a second radius for the enemy. This is used for black holes.
	

	// the spawn rates of all the enemies
	static const int SRLEN;
	// initalizations in cpp
	static int spawnRates[];

	Vec2 force; // the force of the entity
	Vec2 force2; // a secondary force. For the Black Hole, this force is used to draw the player in.
};

