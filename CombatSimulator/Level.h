#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <random>
#include "Soldier.h"

using std::string;
using std::vector;
using std::ifstream;
using std::mt19937;
using std::random_device;

const int NUM_ARMIES = 2;

class Level
{
public:
	Level();

	void load(string);
	void print();

	void update();

	// Getters
	char getTile(int, int);
	Soldier *getSoldier(int, int);
	// Setters
	void setTile(int, int, char, Soldier *);

private:
	void processSoldierMove(char, Soldier *);
	void battle(Soldier *, int, int);
	void moveSoldier(Soldier *, int, int);

	vector<string> _levelData;
	vector<vector <Soldier *>> _soldierGrid;
	vector<Soldier *> _armies[NUM_ARMIES];
};

