#ifndef GARUDA_INPUTMANAGER
#define GARUDA_INPUTMANAGER

#include "../Engine/Engine.h"
#include "../Engine/IO/Mouse.h"
#include "../Engine/IO/Keyboard.h"
#include "Glider.h"
#include "Pipe.h"

class InputManager
{
public:
	InputManager();
	InputManager(Glider* _glider);

	void Update();

private:
	Glider* glider;

};

#endif