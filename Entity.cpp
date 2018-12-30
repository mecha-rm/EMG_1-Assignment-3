#include "Entity.h"
#include "UtilityMath.h"

#include <cmath>
#include <random>

// #include "spine/extension.h" // allows the use of 'PI'
// #define M_PI 3.14159265358979323846   // pi

Vec2 Entity::wrapPointsMin = Vec2(0.0F, 0.0F);
Vec2 Entity::wrapPointsMax = Vec2(0.0F, 0.0F);

Entity::Entity() : Entity(Vec2(0, 0), "images/DUMMY.png") {}

// Entity::Entity(Entity* entity) { *this = entity; }

Entity::Entity(Vec2 position, std::string spritePath, float scale, float MAXVELOCITY, float DECELERATE, float maxHealth) : MAXVELOCITY(MAXVELOCITY), DECELERATE(DECELERATE)
{
	sprite = Sprite::create(spritePath); // loads the handle
	setPosition(position);
	setScale(scale); // sets the sprite's scale; also records the sprite's width, height, and centre.
	setAnchorPoint(Vec2(0.5, 0.5)); // ensures the image is at the middle of its anchor point

	// setting health
	setMaxHealth(maxHealth);
	setHealth(getMaxHealth());

	// computes the starting corners
	startingCorners[0] = Vec2(centre.x - width / 2, centre.y + height / 2); // top left
	startingCorners[1] = Vec2(centre.x + width / 2, centre.y + height / 2); // top right
	startingCorners[2] = Vec2(centre.x - width / 2, centre.y - height / 2); // bottom left
	startingCorners[3] = Vec2(centre.x + width / 2, centre.y - height / 2); // bottom right
	
	// computes the current corners.
	currentCorners[0] = startingCorners[0];
	currentCorners[1] = startingCorners[1];
	currentCorners[2] = startingCorners[2];
	currentCorners[3] = startingCorners[3];
}

// Gets a pointer to the sprite
Sprite* Entity::getSprite() { return sprite; }

// Sets a new sprite (as a pointer).
void Entity::setSprite(Sprite * sprite)
{
	this->sprite = sprite;
	setPosition(sprite->getPosition());
	setScale(sprite->getScale()); // sets the scale of the sprite so that the height and width are updated.
}

// Sets the opacity of the sprite using a percentage. The sprite's built in opacity ranges from 0 to 255.
void Entity::setOpacityPercentage(float opacity)
{
	if (opacity > 1.0F) // setting the opacity to 100% if it's over 100%.
	{
		opacity = 1.0F;
	}
	else if (opacity < 0.0F) // setting the opacity to '0' if the value given is less than 0%.
	{
		opacity = 0.0F;
	}

	sprite->setOpacity(255 * opacity); // setting the sprite's new opacity.
}

// Gets the opacity of the sprite as a percentage. The sprite's built in opacity ranges from 0 to 255.
float Entity::getOpacityPercentage() { return sprite->getOpacity() / 255; }

// sets the texture of the sprite with an image path
void Entity::setTexture(std::string filePath) { sprite->setTexture(filePath); }

// sets the texture of the sprite with a texture 2d object
void Entity::setTexture(Texture2D * texture) { sprite->setTexture(texture); }

// gets the sprite's texture
Texture2D * Entity::getTexture() { return sprite->getTexture(); }

// sets the texture (image) of the sprite. This does the same as setTexture();
void Entity::setImage(std::string imagePath) { setTexture(imagePath); }

// PhysicsBody* Entity::getBody() { return sprite->getPhysicsBody(); }

// Get Sprite Position
Vec2 Entity::getPosition() { return sprite->getPosition(); }

// changing the sprite's position
void Entity::setPosition(Vec2 position)
{
	sprite->setPosition(position);
	// *x = sprite->getPositionX();
	// *y = sprite->getPositionY();
}

// Gets and sets positions on the 'x'
float Entity::getPositionX() { return sprite->getPositionX(); }

void Entity::setPositionX(float x) { sprite->setPosition(x, sprite->getPositionY()); }

// gets and sets position on the 'y'
float Entity::getPositionY() { return sprite->getPositionY(); }

void Entity::setPositionY(float y) { sprite->setPosition(sprite->getPositionX(), y); }

// gets the sprite's width
float Entity::getWidth() { return width; }

// gets the sprite's original width
float Entity::getDefaultWidth() { return sprite->getContentSize().width; }

// gets the sprite's height
float Entity::getHeight() { return height; }

// gets the sprite's defeault height, which is the height of the image file
float Entity::getDefaultHeight() { return sprite->getContentSize().height; }

// gets the centre of the sprite
Vec2 Entity::getCentre() { return centre; }

// gets the centre of the sprite at its current scale
Vec2 Entity::getDefaultCentre()
{
	Vec2 tempCentre;
	// gets the centre of the sprite
	tempCentre.x = getDefaultWidth() / 2;
	tempCentre.y = getDefaultHeight() / 2;
	return tempCentre;
}

// gets a corner by number
const Vec2 Entity::getCorner(int corner)
{
	if (corner > 0 && corner <= 4) // there are 4 corners
		return currentCorners[corner - 1]; // returns the corner

	return Vec2(0, 0); // returns a vector of (0, 0) if the index is outside of the range 
}

// Gets the corners of the entity
const Vec2 * Entity::getCorners() { return currentCorners; }

// Finds the 4 corners of each sprite, assuming that the centre point, width, and height are all accurate.
void Entity::recomputeCorners()
{
	// c1 > top left, c2 > top right, c3 > bottom left, c4 > bottom right
	currentCorners[0] = Vec2(centre.x - width / 2, centre.y + height / 2); // top left
	currentCorners[1] = Vec2(centre.x + width / 2, centre.y + height / 2); // top right
	currentCorners[2] = Vec2(centre.x - width / 2, centre.y - height / 2); // bottom left
	currentCorners[3] = Vec2(centre.x + width / 2, centre.y - height / 2); // bottom right
}

// Rotates the entity by the member variable 'theta', which is in degrees. It also uses a passed vector object to determine the direction of the object.
Vec2 Entity::rotateEntity(Vec2 direcVec) {return rotateEntity(theta, direcVec); }

// Rotates the entity by a factor provided in degrees
Vec2 Entity::rotateEntity(float theta, Vec2 direcVec)
{	// degrees to radians - 1 degree = pi/180 radians. 
	// radians to degrees - 1 radian = 180/pi degrees.
	
	Vec2 pastPos = sprite->getPosition(); // saves the previous position.

	// M_PI; // Pi

	// Rotates Entity
	cocos2d::Mat4 rotation = Mat4::IDENTITY;
	rotation.translate(cocos2d::Vec3(sprite->getCenterRect().size.width * sprite->getAnchorPoint().x, sprite->getCenterRect().size.height * sprite->getAnchorPoint().y, 0.0F)); // makes it rotate on its centre
	rotation.rotateZ(-theta); // rotates the entity; cocos uses degrees
	rotation.translate(-cocos2d::Vec3(sprite->getCenterRect().size.width * sprite->getAnchorPoint().x, sprite->getCenterRect().size.height * sprite->getAnchorPoint().y, 0.0F)); // moves it back

	// sprite->setPosition(0.0F, 0.0F); // moves the sprite back to the centre for rotation
	sprite->setAdditionalTransform((cocos2d::Mat4*)(&rotation)); // rotates the image of the entity.
	// sprite->setPosition(pastPos); // sets the position back to where it was.
	
	// The position is based on the middle of the entity.
	// acceleration = umath::rotate(acceleration, Vec2(0.0F, 0.0F), -theta); // rotates the entity's velocity
	return umath::rotate(direcVec, -theta);
}

// Gets whether the object wraps the screen or not.
bool Entity::getScreenWrap() { return screenWrap; }

// Sets whether the object wraps the screen or not.
void Entity::setScreenWrap(bool screenWrap) { this->screenWrap = screenWrap; }

// gets the minimum wrapping points (x, y)
Vec2 Entity::getWrapPointsMin() { return wrapPointsMin; }

// sets the minimum wrappings points (x, y)
void Entity::setWrapPointsMin(Vec2 wrapPoints) { wrapPointsMin = wrapPoints; }

// gets the maximum wrapping points (x, y)
Vec2 Entity::getWrapPointsMax() { return wrapPointsMax; }

// gets the maximum wrapping points (x, y)
void Entity::setWrapPointsMax(Vec2 wrapPoints) { wrapPointsMax = wrapPoints; }

// returns sprite's scale
float Entity::getScale() { return sprite->getScale(); }

// Set sprite's scale
void Entity::setScale(float scl) { 
	sprite->setScale(scl); 

	// Getting the sprite's new width and height, accounting for the scale factor
	Size size = sprite->getContentSize();
	width = size.width * sprite->getScaleX();
	height = size.height * sprite->getScaleY();

	// gets the centre of the sprite
	centre.x = width / 2;
	centre.y = height / 2;
}

//  gets the sprite's anchor point
void Entity::setAnchorPoint(Vec2 anchor) { sprite->setAnchorPoint(anchor); }

// sets the sprite's anchor point
Vec2 Entity::getAnchorPoint() { return sprite->getAnchorPoint(); }

// Gets sprite's radius
float Entity::getRadius() { return radius; }

// Sets sprite's radius
void Entity::setRadius(float radius) { this->radius = radius; }

// Gets the radius with the sprite's scale applied.
float Entity::getScaledRadius() { return radius * getScale(); }

// sets the scaled radius.
void Entity::setScaledRadius(float scaledRadius) { radius = scaledRadius / getScale(); }

// getter and setter for mass
float Entity::getMass() { return mass; }

void Entity::setMass(float mass) { this->mass = mass; }

// getter for force
Vec2 Entity::getForce() { return force; }

// alternate setter for force
void Entity::setForce(float x, float y) { setForce(Vec2(x, y)); }

// setter for force
void Entity::setForce(Vec2 force) { this->force = force; }

// adds force
void Entity::addForce(float x, float y)
{
	force.x += x;
	force.y += y;
}

// gets the current velocity of the entity
Vec2 Entity::getVelocity() { return velocity; }

// sets the current velocity of the entity
void Entity::setVelocity(Vec2 velocity) { this->velocity = velocity; }

// sets the current velocity of the entity
void Entity::setVelocity(float x, float y) { velocity = Vec2(x, y); }

// adds to the entity's velocity
void Entity::addVelocity(float x, float y) { velocity += Vec2(x, y); }

// gets the speed limit
bool Entity::getSpeedLimiter() { return speedLimiter; }

// sets the speed limit
void Entity::setSpeedLimiter(bool speedLimiter) { this->speedLimiter = speedLimiter; }

// toggles the speed limit on/off
void Entity::setSpeedLimiter() { speedLimiter = !speedLimiter; }

// gets whether there's constant velocity 
bool Entity::getConstVelocity() { return constVelocity; }

// turns constant velocity on/off
void Entity::setConstVelocity(bool constVelocity) { this->constVelocity = constVelocity; }

// gets the current health of the entity
float Entity::getHealth() { return currentHealth; }

// sets the health of the enemy.
void Entity::setHealth(float currentHealth) { this->currentHealth = currentHealth; }

// gets the current health of the entity using getHealth()
float Entity::getCurrentHealth() { return getCurrentHealth(); }

// gets the max health
float Entity::getMaxHealth() { return maxHealth; }

// sets the maximum heatlh
void Entity::setMaxHealth(float maxHealth) { this->maxHealth = maxHealth; }

// gets the amount of damage an entity gives out
float Entity::getDamage() { return damage; }

// sets the amount of damage an entity takes
void Entity::setDamage(float damage) { this->damage = damage; }

// If 'true' then the entity can be destroyed. If 'false', then the entity cannot be destroyed.
bool Entity::getKillable() { return killable; }

// Sets whether an entity can be destroyed or not.
void Entity::setKillable(bool killable) { this->killable = killable; }

// Toggles on/off the 'killable' parameter for the enemy.
void Entity::setKillable() { killable = !killable; }

// returns how long an entity has existed for.
float Entity::getTime() { return timer; }

// updates the sprite
void Entity::update(float deltaTime)
{
	Vec2 position(sprite->getPosition());

	// Getting the current acceleration. Acceleration is equal to the current amount of force being applied, divided by the mass of the object.
	
	acceleration = force / mass;
	
	if (rotateLR) // controls whether the entity will rotate or not when certain buttons are pressed.
	{
		acceleration = rotateEntity(acceleration);
		// acceleration = rotateEntity(acceleration.getNormalized()) * (250); // rotates entity
		// position = sprite->getPosition(); // gets the sprite's position, since it has been effected from the rotation
	}
	
	velocity += acceleration * deltaTime;
	//  spaceShip->velocity += Vector3(-sinf(spaceShip->theta / 180 * M_PI), cosf(spaceShip->theta / 180 * M_PI), 0.0f) * dt * rotateScalar

	// Setting the ship's maximum speed. How the velocity is set needs to be altered.
	
	// The ship may end up stuttering slightly at some points
	// Prevents the entity from going any faster
	if (speedLimiter == true)
	{
		if (abs(velocity.x * deltaTime) > MAXVELOCITY)
		{
			(velocity.x > 0) ? velocity.x = MAXVELOCITY / deltaTime : velocity.x = -MAXVELOCITY / deltaTime;
		}
		if (abs(velocity.y * deltaTime) > MAXVELOCITY)
		{
			(velocity.y > 0) ? velocity.y = MAXVELOCITY / deltaTime : velocity.y = -MAXVELOCITY / deltaTime;
		}
	}
	
	// Slowing the ship down if no force is being applied
	if (SLOWDOWN)
	{
		// 'x' direction
		if (acceleration.x == 0 && velocity.x != 0)
		{
			velocity.x *= DECELERATE;
			if (abs(velocity.x * deltaTime) <= FORCESTOP)
				velocity.x = 0;
		}
		// 'y' direction
		if (acceleration.y == 0 && velocity.y != 0)
		{
			velocity.y *= DECELERATE;
			if (abs(velocity.y * deltaTime) <= FORCESTOP)
				velocity.y = 0;
		}
	}
	
	/*
	if (rotateLR) // controls whether the entity will rotate or not when certain buttons are pressed.
	{
		rotateEntity(); // rotates entity
		position = sprite->getPosition(); // gets the sprite's position, since it has been effected from the rotation
	}
	*/

	// Getting the current position. Position = Previous Position + Velocity * Delta Time (Time Passed)
	if (!constVelocity) // if false, the entity constantly accelerates
	{
		position.x += velocity.x * deltaTime;
		position.y += velocity.y * deltaTime;
	}
	else // has the entity travel at the same velocity each timer.
	{
		position += acceleration * deltaTime;
	}
	

	// Wraparound for the entity; if true, screen wrapping occurs, but only if the maximum and minimum wrap points are not the same.
	// If false, the entity is deleted once it fully leaves the screen.
	
	// The location used for the sprite is its center
	// This wraps the sprite around the screen. It only shows up on wone side of the screen once it leaves  the screen completely.
	if (screenWrap && wrapPointsMin != wrapPointsMax)
	{
		if (position.x <= wrapPointsMin.x - width / 2) // going through the left side of the screen
		{
			position.x = wrapPointsMax.x + width / 2;
		}
		else if (position.x >= wrapPointsMax.x + width / 2) // going through the right side of the screen
		{
			position.x = wrapPointsMin.x - width / 2;
		}

		// but for this example, just checking if we are at a particular pixel location on Y is fine....
		// y-axis
		if (position.y <= wrapPointsMin.y - height / 2) // going through the bottom of the screen.
		{
			position.y = wrapPointsMax.y + height / 2;
		}
		else if (position.y >= wrapPointsMax.y + height / 2) // going through the top of the screen.
		{
			position.y = wrapPointsMin.y - height / 2;
		}
	}
	// If screenwrap is turned off and there are set minimum and maximum wrapping points, then the entity gets deleted if it leaves these bounds
	else if (!screenWrap && wrapPointsMin != wrapPointsMax)
	{
		if ((position.x <= wrapPointsMin.x - width / 2 ^ position.x >= wrapPointsMax.x + width / 2) || (position.y <= wrapPointsMin.y - height / 2 ^ position.y >= wrapPointsMax.y + height / 2))
		{
			currentHealth = 0.0F; // a health of '0' causes an entity to get deleted.
			// delete this;
		}
		
	}
	sprite->setPosition(position); // setting the sprite's position
	setForce(0.0f, 0.0f); // setting the force to (0, 0)
	
	timer += deltaTime; // adds to the timer
}

Entity::~Entity()
{
	// removes the sprite from the draw list upon deletion
	// sprite->runAction(RemoveSelf::create());
	// sprite = NULL;
}