//
// tile.h
//
// Davin Benson
// CS301 Project
// 10/10/19
//
#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED
#include "character.h"
#include "inventory.h"
#include <string>
using namespace std;

class tile
{
private:
    int _id;
    string _name;
    string _descrip;
    inventory inv; // maybe
    int hp_effect;
    int mana_effect;
    bool life_effect;
    bool passable;
    bool item_passable;
    bool conditional_effect;
    char effect_type; // same as item for which letters are used
    int key_id;

public:
    tile();
    tile( int id, string name, string descrip, int hp, int mana,
		  bool life, bool pass, bool item_pass, bool condition,
		  char effect, int key);
	~tile();
    bool affect( character *chara );
    string get_name();
    string get_desc();
    int get_id();
};

#endif // TILE_H_INCLUDED
