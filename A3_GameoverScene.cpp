#include "A3_GameoverScene.h"

A3_GameoverScene::A3_GameoverScene() {}

Scene * A3_GameoverScene::createScene()
{
	// 'scene' is an autorelease object
	Scene* scene = Scene::create(); // create without physics
	// Scene* scene = Scene::createWithPhysics(); // create with physics
	A3_GameoverScene* layer = A3_GameoverScene::create();

	scene->addChild(layer);

	return scene;
}

void A3_GameoverScene::onEnter() { Scene::onEnter(); }

bool A3_GameoverScene::init()
{
	// Ensure the parent init function was called first. If it wasn't, exit this one.
	if (!Scene::init())
		return false;

	director = Director::getInstance();

	// Initialize the event handlers
	initListeners();

	// Initalize sprites
	initSprites();

	// Allows for the update() function to be called by cocos
	this->scheduleUpdate();

	//Let cocos know that the init function was successful
	return true;
}

void A3_GameoverScene::initListeners() // initalizes event handlers
{
	initKeyboardListener();

}

void A3_GameoverScene::initKeyboardListener()
{
	//Create the keyboard listener
	keyboardListener = EventListenerKeyboard::create();

	//Setting up callbacks
	keyboardListener->onKeyPressed = CC_CALLBACK_2(A3_GameoverScene::keyDownCallback, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(A3_GameoverScene::keyUpCallback, this);

	//Add the keyboard listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void A3_GameoverScene::initContactListener()
{

}

void A3_GameoverScene::mouseDownCallback(Event* event)
{

}

void A3_GameoverScene::mouseUpCallback(Event* event)
{

}

void A3_GameoverScene::mouseMoveCallback(Event* event)
{

}

void A3_GameoverScene::mouseScrollCallback(Event* event)
{

}

void A3_GameoverScene::keyDownCallback(EventKeyboard::KeyCode keyCode, Event* event) // if a key is held down
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) // exiting the game.
		exit(0);
}

void A3_GameoverScene::keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event) // if a key is let go
{

}

void A3_GameoverScene::initSprites()
{

	// Creates a background and gameover message.
	spr_BG = Sprite::create("images/space_bg1_gm.jpg"); //Load the handle
	spr_BG->setAnchorPoint(Vec2(0.5f, 0.5f)); //Ensure the middle of the background is the anchor point
	spr_BG->setPosition(director->getWinSizeInPixels().width / 2.0f, director->getWinSizeInPixels().height / 2.0f); // centre background; ensure the middle of the background is the anchor point
	this->addChild(spr_BG); // Adds the background sprite

	gmLabel = Label::create("Game Over", "fonts/arial.ttf", 100, Size(director->getWinSizeInPixels().width, director->getWinSizeInPixels().height), TextHAlignment::CENTER, TextVAlignment::CENTER);
	gmLabel->setAnchorPoint(cocos2d::Vec2(0.0F, 0.0F));
	gmLabel->setPosition(gmLabel->getPosition() + Vec2(0.0F, 30.0F));
	gmLabel->enableShadow();
	this->addChild(gmLabel);

	msgLabel = Label::create("Press the space bar to exit the game.", "fonts/arial.ttf", 48, Size(director->getWinSizeInPixels().width, director->getWinSizeInPixels().height), TextHAlignment::CENTER, TextVAlignment::CENTER);
	msgLabel->setAnchorPoint(cocos2d::Vec2(0.0F, 0.0F));
	msgLabel->setPosition(msgLabel->getPosition() + Vec2(0.0F, -30.0F));
	msgLabel->enableShadow();
	this->addChild(msgLabel);

}

void A3_GameoverScene::update(float deltaTime)
{

}

void A3_GameoverScene::onExit()
{
	Scene::onExit();
}

