// The player object
#pragma once
#include "Entity.h"

enum playerState
{
	normal, // normal state; no power-ups or effects
	reverse, // reversed controls
	grapple, // grappling hook gravity
	spin // random spinning
};

class Player : public Entity
{
public:
	// Player's position, the file path to their image, and they're base force
	Player(Vec2 position, std::string imagePath = "images/player_ship.png", const float APPLIEDFORCE = 200.0F);
	// Player(Player*);

	playerState getState();
	void setState(playerState newState);
	// gets the base force of the player. This is the amount of force applied every button press.
	float getAppliedForce();

	// gets the player's health
	int getHealth();
	// gets the player's maximum health
	int getMaxHealth();
	// gets the player's score
	unsigned int getScore();

	void update(float deltaTime);

protected:
	void setHealth(int health);
	void setScore(unsigned int score);

private:
	playerState state;
	const float APPLIEDFORCE; // force for the player when they move. It's only one float because they move the same speed regardless of the axis.

	int health = 3;
	const float MAXHEALTH = 3;
	unsigned int score = 0;
};

