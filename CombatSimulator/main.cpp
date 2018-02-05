#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>

#include"GameSystem.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
	GameSystem gameSystem("level1.txt");

	gameSystem.playGame();

	return 0;
}