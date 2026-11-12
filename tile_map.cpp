//
// tile_map.cpp
//
// Davin Benson
// 10/16/19
// CS301 Project
//
#include "tile_map.h"
#include <iostream>
#include <fstream>
#include "tile.h"

using namespace std;

tile_map::tile_map()
{
	_height = 10;
	_width = 10;
	_pos = new tile*[_width * _height]{nullptr};
}
tile_map::tile_map( int height, int width)
{
	_height = height;
	_width = width;
	_pos = new tile*[_width * _height]{nullptr};
}
tile_map::~tile_map()
{
	for ( int i = 0; i < _height; i++ )
	{
		for ( int j = 0; j < _width; j++)
		{
			// i*width elements down, and j elements to the right
			// this is from [0,0], the top left of the tile map
			// meaning [0,1] would be 0*_width elements down, and
			// 1 element to the right, making it be the first element
			// of the second "row"
			// the elements are merely pointers to tiles that are
			// housed elsewhere in the engine, so the map will not
			// delete the tiles.
			_pos[i * _width + j] = nullptr;
		}
	}
	delete[] _pos;
}

tile* tile_map::_at( int x, int y)
{
    tile* t = nullptr;
    if ( (x < _height) && (x >= 0) )
    {
        if ( (y < _width) && (y >= 0) )
        {
            t = _pos[x*_width + y];
        }
    }
    return t;
}

void tile_map::read( istream& in, tile** arr)
{
	int index = 0;
	for ( int i = 0; i < _height; i++ )
	{
		for ( int j = 0; j < _width; j++)
		{
			in >> index;
			// points the pointer at [i, j] to the correct tile in
			// the tile array.
			_pos[i * _width + j] = arr[index];
		}
	}
}
void tile_map::Print( ostream &out, int x, int y )
{
    int i, j;
	for ( i = 0; i < _height; i++ )
	{
		for ( j = 0; j < _width-1; j++)
		{
            if ( (i != x) || (j != y) )
            {
                out << _pos[i * _width + j]->get_id() << ' ';
            }
            else
            {
                out << "X ";
            }
		}
		out << _pos[i*_width +j]->get_id() << endl;
	}
}
int tile_map::geth()
{
    return _height;
}
int tile_map::getw()
{
    return _width;
}
