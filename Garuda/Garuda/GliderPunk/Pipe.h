#ifndef GARUDA_PIPE
#define GARUDA_PIPE

//Erastus

#include "../Engine/Graphics/Sprite.h"
#include "../Engine/Physics/BadanKaku.h"
#include "../Engine/Math/Vector3.h"

// using namespace std;

class Pipe
{
public:
	static Sprite* pipeSprite;
	static void initialize();

	Pipe();
	Pipe(Vector3 _pos);

	void SetGap(float gap);

	void Update();
	void Render();

	void MoveTo(Vector3 to);
	void MoveBy(Vector3 by);

	float GetX();
	float GetWidth();

	BadanKaku GetTopBK();
	BadanKaku GetBotBK();

private:
	void UpdatePos();

	Sprite topSprite;
	Sprite botSprite;
	BadanKaku topRB;
	BadanKaku botRB;

	Vector3 pos;


	float gap;
	float speed;
};

#endif
