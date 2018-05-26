#include "GameManager.h"
#include <Windows.h>
#include <MMSystem.h>


GameManager::GameManager() 
{
	mEngine = new Engine();
	mEngine->Initialize((char*)"GLIDY PUNK");
	
	Sprite testSprite = Sprite("Assets/Gambar/kartun.png", Vector3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	testSprite.SetScale(0.15f);

	mLogoSprite = Sprite("Assets/Gambar/GlidyPunk_Logo.png", Vector3(Engine::SCREEN_WIDTH / 2, 2* (Engine::SCREEN_HEIGHT / 3), 0));
	mNotif = Sprite("Assets/Gambar/Spacebar.png", Vector3(Engine::SCREEN_WIDTH / 2, (Engine::SCREEN_HEIGHT / 3), 0));

	mGameoverSprite = Sprite("Assets/Gambar/go.png", Vector3(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2, 0));
	
	mGlider = new Glider(testSprite);
	mPipeManager = new PipeManager();
	mText = new Text();
	mText->Initialize();

	mState = State::START;
}

GameManager::~GameManager() 
{
	delete mEngine;
	delete mGlider;
	delete mPipeManager;
}

void GameManager::Start() 
{

	while (!glfwWindowShouldClose(mEngine->GetWindow()))
	{
		mEngine->Update();
		switch (mState)
		{
			case State::START:
			{
				mEngine->BeginRender();
				cout << mText->GetProgram() << endl;
			
				mText->RenderText("This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
				mLogoSprite.Render();
				mNotif.Render();
				
				//char buffer[10] = { '\0' };
				//sprintf_s(buffer, "%d", mPipeManager->GetTotalPipeSpawned()); //%d is for integers 
				//renderBitmapString(-1.2f, -0.2f, -5.0f, GLUT_BITMAP_HELVETICA_18, buffer);

				//mStartSprite.Render();
				mEngine->EndRender();

				if (Keyboard::KeyDown(GLFW_KEY_SPACE))
				{
					PlaySound("Assets/Sounds/track03.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

					SetState(State::GAMEPLAY);
				}
			}
			break;
			case State::GAMEPLAY:
			{
				
				mGlider->Update();
				mPipeManager->Update();
				mText->Update();
				bool isColliding = mPipeManager->CheckCollision(*mGlider);
				cout << mPipeManager->GetTotalPipeSpawned() << endl;

				mEngine->BeginRender();
				mGlider->Render();
				mPipeManager->Render();
				
				mEngine->EndRender();

				if (mGlider->GetY()<0 || mGlider->GetY()>Engine::SCREEN_HEIGHT)
				{
					isColliding = true;
				}

				if (isColliding) 
				{
					SetState(State::GAMEOVER);
				}

				
			}
			break;
			case State::GAMEOVER:
			{
				mEngine->BeginRender();
				mGlider->Render();
				mPipeManager->Render();
				mGameoverSprite.Render();
				mEngine->EndRender();
				if (Keyboard::KeyDown(GLFW_KEY_SPACE))
				{
					SetState(State::START);
				}

				if (Keyboard::KeyDown(GLFW_KEY_ESCAPE))
				{
					mEngine->Tutup();
				}


			}
			break;
			default: 
			{
				cout << "Unhandled" << static_cast<int>(mState) << endl;
			}
			break;
		}
	}
}

//private

void GameManager::SetState(State state) 
{
	mState = state;
	if (mState == State::START) 
	{
		mGlider->Reset();
		mPipeManager->Reset();
	}
}