//
// player.h
//
// Davin Benson
//
// 10/16/19
// CS301 Project
//
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "character.h"
using namespace std;


class player : public character
{
protected:
public:
    player();
    player (int id, string name, string descrip, /*inventory inv,*/ int hp,
                int mana, int xpos, int ypos);
    ~player();
	virtual char dir();
};


#endif //PLAYER_H_INCLUDED
