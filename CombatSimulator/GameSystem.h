#pragma once
#include "Level.h"
#include <string>
#include <conio.h>
//#include <iostream>

using std::string;

class GameSystem
{
public:
	GameSystem(string);

	void playGame();

private:
	Level _level;
};
