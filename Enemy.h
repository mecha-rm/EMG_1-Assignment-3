// Entity class that all other objects inherit
#pragma once
#include "Entity.h"
#include "Projectile.h" // used to setup pre-existing projectiles that model enemy projectiles.

#include <vector>


class Enemy : public Entity
{
public:
	/*
	* The enemy's type and file path. The rest of the factors are decided upon initalization.
	* 1. Small Asteroid 
	* 2. Large Asteroid
	* 3. Black Hole
	* 4. Planets
	* 5. Enemy Ship - Shooter
	* 6. Enemy Ship - Kamikaze
	* 7. Boss
	* 8. Projectile 1
	* 9. Projectile 2
	*/
	Enemy(unsigned short int type);

	void initEnemy(unsigned short int type);

	// returns the enemy type
	unsigned short int getType();

	// returns the rectangle size of the enemy sprites
	Rect getCrop();

	// sets the secondary radius of the enemy. This is the second radius of the enemy at the enemy's default size.
	void setSecondRadius(float radius2);

	// gets the secondary radius of the enemy. This is the second radius of the enemy at the enemy's default size.
	float getSecondRadius();

	// gets the second radius with the scale factor applied. This is the radius of the enemy at the enemy's current scale.
	void setScaledSecondRadius(float scaledRadius);

	// sets the second radius with the scale factor applied. This is the radius of the enemy at the enemy's current scale.
	float getScaledSecondRadius();
	
	// gets the variable 'force' stored in this class, which the enemines send to the 'entity' class to apply force every cycle.
	Vec2 getForce1();

	// sets the variable 'force' stored in this class, which the enemines send to the 'entity' class to apply force every cycle.
	void setForce1(Vec2 force1);

	// gets the second force that an enemy has. This force ISN'T used for movement, but something else.
	Vec2 getForce2();

	// gets a secondary force. This force is reserved for operations regarding the enemy, movement not withstanding.
	void setForce2(Vec2 force2);

	// gets the durability of the shield.
	float getShield();

	// sets the durability of the shield.
	void setShield(float shield);

	// gets the maximum durability of the shield.
	float getMaxShield();

	// Returns a random enemy object; the chances are different for each type.
	static Enemy * getRandEnemy();
	
	// Gets the spawn rate of a given enemy.
	// 1. Small Asteroid , 2. Large Asteroid, 3. Black Hole, 4. Planets, 5. Enemy Ship - Shooter, 6. Enemy Ship - Kamikaze, 7. Boss, 8. Projectile 1, 9. Projectile 2
	static int getSpawnRate(const unsigned int enemy);

	// gets all enemy spawn rates as an array
	// 1. Small Asteroid , 2. Large Asteroid, 3. Black Hole, 4. Planets, 5. Enemy Ship - Shooter, 6. Enemy Ship - Kamikaze, 7. Boss, 8. Projectile 1, 9. Projectile 2
	static int* getAllSpawnRatesArray();

	// gets all enemy spawn rates as a vector
	// 1. Small Asteroid , 2. Large Asteroid, 3. Black Hole, 4. Planets, 5. Enemy Ship - Shooter, 6. Enemy Ship - Kamikaze, 7. Boss, 8. Projectile 1, 9. Projectile 2
	static std::vector<int> getAllSpawnRatesVector();

	// if true, then the enemy's action is available to be used (if applicable). If false, the enemy can't use its action yet.
	bool actionAvailable();
	
	// if called, the cooldown period for the enemy's specific action begins. While this is happening, the enemy cannot perform this action.
	void actionOcurred();

	// Changes the spawn rates of the given enemy. The boss's spawn rate cannot be changed, since it's gotten upon collecting 10 energy cubes.
	// If a negative number is provided, the enemy's spawn rate is diminished. An enemy cannot have a smaller spawn rate than '0'.
	static void addToSpawnRates(int smlAsteroids = 0, int lgeAsteroids = 0, int blackHoles = 0, int planets = 0, int shooters = 0, int kamikazes = 0);

	void update(float deltaTime);

protected:

	// sets the maximum shield durability
	void setMaxShield(float maxShield);

	// Used to crop the sprite sheet.
	Rect crop;

	// A timer that's used to measure when 'actionTime' has been reached.
	float timer = 0.0F;
	// A float that stores when a specific action should take place.
	float actionTime = 0.0F;

private:
	unsigned short int type = 0; // the type of the enemy

	float shield = 0.0F; // the enemy's shield
	float maxShield = 0.0F; // the maximum durabiltiy of the enemy's shield.
	float radius2 = 0; // a second radius for the enemy. This is used for black holes, and enemy ships.

	// the spawn rates of all the enemies
	static const int SRLEN;
	// initalizations in cpp
	static int spawnRates[];

	Vec2 force; // the force of the entity
	Vec2 force2; // a secondary force. For the Black Hole, this force is used to draw the player in.

	//float 
	// Projectile proj1 = Projectile(Vec2(0.0F, 0.0F), "images/projectile.png", 20.0F, 5.0F, 0.0F, 1.0F, 1.0F);
	// Projectile proj2 = Projectile(Vec2(0.0F, 0.0F), "images/projectile3.png", 20.0F, 20.0F, 0.0F, 1.0F, 1.0F);
};

