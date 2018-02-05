#include "Level.h"

using std::cout;

Level::Level()
{
}

void Level::load(string fileName)
{
	// Loads the level
	ifstream file;

	file.open(fileName);
	if (file.fail())
	{
		perror(fileName.c_str());
		system("pause");
		exit(1);
	}

	string line;

	// Loop through the entire file, getting each row and putting it in the line string
	while (getline(file, line))
	{
		// Push the current line onto the _levelData Array
		_levelData.push_back(line);
		_soldierGrid.push_back(vector <Soldier *>());
		_soldierGrid.back().resize(line.size(), nullptr);
	}

	file.close();

	// Process the level
	char tile;
	for (int i = 0; i < _levelData.size(); i++)
	{
		for (int j = 0; j < _levelData[i].size(); j++)
		{
			tile = _levelData[i][j];

			switch (tile)
			{			
				// Armies
			case '1':	// Team 1
				_armies[0].push_back(new Soldier("Skeleton's", tile, 1, 10, 5, 10, 0));
				_armies[0].back()->setPosition(j, i);
				_soldierGrid[i][j] = _armies[0].back();
				break;
			case '2':	// Team 2
				_armies[1].push_back(new Soldier("Zombie's", tile, 1, 10, 5, 10, 1));
				_armies[1].back()->setPosition(j, i);
				_soldierGrid[i][j] = _armies[1].back();
				break;
			case '#':
			case '.':
				break;
			default:
				printf("WARNING:Unknown tile%c at %D, %d", tile, j, i);
				system("pause");
				break;
			}
		}
	}

	random_device::result_type seed = random_device()();
	mt19937 randomEngine(seed);
	Soldier *tmp;

	// Shaffle armies
	for (int i = 0; i < NUM_ARMIES; i++)
	{
		// Iterate backwards through vector
		for (int j = _armies[i].size() - 1; j > 1; j--)
		{
			uniform_int_distribution<int> randomSwap(0, j - 1);
			int swap = randomSwap(randomEngine);
			tmp = _armies[i][j];
			_armies[i][j] = _armies[i][swap];
			_armies[i][swap] = tmp;
		}
	}
}

void Level::print()
{
	printf("%s", string(100, '\n').c_str());

	for (int i = 0; i < _levelData.size(); i++)
	{
		printf("%s\n", _levelData[i].c_str());
	}
}

void Level::update()
{
	char move;
	int i = 0;
	bool isDone = false;
	// loops until done
	while (isDone == false)
	{
		isDone = true;
		// loops through all armies
		for (int j = 0; j < NUM_ARMIES; j++)
		{
			if (i < _armies[j].size())
			{
				move = _armies[j][i]->getMove(_armies, NUM_ARMIES);
				processSoldierMove(move, _armies[j][i]);
				isDone = false;
			}
		}
		i++;
	}
}

char Level::getTile(int x, int y)
{
	return _levelData[y][x];
}

Soldier *Level::getSoldier(int x, int y)
{
	return _soldierGrid[y][x];
}

void Level::setTile(int x, int y, char tile, Soldier *soldier)
{
	_levelData[y][x] = tile;
	_soldierGrid[y][x] = soldier;
}

void Level::processSoldierMove(char direction, Soldier *soldier)
{
	int x, y;
	int targetX , targetY;

	soldier->getPosition(x, y);

	switch (direction)
	{
	case 'w':
		targetX = x;
		targetY = y - 1;
		break;
	case 'a':
		targetX = x - 1;
		targetY = y;
		break;
	case 's':
		targetX = x;
		targetY = y + 1;
		break;
	case 'd':
		targetX = x + 1;
		targetY = y;
		break;
	case '.':
		return;
	/*default:
		targetX = x;
		targetY = y;
		break;*/
	}

	char targetTile = getTile(targetX, targetY);

	switch (targetTile)
	{
	case '#':
		break;
	case '.':
		moveSoldier(soldier, targetX, targetY);
		break;
	default:
		battle(soldier, targetX, targetY);
		break;
	}
}

void Level::battle(Soldier *soldier, int targetX, int targetY)
{
	int x, y;
	int enemyArmy;
	soldier->getPosition(x, y);

	Soldier *targetSoldier = getSoldier(targetX, targetY);
	if (targetSoldier == nullptr)
	{
		return;
	}
	enemyArmy = targetSoldier->getArmy();
	if (enemyArmy == soldier->getArmy())
	{
		return;
	}

	int result = targetSoldier->takeDamage(soldier->attack());
	if (result == 1)
	{
		for (int i = 0; i < _armies[enemyArmy].size(); i++)
		{
			if (_armies[enemyArmy][i] == targetSoldier)
			{
				_armies[enemyArmy][i] = _armies[enemyArmy].back();
				_armies[enemyArmy].pop_back();
				
				setTile(targetX, targetY, '.', nullptr);
				break;
			}
		}
	}
}

void Level::moveSoldier(Soldier *soldier, int targetX, int targetY)
{
	int x, y;
	soldier->getPosition(x, y);

	setTile(x, y, '.', nullptr);
	setTile(targetX, targetY, soldier->getTile(), soldier);

	soldier->setPosition(targetX, targetY);
}
