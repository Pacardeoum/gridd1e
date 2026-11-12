//
// player.cpp
//
// Davin Benson
// 10/16/19
// CS301 Project
//
#include "player.h"
#include <iostream>
#include <string>
using namespace std;


player::player()
{
	_id = -1;
	_name = "";
	_descrip = "";
	_alive = false;
	_hp = _mana = _xpos = _ypos = 0;
}
player::player( int id, string name, string descrip, int hp,
					  int mana, int xpos, int ypos)
{
	_id = id;
	_name = name;
	_descrip = descrip;
	_hp = hp;
	_mana = mana;
	_xpos = xpos;
	_ypos = ypos;
	_alive = true;
}
player::~player()
{
}
char player::dir()
{
	char input;
	do
	{
		cout << "What direction do you want to move? Enter 'w' 'a' 's'"
			 << " or 'd' for North, South, East or West: " << endl;
		cin >> input;

	} while (input != 'w' && input != 'a'
			&& input != 's' && input != 'd');
	return input;
}
