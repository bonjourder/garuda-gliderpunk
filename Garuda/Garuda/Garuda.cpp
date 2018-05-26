#include "GliderPunk/GameManager.h"
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	cout << "Garuda" << endl;
	srand(time(NULL));

	GameManager gameManager;
	gameManager.Start();

	return 0;
}