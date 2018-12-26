// Base class that all entitys inherit from
#pragma once
#include "cocos2d.h"

#include <string>

using namespace cocos2d;

class Entity
{
public:
	Entity();
	// Entity(Entity*);
	// Creating an entity, setting its position, image, scale, maximum velocity, and deceleration rate respectively
	Entity(Vec2 position, std::string spritePath, float scale = 1.0F, float MAXVELOCITY = 50.0F, float DECELRATE = 0.95F, float maxHealth = 1.00F);
	
	virtual ~Entity();
	// virtual ~Entity();

	// Sprite getter
	Sprite* getSprite();
	// Sprite setter
	void setSprite(Sprite*);
	// PhysicsBody* getBody();
	
	// gets the texture (image) of the sprite. Both do the same thing.
	void setTexture(std::string filePath);
	void setTexture(Texture2D * texture);
	Texture2D * getTexture();
	void setImage(std::string imagePath);

	// getting the sprite's position
	Vec2 getPosition();
	// changing the sprite's position
	void setPosition(Vec2 position);
	
	// Positions, and sprite's current size
	float getPositionX();
	void setPositionX(float x);
	float getPositionY();
	void setPositionY(float y);

	// gets the sprite's current width
	float getWidth();
	// gets the default width of the sprite, which would be the size of the image file
	float getDefaultWidth();
	// gets the sprite's current height, and its default height
	float getHeight();
	// gets the default height of the sprite, which would be the size of the image file
	float getDefaultHeight();
	// gets the centre of the sprite at its current scale. This is in-reference to the size of the sprite, and is NOT the same as the sprite's position.
	Vec2 getCentre();
	// gets the default centre of the sprite. This is in-reference to the size of the sprite, and is NOT the same as the sprite's position.
	Vec2 getDefaultCentre();

	// Returns a specific, current corner. This uses a number from 1 to 4.
	// top left (c1), top right (c2), bottom left (c3), bottom right (c4)
	const Vec2 getCorner(int corner);
	// Gets the current corners of the entity
	const Vec2 * getCorners();
	// Finds the 4 corners of each sprite, assuming that the centre point is accurate.
	void recomputeCorners();
	// rotates the entity using the member variable theta, calculating the entity's new image and direction. Returns a new Vec2 for the direction of the entity
	Vec2 rotateEntity(cocos2d::Vec2 direcVec);
	// Rotates the entity by a certain amount (in degrees), calculating the entity's new image and direction. Returns a new Vec2 for the new direction of the entity.
	Vec2 rotateEntity(float theta, cocos2d::Vec2 direcVec);

	// Gets whether the object wraps the screen or not.
	bool getScreenWrap();
	// Sets whether the object wraps the screen or not. If the maximum and minimum screen wrapping points are the same, no screen wrapping occurs.
	void setScreenWrap(bool screenWrap);
	// gets the minimum wrapping points (x, y)
	static Vec2 getWrapPointsMin();
	// sets the minimum wrappings points (x, y)
	static void setWrapPointsMin(Vec2 wrapPoints);
	// gets the maximum wrapping points (x, y)
	static Vec2 getWrapPointsMax();
	// gets the maximum wrapping points (x, y)
	static void setWrapPointsMax(Vec2 wrapPoints);

	// changing the sprite's scale
	float getScale();
	void setScale(float);

	// setting the sprite's anchor point
	void setAnchorPoint(Vec2 anchor);
	Vec2 getAnchorPoint();

	// gets the sprite's default radius. This does not take into account the sprite's scale, and assumes that it has a scale of 1.0. 
	float getRadius();
	// sets the sprite's default radius. This is the sprite's radius at scale 1.0, which would be the default size of the sprite.
	void setRadius(float radius);
	// gets the scaled radius of the entity. This is the radius of the entity at its current scale.
	float getScaledRadius();
	// sets the scaled radius of the entity. This is the radius of the entity at its current scale. This will change if the scale of the sprite is changed.
	void setScaledRadius(float scaledRadius);

	// mass
	float getMass();
	void setMass(float mass);

	// force
	Vec2 getForce();
	void setForce(float x, float y);
	void setForce(Vec2 force);
	void addForce(float x, float y);

	// velocity
	// gets the current velocity of the entity
	Vec2 getVelocity();
	// sets the current velocity of the entity
	void setVelocity(Vec2 velocity);
	// sets the current velocity of the entity
	void setVelocity(float x, float y);
	// adds to the entity's current velocity
	void addVelocity(float x, float y);

	// Gets the current health of the entity
	float getHealth();
	// sets the current health of the entity
	void setHealth(float currentHealth);

	// Gets the current health of the entity; same as getHealth();
	float getCurrentHealth();
	// gets the maximum health an enemy can have
	float getMaxHealth(); 

	// gets the damage an entity gives out
	float getDamage();
	// sets the damage an entity gives out
	void setDamage(float damage);

	// Updates the entity's positon.
	void update(float deltaTime);
	// Gets te amount of time the entity has existed for.
	float getTime();

	float theta = 0.0F; // the rotation factor of the entity
	bool rotateLR; //makes the ship rotate when left and right are pressed.

protected:
	// speed limiter getter
	bool getSpeedLimiter();
	// speed limiter setter
	void setSpeedLimiter(bool speedLimiter);
	// speed limiter toggle (auto. ON/OFF)
	void setSpeedLimiter();

	// gets whether there's constant velocity
	bool getConstVelocity();
	// turns on/off constant velocity. When on, the enity moves by the same amount every frame.
	void setConstVelocity(bool constVelocity);
	
	// sets the maximum health
	void setMaxHealth(float maxHealth);

private:
	static Vec2 wrapPointsMin; // the minimum wrapping points for the x and y axes (screen 9s)
	static Vec2 wrapPointsMax; // the maximum wrapping points for the x and y axes (screen length and width)

	Sprite* sprite;
	// float *x, *y;
	float width = 0;
	float height = 0;
	float radius = 0; // the radius of the hit circle. Collision takes into account the scale factor of the character.
	Vec2 centre; // the centre of the sprite at its current size.
	bool screenWrap = true; // loops the screen for the entity

	float mass = 1.0;
	Vec2 force = Vec2(0.0f, 0.0f);
	Vec2 acceleration = Vec2(0.0f, 0.0f);
	Vec2 velocity = Vec2(0.0f, 0.0f);
	bool constVelocity = false; // makes it so that the entity only has one speed.

	bool speedLimiter = true; // limits how fast the entity can go
	const float DECELERATE; // decelerates the ship 
	// Making this 'const' causes a problem
	const float MAXVELOCITY; // the fastest the ship can go.

	bool SLOWDOWN = true; // forces the entity to slow down
	const float FORCESTOP = 0.001; // forces the ship to stop after dropping below a certain speed

	float currentHealth = 1; // the health of the entity
	float maxHealth = 1; // the max amount of health the entity can have
	float damage = 0;

	// top left (c1), top right (c2), bottom left (c3), bottom right (c4)
	const int CORNERS = 4;
	Vec2 currentCorners[4]; // the current corners of the sprite
	Vec2 startingCorners[4]; // the starting corners of the sprite

	float timer = 0.0F; // counts how long an entity has existed for.
};

