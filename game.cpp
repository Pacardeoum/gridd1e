//
// game.cpp
//
// Davin Benson
// 10/16/19
// CS301 Project
//
#include <iostream>
#include "engine.h"
#include <fstream>
#include <string>
#define CMD_ARGS 5
#define CMD_ERR -1
#define IO_ERR -2
using namespace std;

int main ( int argc, char* argv[] )
{
	if ( argc < CMD_ARGS)
	{
		cout << "Usage: program item_file character_file tile_file"
		     << " map_file" << endl;
		return CMD_ERR;
	}

	ifstream item_infile (argv[1]);
	ifstream character_infile (argv[2]);
	ifstream tile_infile (argv[3]);
	ifstream map_infile (argv[4]);

	if ( !item_infile || !character_infile
		|| !tile_infile || !map_infile )
	{
		cout << "File Error!" << endl;
		return IO_ERR;
	}
	engine eng(item_infile, character_infile, tile_infile, map_infile);
	item_infile.close();
	character_infile.close();
	tile_infile.close();
	map_infile.close();
	string command = "";

	//input command
	// for now, this is just having the engine "step" which has it
	// iterate through the character list, calling each character's move
	// function (dir()) and dealing with their movement.
	// it then checks to see if the game is over
	eng.Print(cout);
	do
	{
		eng.step();
		cout << "You are standing on " << eng.player_tile() << endl;
		cout << "Your position is (" << eng.player_x() << ","
			 << eng.player_y() << ")" << endl << endl;
        eng.Print(cout);
	}while ( !eng.over() && command != "Quit" );

	if ( eng.player_dead() )
	{
		cout << "Game Over." << endl;
	}
	else
	{
		cout << "You Won! Congratulations!" << endl;
	}
	return 0;
}
