//
// engine.cpp
//
// Davin Benson
// CS301 Project
// 10/10/19
//
#include "engine.h"
#include <fstream>
#include <iostream>
#include "item.h"
#include "character.h"
#include "tile.h"
#include "tile_map.h"
#include <cstdlib>
#define FOG_TILES 5
using namespace std;

engine::engine()
{
	num_items = num_chars = num_tiles = 0;
	item_list = nullptr;
	tile_list = nullptr;
	grid = nullptr;
	characters = nullptr;
	_end = false;
	pc = nullptr;
	goal = nullptr;
	warmap = nullptr;
}
engine::engine(istream &item_in, istream& character_in,
			   istream& tile_in, istream& map_in)
{
	read_item(item_in);
	read_character(character_in);
	read_tile(tile_in);
	read_map(map_in);
	_end = false;
	pc = characters[0];
	goal = tile_list[0];
	warmap = new char[grid->getw() * grid->geth()];
	int i = 0;
	for ( i = 0; i < grid->geth() * grid->getw(); i++ )
	{
        warmap[i] = '#';
	}
	defog();
	//
}
void engine::read_item( istream &in )
{
	int i;
	item* it = nullptr;
	// read in the item file, making the array of items, and making
	// each of those items from the data present in it.
	in >> num_items;
    item_list = new item*[num_items]{nullptr};
	for ( i = 0; i < num_items; i++)
	{
		it = new item;
		// the read in routine here is likely not proper, specifically
		// in regards to newline management
		in >> it->id;
		getline(in, it->name, '"');
		it->name.erase( it->name.begin());
		getline(in, it->descrip, '"');
		it->descrip.erase(it->descrip.begin());
		in >> it->consumable >> it->type >> it->hp >> it->mana >> it->alive;
		item_list[i] = it;
		it = nullptr;
	}
}
void engine::read_character( istream &in )
{
	int i;
	character* ch = nullptr;
	int id, hp, mana, xpos, ypos;
	string name;
	string descrip;
	in >> num_chars;
	characters = new character*[num_chars]{nullptr};

	// first character is always player

	for ( i = 0; i < num_chars; i++)
	{
		in >> id;
		getline(in, name, '"');
		name.erase( name.begin());
		getline(in, descrip, '"');
		descrip.erase(descrip.begin());
		in >> hp >> mana >> xpos >> ypos;
		if ( i > 0 )
		{
            ch = new character(id, name, descrip, hp, mana, xpos, ypos );
        }
        else
        {
            ch = new player(id, name, descrip, hp, mana, xpos, ypos );
        }
		characters[i] = ch;
		ch = nullptr;
	}
}
void engine::read_tile( istream &in)
{
	int i, id, hp, mana, key;
	bool life, pass, item_pass, condition;
	tile* ti = nullptr;
	string name;
	string descrip;
	char effect;

	in >> num_tiles;
	tile_list = new tile*[num_tiles]{nullptr};

	for ( i = 0; i < num_tiles; i++)
	{
		in >> id;
		getline(in, name, '"');
		name.erase( name.begin());
		getline(in, descrip, '"');
		descrip.erase(descrip.begin());
		in >> hp >> mana >> life >> pass >> item_pass >> condition
		   >> effect >> key;
		ti = new tile(id, name, descrip, hp, mana, life, pass,
					  item_pass, condition, effect, key );
		tile_list[i] = ti;
		ti = nullptr;
	}
}
void engine::read_map( istream &in )
{
	int height, width;
	in >> height >> width;
	grid = new tile_map( height, width);
	grid->read( in, tile_list);
}
engine::~engine()
{
	int i = 0;
	tile* ptr = nullptr;
	character* q = nullptr;
	item* r = nullptr;
	delete grid;
	for (i = 0; i < num_tiles; i++)
	{
		ptr = tile_list[i];
		tile_list[i] = nullptr;
		delete ptr;
	}
	delete[] tile_list;

	for ( i = 0; i < num_chars; i++ )
	{
		q = characters[i];
		characters[i] = nullptr;
		delete q;
	}
	delete[] characters;

	for ( i = 0; i < num_items; i++ )
	{
		r = item_list[i];
		item_list[i] = nullptr;
		delete r;
	}
	delete[] item_list;
	delete[] warmap;
}
void engine::step()
{
    tile* t = nullptr;
	int i, char_x, char_y;
	char dir;
	defog();
	for ( i = 0; i < num_chars; i++ )
	{
		dir = characters[i]->dir();
		char_x = characters[i]->getx();
		char_y = characters[i]->gety();
		// move the position to the desired position
		switch ( dir )
		{
			case 'w':	char_x--;
						break;
			case 's':	char_x++;
						break;
			case 'd':	char_y++;
						break;
			case 'a':	char_y--;
						break;
		}
		// have the tile at the desired position affect the character
		// if it can be moved onto, update character position
		t = grid->_at( char_x, char_y );
		if ( t != nullptr && t->affect(characters[i]) )
		{
            characters[i]->update_pos( char_x, char_y );
            t = nullptr;
		}
	}
	if (!pc->get_alive())
	{
	cout << "updating" << endl;
		_end = true;
	}
	if ( grid->_at(pc->getx(), pc->gety()) == goal )
	{
		_end = true;
	}
	defog();
}
bool engine::over()
{
	return _end;
}
bool engine::player_dead()
{
	return !(pc->get_alive());
}
string engine::player_tile()
{
    tile* t = grid->_at(pc->getx(), pc->gety());
	return t != nullptr ? t->get_name() : "Error";
}
int engine::player_x()
{
	return pc->getx();
}
int engine::player_y()
{
	return pc->gety();
}
void engine::Print(ostream& out )
{
    int i = 0, j = 0;
    /*// print item list
    for ( i = 0; i < num_items; i++ )
    {
        out << item_list[i]->name << ": " << item_list[i]->descrip << " id: "
            << item_list[i]->id << " hp:" << item_list[i]->hp << " mana:"
            << item_list[i]->mana << " life:" << item_list[i]->alive << " cons:"
            << item_list[i]->consumable << " type:" << item_list[i]->type << endl;
    }
    // print tile list
    for ( i = 0; i < num_tiles; i++ )
    {
        out << tile_list[i]->get_name() << ": " << tile_list[i]->get_desc()
            << endl;
    }
    // print character list
    for ( i = 0; i < num_chars; i++ )
    {
        out << characters[i]->getname() << ": " <<  characters[i]->getdescrip()
            << ": " << characters[i]->get_id() << endl;
    }
    */
    // print map
    //grid->Print( out, pc->getx(), pc->gety() );
    for ( i = 0; i < grid->geth(); i ++ )
    {
        for ( j = 0; j < grid->getw()-1; j++ )
        {
            if ( i != pc->getx() || j != pc->gety() )
            {
                out << warmap[i*grid->getw() + j ] << ' ';
            }
            else
            {
                out << "X ";
            }
        }
        if ( i != pc->getx() || j != pc->gety() )
        {
            out << warmap[i*grid->getw() + j ] << endl;
        }
        else
        {
            out << 'X' << endl;
        }

    }
}
void engine::defog()
{
    // starting ewith the tile pc is on, then going clockwise around the
    // tiles directly touching them, unfog the warmap.
    static int x[FOG_TILES] = {0, -1, 0, 1, 0};
    static int y[FOG_TILES] = {0, 0, 1, 0, -1};
    tile* ti = nullptr;
    char temp = '0';
    for (int i = 0; i < FOG_TILES; i++ )
    {
        ti = grid->_at(pc->getx()+x[i], pc->gety()+y[i]);
        if ( ti != nullptr)
        {
            temp += ti->get_id();
            warmap[(pc->getx()+x[i])*grid->getw() + (pc->gety()+y[i])] = temp;
            temp = '0';
        }
    }
}
