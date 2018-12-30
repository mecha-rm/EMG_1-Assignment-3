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

	bool init();
	void initListeners(); // initalizes event handlers
	void initKeyboardListener();
	void initContactListener();
	void initSprites();

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
	Director * director;

	// Event listeners
	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;

	// Background Sprite
	Sprite * spr_BG;
	// Gameover Text
	Label * gmLabel;
	// Additional message text
	Label * msgLabel;

} GameoverScene, GameOverScene;


