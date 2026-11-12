//
// engine.h
//
// Davin Benson
// CS301 Project
// 10/10/19
//
#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#include <fstream>
#include "item.h"
#include "character.h"
#include "tile.h"
#include "tile_map.h"
#include "player.h"
using namespace std;

class engine
{
private:
	int num_items;
	int num_chars;
	int num_tiles;
	item** item_list;
	tile** tile_list;
	tile_map* grid;
	char* warmap;
	character** characters;
	character* pc;
	tile* goal;
	bool _end;
	void read_item(istream& item_in);
	void read_character(istream& character_in);
	void read_tile(istream& tile_in);
	void read_map(istream& map_in);
	//
public:
	engine();
	engine(istream& item_in, istream& character_in, istream& tile_in,
		   istream& map_in);
	~engine();
	void step();
	bool over();
	bool player_dead();
	string player_tile();
	int player_x();
	int player_y();
	void Print(ostream& out);
	void defog();
	// what does the engine do?
};

#endif // ENGINE_H_INCLUDED


using namespace std;
