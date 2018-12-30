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
	// Player's position, the file path to their image, the base force, and how much time it takes for the invincibility frames to ware off
	Player(Vec2 position, std::string imagePath = "images/player_ship_ss.png", const int MAXHEALTH = 4, const float APPLIEDFORCE = 150.0F, const float RECOVERTIME = 2.0F);
	// Player(Player*);

	playerState getState();
	void setState(playerState newState);
	
	// sets the size of the rectangle used to crop the texture (image) of the player
	Rect getRectSize();

	// sets the size of the rectangle used to crop the texture (image) of the player
	void setRectSize(Rect crop);

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

	// called when the player is it. It saves at what time internally this occurred, and makes the player unkillable.
	void playerHit();

	void update(float deltaTime);

	int score = 0; // the player's score
	int lives = 2; // life 0 is a thing

protected:
	// Used to crop the sprite sheet. It's equal to the first player image by default.
	Rect crop = Rect(0.0F, 0.0F, 40.0F, 40.0F);

private:
	playerState state;
	
	float timeHit; // saves at what time the player was hit for the invincibility frames.
	const float RECOVERTIME = 0.0F; // how long it takes for the ship's invincibility frames to end.
	const float APPLIEDFORCE; // force for the player when they move. It's only one float because they move the same speed regardless of the axis.
};

