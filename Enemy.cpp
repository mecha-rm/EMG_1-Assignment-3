#include "Enemy.h"
#include "UtilityMath.h"

// 1. Small Asteroid , 2. Large Asteroid, 3. Black Hole, 4. Planets, 5. Enemy Ship - Shooter, 6. Enemy Ship - Kamikaze, 7. Boss
const int Enemy::SRLEN = 7;
int Enemy::spawnRates[SRLEN] = {5, 5, 1, 0, 0, 0, 0};

// constructor 
Enemy::Enemy(unsigned short int type) : Entity(Vec2(0, 0), "images/DUMMY.png") { initEnemy(type); } 

// Initalizes enemies
void Enemy::initEnemy(unsigned short int type)
{ 
	setScreenWrap(true); // turns on screen wrapping
	rotateLR = false; // Since the theta is '0' by default, this speeds up the computation time when no rotations are used.
	this->type = type; // saves the enemy type; if the type is invalid, it will be set to '0' in the 'default' case statement.
	getSprite()->setGlobalZOrder(2);
	getSprite()->setAnchorPoint(Vec2(0.5, 0.5));
	switch (type)
	{
	// Remember: wrapping poitnts are shared
	// Small Asteroid
	case 1:
		setTexture("images/asteroid_small.png");
		setRadius(20.0F);	
		setMaxHealth(1); // health of 1
		setHealth(getMaxHealth());
		setDamage(1); // damage given

		// Setting the force of the asteroid
		force = Vec2(umath::randInt(180, 220, true), umath::randInt(180, 220, true)); // abs(velocity) ranges from
		setMass(2.0F);
		setConstVelocity(true);
		break;

	// Large Asteroid
	case 2:
		setTexture("images/asteroid_large.png");
		setRadius(34.0F);
		setMaxHealth(1); // health of 1
		setHealth(getMaxHealth());
		setDamage(2); // damage given

		// Setting the force of the asteroid
		force = Vec2(umath::randInt(180, 220, true), umath::randInt(180, 220, true)); // abs(velocity) ranges from
		setMass(3.0F); // slightly higher mass than the small asteroids
		setConstVelocity(true);
		
		break;

	// Blackhole
	case 3:
		setTexture("images/black_hole.png");
		getSprite()->setGlobalZOrder(0);
		setScale(1.5F);
		setMass(2.5F); // the 'mass' is used to control the gravitational force of the blackhole.
		
		setMaxHealth(1); // health of 1
		setHealth(getMaxHealth());
		killable = false; // black holes disappear on their own, and thus cannot be killed.
		setDamage(4); // black holes instantly kill.

		force.x = 0;
		force.y = 0;
		setRadius(25.0F); // the hitcircle of the black hole's body.
		radius2 = 50.0F; // the radius of the suction area of the black hole
		force2 = Vec2(50.0F, 50.0F); // the force that's used to draw in other ships.
		
		break;
	// Planet
	case 4:
		setTexture("images/planet.png");
		setMaxHealth(1); // health of 1
		setHealth(getMaxHealth());
		killable = false; // planets cannot be destroyed.

		force.x = 10;
		force.y = 10;


		break;

	// Shooter
	case 5:
		setTexture("images/enemy_ship_shooter.png");
		setMaxHealth(1); // health of 1
		setHealth(getMaxHealth());
		force.x = 10;
		force.y = 10;

		break;

	// Kamikaze
	case 6:
		setTexture("images/enemy_ship_kamikaze_green.png");
		setMaxHealth(1); // health of 1
		setHealth(getMaxHealth());
		force.x = 10;
		force.y = 10;
		break;

	// Boss
	case 7:
		setTexture("images/boss.png");
		setMaxHealth(3); // health of 1
		setHealth(getMaxHealth());
		force.x = 10;
		force.y = 10;

		break;

	// DUMMY (i.e. the enemy that shows up when there is no enemy)
	default:
		this->type = 0; // sets the 'type' to 0.
		force.x = 1.0F;
		force.y = 1.0F;
		setMass(0.001F);
		break;

	}

	// Determines what direction the enemy will be going.
	force.x *= (rand() % 2 == 0) ? -1 : 1;
	force.y *= (rand() % 2 == 0) ? -1 : 1;

	// If the enemy is going left
	if (force.x < 0)
	{
		setPositionX(getWrapPointsMax().x + getWidth() / 2);
	}
	// If the enemy is going right
	else if (force.x > 0)
	{
		setPositionX(getWrapPointsMin().x - getWidth() / 2);
	}

	// If the enemy is going down
	if (force.y < 0)
	{
		setPositionY(getWrapPointsMax().y + getHeight() / 2);
	}
	// If the enemy is going up
	else if (force.y > 0)
	{
		setPositionY(getWrapPointsMin().y - getHeight() / 2);
	}

	// If the force is '0' for the enemy, it spawns randomly on screen, as it would be spawned off-screen and move iself on-screen otherwise.
	if (force.x == 0 && force.y == 0)
	{
		setPosition(Vec2(rand() % (int)getWrapPointsMax().x + 1, rand() % (int)getWrapPointsMax().y + 1));
	}
	else // randomizes the location of the entity if there is force being applied to it.
	{
		// 1 = random starting position on the x-axis. 0 or 2 = random starting position on the y-axis
		switch (rand() % 3)
		{
			// Gives a random position on the X-axis.
		case 0:
			setPositionX(rand() % (int)getWrapPointsMax().x + 1); // wrapPointsMax.x is the width of the screen
		// Gives a random position on the x-axis.
			break;
			// Gives a random position on the y-axis.
		default:
			setPositionY(rand() % (int)getWrapPointsMax().y + 1); // wrapPointsMax.y is the height of the screen
			break;
		}
	}

}

// Returns the type of the enemy.
unsigned short int Enemy::getType() { return type; }

// sets the secondary radius of the enemy.
void Enemy::setSecondRadius(float radius2) { this->radius2 = radius2; }

// gets the secondary radius of the enemy.
float Enemy::getSecondRadius() { return radius2; }

// gets the second radius with the scale factor applied
void Enemy::setScaledSecondRadius(float scaledRadius) { radius2 = scaledRadius / getScale(); }

// sets the second radius with the scale factor applied
float Enemy::getScaledSecondRadius() { return radius2 * getScale(); }

// gets the second force that an enemy has. This force ISN'T used for movement, but something else.
Vec2 Enemy::getForce2() { return force2; };

// gets a secondary force. This force is reserved for operations regarding the enemy, movement not withstanding.
void Enemy::setForce2(Vec2 force2) { this->force2 = force2; }

// Returns a random enemy, as influced by the spawn rates.
Enemy * Enemy::getRandEnemy()
{
	int chanceTotal = 0; // stores the number used for calculating the random chance
	int randInt = 0; // the random number generated
	int type = 0; // the type of enemy that will be made

	for (int i = 0; i < SRLEN; i++)
	{
		chanceTotal += spawnRates[i]; // adds togehter all spawn rates.
	}

	// Generates the random number.
	randInt = rand() % chanceTotal + 1;
	chanceTotal = 0;

	// Goes through each index, checking the chances
	for (int i = 0; i < SRLEN; i++)
	{
		chanceTotal += spawnRates[i]; // adds togehter all spawn rates.
		// If the randInt is less than or equal to the current value, it will spawn the enemy at the given index.
		if (randInt <= chanceTotal) // determines the type of enemy to be generated
		{
			type = i + 1;
			break;
		}
	}

	// Returns an enemy object.
	return new Enemy(type);
}

// Returns the spawn rate of the given enemy.
int Enemy::getSpawnRate(const unsigned int enemy)
{
	static int tempInt;
	// If the enemy doesn't exist, a '0' is returned.
	if (enemy >= SRLEN)
	{
		return 0;
	}
	else
	{
		return spawnRates[enemy];
	}
}

// Gets all spawn rates in an array
int* Enemy::getAllSpawnRatesArray() { return spawnRates; }

// Gets all spawn rates in a vector
std::vector<int> Enemy::getAllSpawnRatesVector()
{
	std::vector<int> tempVec;
	for (int i = 0; i < SRLEN; i++)
		tempVec.push_back(spawnRates[i]);

	return tempVec;
 }

// Adds to the spawn rates
void Enemy::addToSpawnRates(int smlAsteroids, int lgeAsteroids, int blackHoles, int planets, int shooters, int kamikazes)
{	
	// Adds to the spawn rates
	spawnRates[0] += smlAsteroids;
	spawnRates[1] += lgeAsteroids;
	spawnRates[2] += blackHoles;
	spawnRates[3] += planets;
	spawnRates[4] += shooters;
	spawnRates[5] += kamikazes;

	// If the spawn rates have been dropped below 0, they are now equal to 0.
	for (int i = 0; i < SRLEN; i++)
		if (spawnRates[i] < 0)
			spawnRates[i] = 0;
}

// Update function for enemies.
void Enemy::update(float deltaTime)
{
	// 1. Small Asteroid , 2. Large Asteroid, 3. Black Hole, 4. Planets, 5. Enemy Ship - Shooter, 6. Enemy Ship - Kamikaze, 7. Boss
	// Black Holes
	switch (type)
	{
	case 3:
		if (getTime() > 10.0F) // if a whole second has passed, then the blackhole is removed.
		{
			setHealth(0); // sets the health of the 'blackhole' to '0' so that it is automatically deleted.
		}
		break;
	}

	addForce(force.x, force.y); // adds force to the standard force of the entity
	Entity::update(deltaTime);
}

