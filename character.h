//
// character.h
//
// Davin Benson
// C301 Project
//
#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

using namespace std;
#include <string>
#include <fstream>
#include "inventory.h"
#include "item.h"

class character
{
protected:
    int _id;
    string _name;
    string _descrip;
    inventory _inv;
    bool _alive;
    int _hp;
    int _mana;
    int _xpos;
    int _ypos;
public:
    character();
    character (int id, string name, string descrip, /*inventory inv,*/ int hp,
                int mana, int xpos, int ypos);
    ~character();

    int gethp();
    int getmana();
    int getx();
    int gety();
    int get_id();
    string getname();
    string getdescrip();
    bool get_alive();

    void sethp( int hp);
    void setmana(int mana);
    void update_pos ( int x, int y ); // changes position to x,y
    int modify_health(int val); // updates (adds) and returns health
    int modify_mana(int val); // updates (adds) and returns mana
    bool update_life(bool life); // updates (assigns) and returns life

    bool has(int item_num); // returns true if item by name is in inv
    bool use(int item_num); // uses an item by name
    void take ( item* it ); // likely best way to do this, so a tile
    // or a monster or such can call this on the character
    // definitely the least certain method
    // Adds the item it into its inventory.
    item *give(int item_num); // removes and returns (by pointer) item with id item_num from inventory
    virtual char dir(); // what direction the character chooses to move in
    void print_inv(fstream &out ); // prints inventory to out
    // virtual combat methods?

    // Attacks, other moves possible by the player here

};
#endif // CHARACTER_H_INCLUDED
