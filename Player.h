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
	Player(Vec2 position, std::string imagePath = "images/player_ship.png", const int MAXHEALTH = 4, const float APPLIEDFORCE = 200.0F);
	// Player(Player*);

	playerState getState();
	void setState(playerState newState);
	// gets the base force of the player. This is the amount of force applied every button press.
	float getAppliedForce();

	// gets the player's score
	int getScore();
	// sets the player's score
	void setScore(int score);
	// increases the player's score
	void increaseScore(int increase);

	// gets the amount of lives the player has
	int getLives();
	// sets the amount of lives the player has
	void setLives(int lives);

	void update(float deltaTime);

	int score = 0;
	int lives = 3;

protected:

private:
	playerState state;
	
	const float APPLIEDFORCE; // force for the player when they move. It's only one float because they move the same speed regardless of the axis.
};

