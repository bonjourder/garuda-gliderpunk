#ifndef GARUDA_RECT
#define GARUDA_RECT

//David

#include "Vector3.h";
#include <string>
#include <sstream>

using namespace std;

class Rect
{
public:
	Rect();
	Rect(Vector3 _size);
	Rect(Vector3 _post, Vector3 _size);

	void MoveTo(Vector3 to);
	void MoveBy(Vector3 by);
	void SetSize(Vector3 _size);

	string ToString();

	Vector3 upperLeftVertex;
	Vector3 upperRightVertex;
	Vector3 lowerLeftVertex;
	Vector3 lowerRightVertex;

private:
	void UpdateVertices();

	Vector3 pos;
	Vector3 size;


};

#endif

