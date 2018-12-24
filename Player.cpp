// Class for the character
#include "Player.h"
// #include tags

// Defaults: Vec2 position, std::string spritePath, float scale = 1.0F, float MAXVELOCITY = 50.0F, float DECELRATE = 0.95F
Player::Player(Vec2 position, std::string imagePath, const float APPLIEDFORCE) : Entity(position, imagePath, 1.0F, 10.0F, 0.95F, 4.00F), APPLIEDFORCE(APPLIEDFORCE)
{
	state = playerState::normal;
	setScale(0.8F); // scales sprite
	setScreenWrap(true); // setting the screen wrap to true.
	setConstVelocity(false); // the player doesn't have a constant velocity
	setRadius(20.0F);
	
	setHealth(getMaxHealth()); // health of '4'
	setDamage(0.00F);
}

// Player::Player(Player * player) { *this = player; };

playerState Player::getState() { return state; }

void Player::setState(playerState newState) { state = newState; }

float Player::getAppliedForce() { return APPLIEDFORCE; }

int Player::getHealth() { return health; }

void Player::setHealth(int health) { this->health = health; }

int Player::getMaxHealth() { return MAXHEALTH; }

unsigned int Player::getScore() { return score; }

void Player::setScore(unsigned int score) { this->score = score; }

void Player::update(float deltaTime)
{
	Entity::update(deltaTime); // calls the entity update function
}
