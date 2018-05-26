#ifndef GARUDA_BADANKAKU
#define GARUDA_BADANKAKU
//Faishal 
#include "../Math/Vector3.h"
#include "../Math/Rect.h"
#include "../Engine.h"
#include "../Math/Math.h"

#include <vector>

class BadanKaku 
{
public:

	static bool IsColliding(const BadanKaku& bkA, const BadanKaku& rbB); 
	BadanKaku();

	void Initialize(float _friction, float _gravity, Vector3* _pos, float* _rot, Vector3* _scale, Vector3* _size , Rect _boundingRect);

	void Update();
	void Render(Vector3 c); //buat RGB

	void AddForce(Vector3 f); //gaya 

	Vector3 GetKec();
	void SetKec(Vector3 _kec);

private:
	Vector3* pos;//vector3 with pointer
	float* rot;
	float lastRot;

	Vector3* scale;
	Vector3* size;

	float gravity;
	float friction;
	Vector3 vel;


	Rect boundingRect;
};

#endif

