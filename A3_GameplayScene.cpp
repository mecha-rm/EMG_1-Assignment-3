#include "A3_GameplayScene.h"
#include "UtilityMath.h"

// #include "A3_GameoverScene.h"
#include <iostream>

float A3_GameplayScene::screenWidth = 0.0f; // screen width
float A3_GameplayScene::screenHeight = 0.0f; // screen height

// constructor; if no screenWidth or height is provided, screen wrapping is disabled
A3_GameplayScene::A3_GameplayScene() 
{
	
}

Scene * A3_GameplayScene::createScene()
{
	// 'scene' is an autorelease object
	Scene* scene = Scene::create(); // create without physics
	// Scene* scene = Scene::createWithPhysics(); // create with physics
	A3_GameplayScene* layer = A3_GameplayScene::create();

	scene->addChild(layer);
	// Vec2 winSize = Director::getInstance()->getWinSizeInPixels();
	return scene;
}

// Creates the scene, setting the scene's width and height as well.
Scene * A3_GameplayScene::createScene(float width, float height) 
{
	screenWidth = width;
	screenHeight = height;
	return createScene();
}

// What we do on enter.
void A3_GameplayScene::onEnter()
{
	Scene::onEnter(); // activates base functionality.
}

// Initalizer function
bool A3_GameplayScene::init()
{
	// Ensure the parent init function was called first. If it wasn't, exit this one.
	if (!Scene::init())
		return false;

	director = Director::getInstance();

	// Initialize the event handlers
	initListeners();

	//Init the Sprites
	initSprites();

	// Initialize the pause menu
	// initPauseMenu();

	// Allows for the update() function to be called by cocos
	this->scheduleUpdate();

	//Let cocos know that the init function was successful
	return true;	
}

// initializes liseners
void A3_GameplayScene::initListeners()
{
	// Init the contact listener
	// initContactListener();
	initKeyboardListener();
}

// void A3_GameplayScene::initMouseListener()
// {

// }

// Listens for keyboard inptu
void A3_GameplayScene::initKeyboardListener()
{
	//Create the keyboard listener
	keyboardListener = EventListenerKeyboard::create();

	//Setting up callbacks
	keyboardListener->onKeyPressed = CC_CALLBACK_2(A3_GameplayScene::keyDownCallback, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(A3_GameplayScene::keyUpCallback, this);

	//Add the keyboard listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

// initContactListeners
/*
void A3_GameplayScene::initContactListener()
{
	//Create the contact listener
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	// create onContactBeginCallback
	//Assign callbacks
	contactListener->onContactBegin = CC_CALLBACK_1(A3_GameplayScene::onContactBeginCallback, this);

	//Add the listener to the event dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

}
*/

// Callbacks; automatically called

// Pressing a Key
void A3_GameplayScene::keyDownCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		std::cout << "Space Bar Was Pressed!" << std::endl;
		spaceBar = true;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW || keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		// pShip->sprite->setPosition(Vec2 (pShip->sprite->getPositionX() + 3.0f, pShip->sprite->getPositionY()));
		std::cout << "Up Key or 'W' Key Pressed!" << std::endl;
		upKey = true;

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW || keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		std::cout << "Down Key or 'S' was pressed" << std::endl;
		downKey = true;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		std::cout << "Left Key or 'L' Key Pressed!" << std::endl;
		leftKey = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		std::cout << "Right Key or 'D' Pressed!" << std::endl;
		rightKey = true;
	}
	// Toggles on and off rotations
	if (keyCode == EventKeyboard::KeyCode::KEY_CAPS_LOCK)
	{
		pShip->rotateLR = !pShip->rotateLR;
	}
}

// Letting Go of a Key
void A3_GameplayScene::keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		std::cout << "Space Bar Was Released!" << std::endl;
		spaceBar = false;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW || keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		// keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ? std::cout << "Up Key Pressed!" << std::endl : std::cout << "W Key Pressed!" << std::endl;
		std::cout << "Up Key or 'W' Key Released!" << std::endl;
		upKey = false;

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW || keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		std::cout << "Down Key or 'S' Key Released!" << std::endl;
		downKey = false;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		std::cout << "Left Key or 'L' Key Released!" << std::endl;
		leftKey = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		std::cout << "Right Key or 'D' Released!" << std::endl;
		rightKey = false;

	}
}

// Tells cocos if we want two things to collide, and what to do if there is collision. We should be using our own collision math.
// bool A3_GameplayScene::onContactBeginCallback(PhysicsContact& contact) { return false; }

// Initializes sprites
void A3_GameplayScene::initSprites()
{
	// image starts in the 'resource' folder
	//Init the background sprites
	spr_BG = Sprite::create("images/space_bg1.jpg"); //Load the handle
	spr_BG->setAnchorPoint(Vec2(0.5f, 0.5f)); //Ensure the middle of the background is the anchor point
	spr_BG->setPosition(director->getWinSizeInPixels().width / 2.0f, director->getWinSizeInPixels().height / 2.0f); // centre background; ensure the middle of the background is the anchor point
	this->addChild(spr_BG); // Add the sprite, pushed way to the back
	// spr_BG2 = Sprite::create("UA/Background/spr_Background.jpg"); //Load the handle
	// spr_BG2->setAnchorPoint(Vec2(0.5f, 0.5f)); //Ensure the middle of the background is the anchor point
	// spr_BG2->setPosition(director->getWinSizeInPixels().width / 2.0f, director->getWinSizeInPixels().height / 2.0f); // centre background; ensure hte middle of the background is the anchor point

	// Setting the wrapping points for all entities
	Entity::setWrapPointsMin(Vec2(0.0f, 0.0f));
	Entity::setWrapPointsMax(Vec2(screenWidth, screenHeight));

	// Creates the player ship; all values beyond the constructor are set in the player class
	pShip = new Player(Vec2(director->getWinSizeInPixels().width / 2.0f, director->getWinSizeInPixels().height / 2.0f), "images/player_ship.png");
	// smallAsteroid = new Enemy(1);
	// largeAsteroid = new Enemy(2);

	this->addChild(pShip->getSprite());
	
	Enemy* enemy; // generic enemy object

	// Starts off with random asteroids of varying sizes
	for (int i = 0; i < 3; i++)
	{
		enemy = new Enemy(rand() % 2 + 1);
		enemies.push_back(enemy); // to keep track of the enemy
		this->addChild(enemy->getSprite());
	}
	
	// Labels
	scoreLabel = Label::create("SCORE: ", "arial", 30.0F, Size(screenWidth, screenHeight), TextHAlignment::CENTER, TextVAlignment::TOP);
	scoreLabel->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	// scoreLabel->setString("Ultron"); // used to change text
	scoreLabel->enableShadow();
	this->addChild(scoreLabel);
	
	// Tutorial: https://www.youtube.com/watch?v=iBfggFTvldw
	hpNode = DrawNode::create(); // creates the shape
	// To set a pre-existing color, use Color4F::COLOUR_NAME. e.g. Color4F::ORANGE
	// RGBA = (Red, Green, Blue, Alpha) https://en.wikipedia.org/wiki/RGBA_color_space
	// 'Alpha' measures how opague each pixel is. The higher the 'alpha' value, the more opague the colour is.
	

	hpNode->drawSolidRect(Vec2(0.0F, 0.0F), Vec2(100.0F, 100.0F), Color4F(50.0F, 200.0F, 150.0F, 1.00F)); // can be done by four corner points, or starting point and ending point.
	hpNode->drawSolidRect(Vec2(49.0F, 324.0F), Vec2(200.0F, 400.0F), Color4F(50.0F, 200.0F, 150.0F, 1.00F));
	this->addChild(hpNode);
	
	// this->addChild(hpNode);


}

// Spawns a random enemy if no enemy is passed
void A3_GameplayScene::spawnEnemy(Enemy * enemy)
{
	this->addChild(enemy->getSprite()); // adds the sprite to the draw list
	enemies.push_back(enemy); // adds the enemy to the enemy vector
}

// Spawns a specific enemy
void A3_GameplayScene::spawnEnemy(unsigned short int type)
{
	Enemy * enemy = new Enemy(type);
	spawnEnemy(enemy); // passes the enemy to be spawned.
}

// Main update loop
void A3_GameplayScene::update(float deltaTime)
{
	timer += deltaTime; // gets delta time across 'x' period of time
	if(timer > 1.0F)// when 1 second has passed, an enemy is spawned.
	{
		spawnEnemy(); // spawns the enemy
		timer = 0; // puts the timer back at 0.
		// spawn = deltaTime; // gets current timer
	}

	updatePlayer(deltaTime);
	updateEnemies(deltaTime);
	updateProjectiles(deltaTime);

	collisions(); // goes through collisions

	//Color4f (r, g, b, a)
	// Color3f()
	// https://cocos2d-x.org/reference/native-cpp/V3.0alpha0/d2/d77/structcocos2d_1_1_color4_f.html#a9b6e45d9600d22cba771844689366dd8
	
	// cocos2d::Label lbl = Label()
	ccDrawSolidRect(Vec2(10.0F, 10.0F), Vec2(40.0F, 40.0F), Color4F(0, 0, 255.0F, 100));

}

void A3_GameplayScene::updatePlayer(float deltaTime)
{
	// Sets whether pressing left and right rotates, or moves the ship.
	// The force that gets applied.
	const float force(pShip->getAppliedForce());
	static float locTime = 0.5F; // prevents a projectile from being fired for (x) amount of time
	const float R_SPD = 0.045F; // controls how fast the player rotates

	Projectile * proj;

	if (spaceBar)
	{
		if (locTime > 0.2F) // has a delay between when a projectile can be fired again.
		{
			proj = new Projectile(pShip->getPosition(), "images/projectile2.png", 7.50F, pShip->theta, 5.0F); // creates a new projectile

			projectiles.push_back(proj);
			this->addChild(projectiles.at(projectiles.size() - 1)->getSprite());
			locTime = 0;

		}
		else
		{
			locTime += deltaTime;
		}
		
	}

	// Going Up
	if (upKey)
	{
		// If true, an 'x' force and 'y' force since the force is going to be rotated.
		(pShip->rotateLR) ? pShip->addForce(0, force) : pShip->addForce(0, force);
		// pShip->setPositionY(pShip->getPositionY() + 1);
	}
	// Going Down
	else if (downKey)
	{
		(pShip->rotateLR) ? pShip->addForce(0, -force) : pShip->addForce(0, -force);
		// pShip->setPositionY(pShip->getPositionY() - 1);
	}


	// Going Left
	if (leftKey)
	{
		(pShip->rotateLR) ? pShip->theta -= R_SPD  : pShip->addForce(-force, 0);
	}
	// Going Right
	else if (rightKey)
	{
		(pShip->rotateLR) ? pShip->theta += R_SPD : pShip->addForce(force, 0);
	}

	pShip->update(deltaTime);
}

// Updates enemies
void A3_GameplayScene::updateEnemies(float deltaTime)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies.at(i)->update(deltaTime); // calls individual updates
		// umath::collision(pShip, enemies.at(i)); // collision check
	}
}

void A3_GameplayScene::updateProjectiles(float deltaTime)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->update(deltaTime); // calls individual updates
		if (projectiles.at(i)->getTime() >= projectiles.at(i)->LIFESPAN)
		{
			projectiles.at(i)->getSprite()->runAction(RemoveSelf::create()); // removes the sprite from the draw list
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
		// umath::collision(pShip, projectiles.at(i)); // collision check
	}
}

// collisions
void A3_GameplayScene::collisions()
{

	Enemy * enemy; // temporary enemy object

	// Projectile Collision with Enemies
	for (int i = 0; i < projectiles.size(); i++)
	{
		for (int j = 0; j < enemies.size(); j++)
		{
			// If there is collision
			if (umath::collision(projectiles[i], enemies[j]))
			{
				// put in deconstructor
				projectiles.at(i)->getSprite()->runAction(RemoveSelf::create()); // removes the sprite from the draw list
				projectiles.erase(projectiles.begin() + i); // removes the sprite from the vector list
				i--;

				// Large Asteroid splits into 2-4 small asteroids.
				if (enemies[j]->getType() == 2)
				{
					for (int k = rand() % 3 + 2; k > 0; k--) // spawns two to four small asteroids
					{
						enemy = new Enemy(1);
						enemy->setPosition(enemies[j]->getPosition()); // gives the new small asteroid the big asteroid's original position

						enemies.push_back(enemy); // pushes the enemy onto the enemy vector
						this->addChild(enemies.at(enemies.size() - 1)->getSprite()); // adds the sprite to the draw list
					}
				}

				enemies.at(j)->getSprite()->runAction(RemoveSelf::create()); // removes the sprite from the draw list
				enemies.erase(enemies.begin() + j); // erases the enemy from the enemy vector
				break;
			}
		}

		if (i >= projectiles.size())
			break;
	}
}

/*
// Updates both mouse and keyboard inputs.
void A3_GameplayScene::updateInputs()
{
	updateKeyboardInputs();
}

void A3_GameplayScene::updateKeyboardInputs()
{
	// if (endMenuDisplayed) return; // prevents use if end screen is active
	
}
*/