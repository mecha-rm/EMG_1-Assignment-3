// The scene the program starts on
#pragma once

#include "cocos2d.h"

using namespace cocos2d;

typedef class A3_GameoverScene : public Scene
{
public:
	A3_GameoverScene();

	static Scene* createScene();
	// Called when the scene is entered.
	void onEnter();

	void initListeners(); // initalizes event handlers
	void initKeyboardListener();
	void initContactListener();

	void mouseDownCallback(Event* event);
	void mouseUpCallback(Event* event);
	void mouseMoveCallback(Event* event);
	void mouseScrollCallback(Event* event);
	void keyDownCallback(EventKeyboard::KeyCode keyCode, Event* event); // if a key is held down
	void keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event); // if a key is let go

	void update(float deltaTime);

	void onExit();

	CREATE_FUNC(A3_GameoverScene);

private:
	
	// Event listeners
	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;

} GameoverScene, GameOverScene;


