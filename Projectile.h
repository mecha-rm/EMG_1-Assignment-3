#pragma once
#include "Entity.h"
#include "cocos2d.h"

class Projectile : public Entity
{
public:
	Projectile(Vec2 position, std::string imagePath, float radius, float theta = 0.0F, float LIFESPAN = -1.0F);
	~Projectile();

	void update(float deltaTime);

	// Used to mesure how long its been since the projectile was on screen
	float timer = 0;
	// The amount of force the projectile has has.
	Vec2 force;
	// the amount of damage an entity does.
	float damage = 0;
	// the amount of times the projectile can hit something without disappearing
	float health = 0; 

	// Tells the timer when to delete the entity. A negative number will not cause an entity to be deleted, regardless of the time.
	const float LIFESPAN = -1.0F;
};

