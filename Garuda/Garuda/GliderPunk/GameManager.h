#ifndef GARUDA_GAMEMANAGER
#define GARUDA_GAMEMANAGER


#include "../Engine/Engine.h"
#include "../Engine/Graphics/Text.h"
#include "../Engine/Graphics/Sprite.h"
#include "../Engine/IO/Mouse.h"
#include "../Engine/IO/Keyboard.h"


#include "Glider.h" 
#include "Pipe.h"
#include "PipeManager.h"

class GameManager 
{
public:
	enum class State { START, GAMEPLAY, GAMEOVER, COUNT};

	int score;

public:
	GameManager();
	~GameManager();
	void Start();

private:

	void SetState(State state);

private:
	Engine * mEngine;
	Glider * mGlider;
	PipeManager * mPipeManager;
	Text * mText;

	Sprite mNotif;
	Sprite mLogoSprite;
	Sprite mGameoverSprite;

	State mState;
};

#endif // !GARUDA_GAMEMANAGER

