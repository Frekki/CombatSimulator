#include "GameSystem.h"

// Constractor sets up the game
GameSystem::GameSystem(string levelFileName)
{
	_level.load(levelFileName);

	system("pause");
}

void GameSystem::playGame()
{
	bool isDone = false;

	while (isDone == false)
	{
		_level.print();
		_level.update();

		_getch();
	}
}