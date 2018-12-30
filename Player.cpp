// Class for the character
#include "Player.h"
// #include tags

// Defaults: Vec2 position, std::string spritePath, float scale = 1.0F, float MAXVELOCITY = 50.0F, float DECELRATE = 0.95F
Player::Player(Vec2 position, std::string imagePath, const int MAXHEALTH, const float APPLIEDFORCE, const float RECOVERTIME) : Entity(position, imagePath, 1.0F, 12.0F, 0.95F, 4.00F), APPLIEDFORCE(APPLIEDFORCE), RECOVERTIME(RECOVERTIME)
{
	getSprite()->setTextureRect(crop); // tells the program to only use the first item in the sprite sheet, being the ship itself.
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

// sets the size of the rectangle used to crop the texture (image) of the player
Rect Player::getRectSize() { return crop; }

// sets the size of the rectangle used to crop the texture (image) of the player
void Player::setRectSize(Rect crop) { this->crop = crop; }

playerState Player::getState() { return state; }

void Player::setState(playerState newState) { state = newState; }

float Player::getAppliedForce() { return APPLIEDFORCE; }

int Player::getScore() { return score; }

void Player::setScore(int score) { this->score = score; }

void Player::increaseScore(int increase) { score += increase; }

int Player::getLives() { return lives; }

void Player::setLives(int lives) { this->lives = lives; }

// saves the time the player took damage at, and makes them unkillable for the time being.
void Player::playerHit() 
{ 
	getSprite()->setTextureRect(Rect(crop.getMinX() + crop.getMaxX(), crop.getMinY(), crop.getMaxX(), crop.getMaxY())); // turns on shield
	timeHit = getTime();
	setOpacityPercentage(0.5F);
	killable = false;
}

void Player::update(float deltaTime)
{
	// timeHit = getTime(); //  uncomment to make the ship invincible.

	// if the player isn't killable, it checks to see if their recovery time has ended. If so, the player is made killable.
	if (!killable && getTime() - timeHit >= RECOVERTIME)
	{
		getSprite()->setTextureRect(crop); // turning off the sheild.
		killable = true;
		setOpacityPercentage(1.0F);
	}
	Entity::update(deltaTime); // calls the entity update function
}
