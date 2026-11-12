//
// tile_map.h
//
// Davin Benson
// 10/16/19
// CS301 Project
//
#ifndef TILE_MAP_H_INCLUDED
#define TILE_MAP_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include "tile.h"
using namespace std;

class tile_map
{
private:
	int _height;
	int _width;
	tile** _pos;
public:
	tile_map();
	tile_map( int height, int width);
	~tile_map();
	tile* _at(int x, int y);
	void read( istream& in, tile** arr);
	void Print(ostream& out, int x, int y );
	int getw();
	int geth();
};

#endif // TILE_MAP_H_INCLUDED
