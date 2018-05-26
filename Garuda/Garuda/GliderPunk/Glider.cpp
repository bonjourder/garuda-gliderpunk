#include "Glider.h"

#include"../Engine/Engine.h"
#include"../Engine/IO/Keyboard.h"
#include"../Engine/IO/Mouse.h"
//Faishal // ->https://youtu.be/w-cPnlsKlGk?t=41m7s
//Kelas gamenya
Glider::Glider()
{
	glideForce = 750; //sesuai setKec di method Glide
	maxRot = 10;
	minRot = -maxRot;
}

Glider::Glider(Sprite _sprite) : Glider()
{
	sprite = _sprite;
	Rect boundingRect = Rect();
	Vector3 sizeOffset(0.8, 0.6, 1);	
	boundingRect.SetSize(*sprite.GetSize() * *sprite.GetScale() * sizeOffset);

	bk.Initialize(0.8f, -10, sprite.GetPos(),sprite.GetRot(),sprite.GetScale(),sprite.GetSize(),boundingRect);
}

void Glider::Update()
{
	HandleInput();
	sprite.Update();
	bk.Update();

	float yVel = bk.GetKec().y;
	if (glideForce == 0)
	{
		cout << "Terdapat error" << endl;
		glideForce = 750;
	}
	float newRot = (maxRot / glideForce)*yVel;
	sprite.RotateTo(newRot); //rotasi default
}

void Glider::Render()
{
	sprite.Render();
	bk.Render(Vector3(255, 255, 255));
}

void Glider::Glide()
{
	bk.SetKec(Vector3(0, glideForce, 0));
	sprite.RotateTo(maxRot); //rotasi pas ditekan
	
}

Sprite& Glider::GetSprite()
{
	return sprite;
}

BadanKaku& Glider::GetBK()
{
	return bk;
}

void Glider::Reset() 
{
	sprite.MoveTo(Vector3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	sprite.RotateTo(0);
	bk.SetKec(Vector3(0,0,0));
}

float Glider::GetY() 
{
	return sprite.GetPos()->y;
}

//private
void Glider::HandleInput()
{
	if (Keyboard::KeyDown(GLFW_KEY_SPACE) || Mouse::ButtonDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		Glide();
	}
}