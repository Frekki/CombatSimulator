#pragma once
#include <string>
#include <random>
#include <ctime>
#include <vector>

using std::default_random_engine;
using std::uniform_int_distribution;
using std::string;
using std::vector;

class Soldier
{
public:
	Soldier(string, char, int, int, int, int, int);

	// Setters
	void setPosition(int, int);

	// Getters
	void getPosition(int&, int&);
	string getName() { return _name; }
	char getTile() { return _tile; }
	int getArmy() { return _army; }

	int attack();
	int takeDamage(int);

	// Gets AI move command
	char getMove(vector <Soldier *> [], int );

private:
	Soldier * getClosestEnemy(vector <Soldier *> [], int);

	string _name;
	char _tile;

	int _level;
	int _attack;
	int _defense;
	int _health;
	int _army;

	// Position
	int _x;
	int _y;
};

