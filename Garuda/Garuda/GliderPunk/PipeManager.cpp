#include "PipeManager.h"

#include "../Engine/Engine.h"
#include "../Engine/Physics/BadanKaku.h"

PipeManager::PipeManager() :
	xSeparation(700),
	ySeparation(350),
	minXSeparation(200),
	minYSeparation(300),
	minSpawnY(200),
	maxSpawnY(Engine::SCREEN_HEIGHT - 200),
	totalPipesSpawn(-1)
{
	Pipe::initialize();
	CreatePipe();
}

PipeManager::~PipeManager() 
{
	for (unsigned int i=0;i<pipes.size(); i++)
	{
		delete pipes[i];
	}
}

void PipeManager::Update()
{
	vector<int> pipesToDelete;
	for (unsigned int i = 0; i < pipes.size(); i++)
	{
		pipes[i]->Update();
		if (pipes[i]->GetX() < -(pipes[i]->GetWidth()/2)) //Obstacle dihapus saat berada di posisi tertentu
		{
			pipesToDelete.push_back(i);
		}

		if (i == pipes.size() - 1) 
		{
			if (pipes[i]->GetX() < Engine::SCREEN_WIDTH - xSeparation) 
			{
				CreatePipe();
			}
		}

	}

	for (unsigned int i = 0; i < pipesToDelete.size(); i++) 
	{
		delete pipes[pipesToDelete[i]];
		pipes.erase(pipes.begin() + pipesToDelete[i]);
		
	}


}

void PipeManager::Render() 
{
	for (unsigned int i = 0; i < pipes.size(); i++)
	{
		pipes[i]->Render();
	}
}
 
bool PipeManager::CheckCollision(Glider& glider) 
{
	bool isColliding = false;
	
	for (unsigned int i = 0; i < pipes.size(); i++) 
	{
		
		isColliding =	BadanKaku::IsColliding(glider.GetBK(), pipes[i]->GetTopBK()) || 
						BadanKaku::IsColliding(glider.GetBK(), pipes[i]->GetBotBK());

		if (isColliding) 
			break;
	}

	return isColliding;

}

void PipeManager::Reset() 
{
	for (unsigned int i = 0; i < pipes.size() ;i++) 
	{
		delete pipes[i];
	}
	pipes.clear();

	totalPipesSpawn = -1;
	CreatePipe();
}

int PipeManager::GetTotalPipeSpawned()
{
	return totalPipesSpawn;
}
 
//private

void PipeManager::CreatePipe()
{
	float spawnY = rand() % (maxSpawnY - minSpawnY) + minSpawnY;
	Pipe* pipe = new Pipe(Vector3(Engine::SCREEN_WIDTH, spawnY, 0));
	pipe->SetGap(ySeparation);

	pipes.push_back(pipe);
	totalPipesSpawn++;
}

