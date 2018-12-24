#include "Projectile.h"



Projectile::Projectile(Vec2 position, std::string imagePath, float radius, float theta, float LIFESPAN) : Entity(position, imagePath), LIFESPAN(LIFESPAN)
{
	
	setMass(1.0F);
	setRadius(radius);
	force.x = 0.0f;
	force.y = 10.0F;

	this->theta = theta;
	force = rotateEntity(force); // gives the entity its force, rotated by the ship's theta
	setConstVelocity(true);
}


Projectile::~Projectile()
{
}

// The update of the projectile
void Projectile::update(float deltaTime)
{
	addForce(force.x, force.y);
	Entity::update(deltaTime);
}
