// Class for the character
#include "Player.h"
// #include tags

// Defaults: Vec2 position, std::string spritePath, float scale = 1.0F, float MAXVELOCITY = 50.0F, float DECELRATE = 0.95F
Player::Player(Vec2 position, std::string imagePath, const int MAXHEALTH, const float APPLIEDFORCE) : Entity(position, imagePath, 1.0F, 10.0F, 0.95F, 4.00F), APPLIEDFORCE(APPLIEDFORCE)
{
	state = playerState::normal;

	setMaxHealth(MAXHEALTH);
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

int Player::getScore() { return score; }

void Player::setScore(int score) { this->score = score; }

void Player::increaseScore(int increase) { score += increase; }

int Player::getLives() { return lives; }

void Player::setLives(int lives) { this->lives = lives; }

void Player::update(float deltaTime)
{
	// std::cout << "(" << getVelocity().x << ", " << getVelocity().y << ")" << std::endl;
	Entity::update(deltaTime); // calls the entity update function
}
