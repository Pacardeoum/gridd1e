//
// character.cpp
//
// Davin Benson
// 10/17/19
// CS301 Project
//
#include "character.h"
#include "item.h"
#include <iostream>
using namespace std;

character::character()
{
	_id = -1;
	_name = "";
	_descrip = "";
	_alive = false;
	_hp = _mana = _xpos = _ypos = 0;
}
character::character( int id, string name, string descrip, int hp,
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
character::~character()
{
}
int character::gethp()
{
	return _hp;
}
int character::getmana()
{
	return _mana;
}
int character::getx()
{
	return _xpos;
}
int character::gety()
{
	return _ypos;
}
int character::get_id()
{
	return _id;
}
string character::getname()
{
	return _name;
}
string character::getdescrip()
{
	return _descrip;
}
bool character::get_alive()
{
	return _alive;
}
void character::sethp(int hp)
{
	_hp = hp;
}
void character::setmana(int mana)
{
	_mana = mana;
}
void character::update_pos( int x, int y)
{
	_xpos = x;
	_ypos = y;
}
int character::modify_health( int val )
{
	_hp += val;
	return _hp;
}
int character::modify_mana( int val )
{
	_mana += val;
	return _mana;
}
bool character::update_life( bool life )
{
	_alive = life;
	return _alive;
}
bool character::has( int item_num )
{
	return _inv.IsInList( item_num);
}
bool character::use( int item_num)
{
	bool ret = false;
	item* it = _inv.removeByKey( item_num );
	if ( it != nullptr )
	{
		delete it;
		ret = true;
	}
	return ret;
}
void character::take( item* it )
{
	_inv.AddEl( it );
}
item* character::give( int item_num )
{
	return _inv.removeByKey( item_num );
}
char character::dir()
{
	// temporary to make non-player characters not move.
	return 'n';
}
void character::print_inv( fstream &out )
{
	// change this bit to be configurable later
	out << "You look into your adventuring pack\n" << endl;
	_inv.Print( out );
}
