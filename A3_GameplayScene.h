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
	A3_GameplayScene() = default;

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

	void updateHud(); // updates the game hud with new information


private:
	// Engine
	Director * director;

	DrawNode * hud; // a second layer used to put the hud on screen.
	Label * scoreLabel; // saves the score
	Label * lifeLabel; // saves the amount of lives

	DrawNode * hpNode; // saves the hp
	// Saves the location of the assets used to create the health bar. There are 6 assets used.
	/*
		[0]: HP Bar BG - a black background put behind the HP bar. It is the same size as a full hp bar.
		[1]: HP Bar - the actual hp bar. This changes size based on how much health the palyer has.
		[2]: Sepration Line (0.25) - separation line on the health bar. It marks 1/4 of the HP bar.
		[3]: Sepration Line (0.50) - separation line on the health bar. It makrs 2/4 of the HP bar.
		[4]: Sepration Line (0.75) - separation line on the health bar. It makrs 3/4 of the HP bar.
		[5]: Outline - outlines the HP Bar.
	*/
	DrawNode * hpBar[6];

	Size BARSIZE = Size(200.0F, 40.0F); // the size of the health bar

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

	//Event listeners
	// EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;

} GameplayScene;




