//
// item.h
//
// Davin Benson
// CS301 Project
//
#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include <string>
using namespace std;

struct item
{
    int id;
    string name; // name of the item
    string descrip; // description of item
    bool consumable; // whether the item is consumable or not
    char type; // h health, m mana, d death
    int hp; // hp effect, pos or neg
    int mana; // mana effect, pos or neg
    bool alive; // death effect, true or false (doesnt or does kill)
    // statistics for armor and eweapons? or other buffs?
};

#endif // ITEM_H_INCLUDED
