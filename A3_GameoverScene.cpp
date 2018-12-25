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

void A3_GameoverScene::onEnter()
{

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

}

void A3_GameoverScene::keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event) // if a key is let go
{

}

void A3_GameoverScene::update(float deltaTime)
{

}

void A3_GameoverScene::onExit()
{
	Scene::onExit();
}

