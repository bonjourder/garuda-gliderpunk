#ifndef GARUDA_GLIDER
#define GARUDA_GLIDER
//Faishal
#include "../Engine/Graphics/Sprite.h"
#include "../Engine/Physics/BadanKaku.h"


class Glider
{
public:
	Glider();
	Glider(Sprite _sprite);

	void Update();
	void Render();

	void Glide();
	void Reset();

	float GetY();
	
	Sprite& GetSprite();
	BadanKaku& GetBK();



private:
	void HandleInput();

private:
	Sprite sprite;
	BadanKaku bk;

	float glideForce;
	float maxRot;
	float minRot;
	
};

#endif // !GARUDA_GLIDER;
