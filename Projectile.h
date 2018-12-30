#pragma once
#include "Entity.h"
#include "cocos2d.h"

class Projectile : public Entity
{
public:
	// Position, image, radius, rotation factor, the amount of damage it does, and how long the entity will stay on screen. A negative value will make the projectile unable to be deleted by time.
	Projectile(Vec2 position, std::string imagePath, float speed, float radius, float theta = 0.0F, float damage = 1.0, float LIFESPAN = -1.0F);
	~Projectile();

	void update(float deltaTime);

	// Used to mesure how long its been since the projectile was on screen
	float timer = 0;

	// The amount of force the projectile has has. This saves the amount of force the projectile applies each frame.
	Vec2 force;

	// Tells the timer when to delete the entity. A negative number will not cause an entity to be deleted, regardless of the time.
	const float LIFESPAN = -1.0F;
};

