#pragma once
#include "cocos2d.h"

#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Projectile.h"
#include "UtilityMath.h"

#include <vector>


using namespace cocos2d;

typedef class A3_GameplayScene : public Scene
{
public:
	A3_GameplayScene();

	// The floats are extras that I added so that the scene could have the screen's size
	static Scene* createScene();
	static Scene* createScene(float width, float height);

	// called when the scene is entered
	void onEnter();
	
	// init functions
	bool init(); // what's called when the Cocos2D-X scene is created.
	void initListeners(); // initalizes event handlers
	// void initMouseListener();
	void initKeyboardListener();
	// void initContactListener();
	// void initPauseMenu();
	void initSprites();
	// void initObstacles();
	// void initPigs();

	//Callbacks
	// void mouseDownCallback(Event* event);
	// void mouseUpCallback(Event* event);
	// void mouseMoveCallback(Event* event);
	// void mouseScrollCallback(Event* event);
	void keyDownCallback(EventKeyboard::KeyCode keyCode, Event* event); // if a key is held down
	void keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event); // if a key is let go
	// bool onContactBeginCallback(PhysicsContact& contact); // listening for hit detection (which we're not supposed to use)

	// General update
	void update(float deltaTime);

	// void updateInputs(); // updates all inputs
	// void updateKeyboardInputs(); // updates all keyboard inputs
	
	CREATE_FUNC(A3_GameplayScene);

protected:
	// Spawns an enemy. If no enemy object is passed, a random enemy is chosen.
	void spawnEnemy(Enemy * enemy = Enemy::getRandEnemy());
	// Spawns an enemy based on the type passed. A prototype enemy will be used if an invalid type is passed.
	void spawnEnemy(unsigned short int type);

	void updatePlayer(float deltaTime);
	void updateEnemies(float deltaTime);
	void updateProjectiles(float deltaTime);
	void collisions(); // handles all collisions


private:
	// Engine
	Director * director;
	Label * scoreLabel;
	DrawNode * hpNode;

	// the screen's width and height
	static float screenWidth;
	static float screenHeight;

	//Background Sprite
	Sprite* spr_BG;
	Sprite* spr_BG2; // unneeded?

	// Vectors and player objects
	Player * pShip;
	// Enemy * smallAsteroid;
	// Enemy * largeAsteroid;
	// Enemy * planet;
	// Enemy * shooter;
	// Enemy * kamikaze;

	std::vector<Enemy*> enemies;
	std::vector<Projectile*> projectiles;
	std::vector<Item*> items;

	bool upKey = false;
	bool downKey = false;
	bool leftKey = false;
	bool rightKey = false;
	bool spaceBar = false;

	// Records the totaled delta timer across 'x' amount of frames.
	float timer = 0;
	// The player's score


	//Event listeners
	// EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;

} GameplayScene;




