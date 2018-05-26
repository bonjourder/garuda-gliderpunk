#ifndef GARUDA_PIPEMANAGER
#define GARUDA_PIPEMANAGER

#include "Pipe.h"
#include "Glider.h"

#include <vector>

class PipeManager
{
public:
	PipeManager();
	~PipeManager();

	void Update();
	void Render();

	void Reset();

	bool CheckCollision(Glider& glider );
	int GetTotalPipeSpawned();
	
private:
	vector<Pipe*> pipes;

	float xSeparation;
	float minXSeparation;
	float ySeparation;
	float minYSeparation;

	int minSpawnY;
	int maxSpawnY;
	
	int totalPipesSpawn;

	void CreatePipe();
	
};

#endif // !GARUDA_PIPEMANAGER