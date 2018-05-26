#include "BadanKaku.h"

using namespace std;
//Faishal
BadanKaku::BadanKaku()
{
	friction = 1; //makin velil makin pelan objek
	gravity = 0;
}

void BadanKaku::Initialize(float _friction, float _gravity, Vector3* _pos, float* _rot, Vector3* _scale, Vector3* _size , Rect _boundingRect)
{
	friction = _friction;
	gravity = _gravity;

	pos = _pos;
	rot = _rot;
	scale = _scale;
	size = _size;
	lastRot = *rot;

	boundingRect = _boundingRect;
}

void BadanKaku::Update()
{
	vel.x *= friction;
	vel.y += gravity;

	*pos = *pos + (vel * Engine::GetDT());//modifikasi posisi tiap End of Frame

	
	if (lastRot != *rot) {
		boundingRect.lowerLeftVertex =		Math::RotatePoint(boundingRect.lowerLeftVertex, Vector3(0), *rot - lastRot);
		boundingRect.lowerRightVertex =		Math::RotatePoint(boundingRect.lowerRightVertex, Vector3(0), *rot - lastRot);
		boundingRect.upperLeftVertex =		Math::RotatePoint(boundingRect.upperLeftVertex, Vector3(0), *rot - lastRot);
		boundingRect.upperRightVertex =		Math::RotatePoint(boundingRect.upperRightVertex, Vector3(0), *rot - lastRot);
		lastRot = *rot;
	}
}

void BadanKaku::Render(Vector3 c)
{
	glLoadIdentity();

	glTranslatef(pos->x, pos->y, pos->z);
	

	glColor4f(c.x, c.y , c.z, 0);
	glLineWidth(0);
	glBegin(GL_LINES);
	{
		/*
		glVertex2i(0,0);//garis kiribawah
		glVertex2i((int)size->x,0);//garis kananbawah

		glVertex2i((int)size->x, 0);//garis kananbawah
		glVertex2i((int)size->x, (int)size->y);//garis ataskanan

		glVertex2i((int)size->x, (int)size->y);//garis ataskanan
		glVertex2i(0, (int)size->y);//garis kiriatas

		glVertex2i(0, (int)size->y);//garis kiriatas
		glVertex2i(0, 0);//garis kiribawah
		*/

		glVertex2f(boundingRect.lowerLeftVertex.x, boundingRect.lowerLeftVertex.y);//garis kiribawah
		glVertex2f(boundingRect.lowerRightVertex.x, boundingRect.lowerRightVertex.y);//garis kananbawah

		glVertex2f(boundingRect.lowerRightVertex.x, boundingRect.lowerRightVertex.y);//garis kananbawah
		glVertex2f(boundingRect.upperRightVertex.x, boundingRect.upperRightVertex.y);//garis ataskanan

		glVertex2f(boundingRect.upperRightVertex.x, boundingRect.upperRightVertex.y);//garis ataskanan
		glVertex2f(boundingRect.upperLeftVertex.x, boundingRect.upperLeftVertex.y);//garis kiriatas

		glVertex2f(boundingRect.upperLeftVertex.x, boundingRect.upperLeftVertex.y);//garis kiriatas
		glVertex2f(boundingRect.lowerLeftVertex.x, boundingRect.lowerLeftVertex.y);//garis kiribawah

	}
	glEnd();
}

void BadanKaku::AddForce(Vector3 gaya)
{
	vel = vel + gaya;
}

Vector3 BadanKaku::GetKec()
{
	return vel;
}

void BadanKaku::SetKec(Vector3 _kec)
{
	vel = _kec;
}

bool BadanKaku::IsColliding(const BadanKaku& bkA, const BadanKaku& bkB) //David
{
	Rect rcA = bkA.boundingRect;
	Rect rcB = bkB.boundingRect;

	Vector3 aUR = rcA.upperRightVertex	+ *bkA.pos;
	Vector3 aUL = rcA.upperLeftVertex	+ *bkA.pos;
	Vector3 aLR = rcA.lowerRightVertex	+ *bkA.pos;
	Vector3 aLL = rcA.lowerLeftVertex	+ *bkA.pos;
	Vector3 bUR = rcB.upperRightVertex	+ *bkB.pos;
	Vector3 bUL = rcB.upperLeftVertex	+ *bkB.pos;
	Vector3 bLR = rcB.lowerRightVertex	+ *bkB.pos;
	Vector3 bLL = rcB.lowerLeftVertex	+ *bkB.pos;

	float aMax = 0;
	float aMin = 0;	
	float bMax = 0;	
	float bMin = 0;

	Vector3 axis1 = aUR - aUL; //Garis atas
	Vector3 axis2 = aUR - aLR; //Garis samping kanan
	Vector3 axis3 = bUL - bLL; //Garis Samping kiri
	Vector3 axis4 = bUL - bUR; 

	vector<Vector3> axes;
	axes.push_back(axis1);
	axes.push_back(axis2);
	axes.push_back(axis3);
	axes.push_back(axis4);

	for (int i = 0 ; i < axes.size() ; i++) 
	{
		Vector3 aURProject = Vector3::Project(aUR, axes[i]);
		Vector3 aULProject = Vector3::Project(aUL, axes[i]);
		Vector3 aLRProject = Vector3::Project(aLR, axes[i]);
		Vector3 aLLProject = Vector3::Project(aLL, axes[i]);
		Vector3 bURProject = Vector3::Project(bUR, axes[i]);
		Vector3 bULProject = Vector3::Project(bUL, axes[i]);
		Vector3 bLRProject = Vector3::Project(bLR, axes[i]);
		Vector3 bLLProject = Vector3::Project(bLL, axes[i]);

		float aURScalar = Vector3::Dot(aURProject, axes[i]);
		float aULScalar = Vector3::Dot(aULProject, axes[i]);
		float aLRScalar = Vector3::Dot(aLRProject, axes[i]);
		float aLLScalar = Vector3::Dot(aLLProject, axes[i]);
		float bURScalar = Vector3::Dot(bURProject, axes[i]);
		float bULScalar = Vector3::Dot(bULProject, axes[i]);
		float bLRScalar = Vector3::Dot(bLRProject, axes[i]);
		float bLLScalar = Vector3::Dot(bLLProject, axes[i]);

		vector<float> aScalars;
		aScalars.push_back(aURScalar);
		aScalars.push_back(aULScalar);
		aScalars.push_back(aLRScalar);
		aScalars.push_back(aLLScalar);
		aMin = Math::Min(aScalars);
		aMax = Math::Max(aScalars);

		vector<float> bScalars;
		bScalars.push_back(bURScalar);
		bScalars.push_back(bULScalar);
		bScalars.push_back(bLRScalar);
		bScalars.push_back(bLLScalar);
		bMin = Math::Min(bScalars);
		bMax = Math::Max(bScalars);

		if (!(bMin <= aMax && bMax >= aMin)) 
		{
			return false;
		}
		
	}
	return true;
}
