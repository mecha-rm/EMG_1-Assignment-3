#include "Projectile.h"


// Position, image, radius, rotation factor, and how long the entity will stay on screen. A negative value will make the projectile unable to be deleted by time.
Projectile::Projectile(Vec2 position, std::string imagePath, float speed, float radius, float theta, float damage, float LIFESPAN) : Entity(position, imagePath), LIFESPAN(LIFESPAN)
{
	getSprite()->setAnchorPoint(Vec2(0.5F, 0.5F));
	getSprite()->setGlobalZOrder(1); // the projectiles spawn below thes ships.

	// rotateLR = true; // has the projectile rotate based on the theta value. This makes it continue in the same direction it started in.
	setDamage(damage);
	setMass(1.0F);
	setRadius(radius);

	this->theta = theta;
	force = rotateEntity(theta, Vec2(0.0F, speed)); // saves the projectile's force, rotated by the ship's theta so that it goes in the right direction.
	rotateLR = false; // turning the rotations off since the 'force' already accounts for them. This stops it from being rotated an additional time each frame.
	
	setConstVelocity(true);
}


Projectile::~Projectile()
{
}

// The update of the projectile
void Projectile::update(float deltaTime)
{
	setForce(force.x, force.y); // sends over the projectile's force so that it can be moved in the update.
	Entity::update(deltaTime);
}
