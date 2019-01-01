#include "Enemy.h"
#include "UtilityMath.h"

/*
 * Type, Index, and Enemy
 * T01 [0]: Small Asteroid 
 * T02 [1]: Large Asteroid
 * T03 [2]: Black Hole
 * T04 [3]: Planets
 * T05 [4]: Enemy Ship - Shooter
 * T06 [5]: Enemy Ship - Kamikaze
 * T07 [6]: Boss
 * T08 [7]: Projectile 1
 * T09 [8]: Projectile 2
*/

const int Enemy::SRLEN = 9;
 int Enemy::spawnRates[SRLEN] = {10, 5, 1, 2, 3, 3, 0, 0, 0};

// constructor 
Enemy::Enemy(unsigned short int type) : Entity(Vec2(0, 0), "images/DUMMY.png") { initEnemy(type); } 

// Initalizes enemies
void Enemy::initEnemy(unsigned short int type)
{ 
	Vec2 rForce; // saves the force an enemy has, rotated. This is used to optimize force checking when deciding where to position the enemy at the start.

	setScreenWrap(true); // turns on screen wrapping
	// rotateLR = false; // Since the theta is '0' by default, this speeds up the computation time when no rotations are used.
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
		setScale(0.8);

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

		force = Vec2(0.0F, 0.0F);
		setRadius(25.0F); // the hitcircle of the black hole's body.
		radius2 = 50.0F; // the radius of the suction area of the black hole
		force2 = Vec2(50.0F, 50.0F); // the force that's used to draw in other ships.
		
		break;
	// Planet
	case 4:
		setTexture("images/planet.png");
		setMass(4.0F);
		setMaxHealth(1); // health of 1
		setHealth(getMaxHealth());
		killable = false; // planets cannot be destroyed.
		setDamage(2);
		
		force = Vec2(100.0F, 100.0F);
		setConstVelocity(true);
		setScreenWrap(false); // the planets don't wrap around the screen.

		setRadius(25.0F);
		radius2 = 200.0F;
		setScale(1.5);
		actionTime = 2.0F; // a projectile is shot if the player is within range. The 'actionTime' controls the cooldown time that the planet has until it can fire again.
		timer = actionTime; // the planet is ready to fire a shot upon spawning

		break;

	// Shooter
	case 5:
		setTexture("images/enemy_ship_shooter.png");
		setMass(1.5F);
		setMaxHealth(2); // health of 1
		setHealth(getMaxHealth());

		setDamage(1.0F);
		setRadius(20.0F);
		radius2 = 500.0F;
		force = Vec2(0.0F, 0.0F);
		theta = umath::degreesToRadians(rand() % 361); // rotates the enemy's force by a random amount.

		actionTime = 1.0F; // the cooldown time for the shooter to fire at the enemy.
		timer = actionTime;
		break;

	// Kamikaze
	case 6:
		setTexture("images/enemy_ship_kamikaze_ss.png");
		crop = Rect(0.0F, 0.0F, 50.0F, 50.0F);
		getSprite()->setTextureRect(crop); // uses the first image.
		setMass(1.50F);

		setMaxHealth(2.0F); // health of 1
		setHealth(getMaxHealth());
		
		setDamage(1.0F);
		setRadius(25.0F);
		radius2 = 300.0F;
		setScale(1.5);

		force = Vec2(0.0F, 75.0F);
		theta = umath::degreesToRadians(rand() % 361); // rotates the enemy's force by a random amount.
		setConstVelocity(true);
		// setScreenWrap(false); // the kamikaze doesn't loop around the screen.
		actionTime = 1000.0F; // after this amount of time has 
		break;

	// Boss
	case 7:
		setTexture("images/boss_ss.png");
		crop = Rect(0, 0, 100, 100);
		getSprite()->setTextureRect(Rect(crop.getMaxX(), 0, crop.getMaxX(), crop.getMaxY())); // starts with green shield.
		setMass(5.0F);

		setRadius(50.0F);
		radius2 = 1000.0F; // the boss can shoot and the player regardless of their location.
		setScale(3.0F);

		setMaxHealth(3); // health of 3
		setHealth(getMaxHealth());
		maxShield = 25.0F;
		shield = maxShield;
		setDamage(1.0F);
		
		force = Vec2(0, 180.0F); // movement speed
		force2 = Vec2(0.0F, 30.0F); // this will be added to the ship's main force in the following phases.
		theta = umath::degreesToRadians(rand() % 361); // random rotation value to start.
		

		setConstVelocity(true);
		setScreenWrap(true);
		actionTime = 2.5F;
		timer = actionTime;

		break;

	// Projectile Type-1
	case 8:
		setTexture("images/projectile.png");
		setMass(0.5F);
		setMaxHealth(1); // health of 1
		setHealth(getMaxHealth());
		killable = true;
		setDamage(1); // damage given

		setRadius(5.0F);
		force = Vec2(0.0F, 45.0F);
		setScreenWrap(false);
		setConstVelocity(true);
		rotateLR = true;
		
		break;

	// Projectile Type-2
	case 9:
		setTexture("images/projectile3.png");
		setMass(0.5F);
		setMaxHealth(1);
		setHealth(getMaxHealth());
		killable = true;
		setDamage(2);

		setRadius(20.0F);
		force = Vec2(0.0F, 60.0F);
		setScreenWrap(false);
		setConstVelocity(true);

		break;

	// DUMMY (i.e. the enemy that shows up when there is no enemy)
	default:
		this->type = 0; // sets the 'type' to 0.
		setMaxHealth(1.0F);
		setHealth(getMaxHealth());

		
		force.x = 1.0F;
		force.y = 1.0F;
		setMass(0.001F);
		break;

	}
	
	// Determines what direction the enemy will be going.
	switch (type)
	{
	case 5: // shooter
	case 6: // kamikaze
	case 7:
	case 8: // projectile 1
	case 9: // projectile 2; direction for projectiles is determined based on something else.
		break;

	default: // makes the direction random.
		force.x *= (rand() % 2 == 0) ? -1 : 1;
		force.y *= (rand() % 2 == 0) ? -1 : 1;
	}


	rForce = umath::rotate(force, this->theta); // gets the force of the enemy, rotated by the enemy's theta value.
	// For the projectiles, their position is set outside of the defaults.
	// If the enemy is going left
	if (rForce.x < 0)
	{
		setPositionX(getWrapPointsMax().x + getWidth() / 2);
	}
	// If the enemy is going right
	else if (rForce.x > 0)
	{
		setPositionX(getWrapPointsMin().x - getWidth() / 2);
	}

	// If the enemy is going down
	if (rForce.y < 0)
	{
		setPositionY(getWrapPointsMax().y + getHeight() / 2);
	}
	// If the enemy is going up
	else if (rForce.y > 0)
	{
		setPositionY(getWrapPointsMin().y - getHeight() / 2);
	}

	// If the force is '0' for the enemy, it spawns randomly on screen, as it would be spawned off-screen and move iself on-screen otherwise.
	if (rForce.x == 0 && rForce.y == 0)
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

// returns the rectangle size of the enemy sprites
Rect Enemy::getCrop() { return crop; }

// sets the secondary radius of the enemy.
void Enemy::setSecondRadius(float radius2) { this->radius2 = radius2; }

// gets the secondary radius of the enemy.
float Enemy::getSecondRadius() { return radius2; }

// gets the second radius with the scale factor applied
void Enemy::setScaledSecondRadius(float scaledRadius) { radius2 = scaledRadius / getScale(); }

// sets the second radius with the scale factor applied
float Enemy::getScaledSecondRadius() { return radius2 * getScale(); }

// gets the variable 'force' stored in this class, which the enemines send to the 'entity' class to apply force every cycle.
Vec2 Enemy::getForce1() { return force; }

// sets the variable 'force' stored in this class, which the enemines send to the 'entity' class to apply force every cycle.
void Enemy::setForce1(Vec2 force1) { this->force = force1; }

// gets the second force that an enemy has. This force ISN'T used for movement, but something else.
Vec2 Enemy::getForce2() { return force2; };

// gets a secondary force. This force is reserved for operations regarding the enemy, movement not withstanding.
void Enemy::setForce2(Vec2 force2) { this->force2 = force2; }

// gets the enemy's current shield health
float Enemy::getShield() { return shield; }

// sets the enemy's current shield health
void Enemy::setShield(float shield) { this->shield = shield; }

// gets the enemy's maximum shield helath
float Enemy::getMaxShield() { return maxShield; }

// sets the enemy's maximum shield health
void Enemy::setMaxShield(float maxShield) { this->maxShield = maxShield; }

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

// if true, then the enemy's action is available to be used (if applicable). If false, the enemy can't use its action yet.
bool Enemy::actionAvailable() { return timer >= actionTime; }

// if called, the cooldown period for the enemy's specific action begins. While this is happening, the enemy cannot perform this action.
void Enemy::actionOcurred() { timer = 0.0F; }

// Update function for enemies.
void Enemy::update(float deltaTime)
{
	timer += deltaTime; // calculates how much time has passed since the last event determined by 'actionTime'
	// std::cout << "Type: " << type << std::endl;

	// 1. Small Asteroid , 2. Large Asteroid, 3. Black Hole, 4. Planets, 5. Enemy Ship - Shooter, 6. Enemy Ship - Kamikaze, 7. Boss, 8. Projectile 1, 9. Projectile 2
	// Black Holes
	switch (type)
	{
	case 3:
		if (getTime() > 10.0F) // if a whole second has passed, then the blackhole is removed.
		{
			setHealth(0); // sets the health of the 'blackhole' to '0' so that it is automatically deleted.
		}
		break;

	// Shooter Ship
	case 5:
		if (getTime() > 15.0F)
		{
			setHealth(0); // the shooter ship gets deleted automatically, since it's stationary.
		}
		break;

	// Kamikaze
	case 6:
		if (getTime() > 34.0F) // after this amount of time has passed, the kamikaze ship will no longer loop around the stage, making it despawn if it goes off screen.
		{
			setScreenWrap(false);
		}
		break;

	// BOSS
	case 7:
	
		if (shield <= 0.00F && getSprite()->getTextureRect().getMinX() != 100 * 0) // enemy sprite (no shield)
		{
			getSprite()->setTextureRect(crop);
		}
		else if (shield / maxShield > 0.00F && shield / maxShield <= 0.33F && getSprite()->getTextureRect().getMinX() != 100 * 3) // shield becomes red
		{
			getSprite()->setTextureRect(Rect(crop.getMaxX() * 3, crop.getMinY(), crop.getMaxX(), crop.getMaxY()));
		}
		else if (shield / maxShield > 0.33F && shield / maxShield <= 0.66F && getSprite()->getTextureRect().getMinX() != 100 * 2) // shield becomes yellow
		{
			getSprite()->setTextureRect(Rect(crop.getMaxX() * 2, crop.getMinY(), crop.getMaxX(), crop.getMaxY()));
		}
		else if (shield / maxShield > 0.66F && getSprite()->getTextureRect().getMinX() != 100) // shield becomes green
		{
			getSprite()->setTextureRect(Rect(crop.getMaxX(), crop.getMinY(), crop.getMaxX(), crop.getMaxY()));
		}

		// std::cout << "(" << sprite->getTextureRect().getMinX() << ", " << sprite->getTextureRect().getMinY() << ", " << sprite->getTextureRect().getMaxX() << ", " << sprite->getTextureRect().getMaxY() << ")" << std::endl;

		break;

	// Projectile 1 (used by planets and shooters)
	case 8:
		if (getTime() > 10.0F)
		{
			setHealth(0); // sets the health of the 'projectile' to '0' so that it is automatically deleted.
		}
		break;
	}

	addForce(force.x, force.y); // adds force to the standard force of the entity
	Entity::update(deltaTime);
}

