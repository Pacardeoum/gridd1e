//
// tile.cpp
//
// Davin Benson
// 10/17/19
// CS301 Project
//

#include "tile.h"
#include <iostream>
using namespace std;

tile::tile()
{
	_id = -1;
	_name = "";
	_descrip = "";
	hp_effect = mana_effect = 0;
	life_effect = true;
	passable = false;
	item_passable = false;
	conditional_effect = false;
	effect_type = 'x';
	key_id = -2;
}
tile::~tile()
{

}
tile::tile( int id, string name, string descrip, int hp, int mana,
		  bool life, bool pass, bool item_pass, bool condition,
		  char effect, int key)
{
	_id = id;
	_name = name;
	_descrip = descrip;
	hp_effect = hp;
	mana_effect = mana;
	life_effect = life;
	passable = pass;
	item_passable = item_pass;
	conditional_effect = condition;
	effect_type = effect;
	key_id = key;
}
// returns true if the character is able to move onto the tile, false
// otherwise. If the character CAN move onto it, it will apply the
// appropriate affect to the character.
bool tile::affect( character *chara )
{
	bool ret = false;
	if ( passable )
	{
		ret = true;
		if ( item_passable && !(chara->has(key_id)) )
		{
			ret = false;
		}
	}
	if ( conditional_effect && chara->has(key_id) )
    {
    }
    else
    {
        switch (effect_type)
        {
            case 'h':	chara->modify_health( hp_effect);
                        break;
            case 'm':	chara->modify_mana( mana_effect );
                        break;
            case 'd':	chara->update_life( life_effect );
                        break;
            default:    break;
        }
    }
	return ret;
}
string tile::get_name()
{
	return _name; // might need to do some protection?
}
string tile::get_desc()
{
	return _descrip; //might need protection
}
int tile::get_id()
{
    return _id;
}
