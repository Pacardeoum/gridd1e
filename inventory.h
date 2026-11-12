//
// inventory.h
//
// Keith Mehl
// 1/31/17
//
// Singly linked list example for a linked list with carriers
//
// Davin Benson
// 5/14/19
// tweaking to use UN_FILE objects for a simplified UNIX-like file system
// CS20 assign 5 (Final Project)
//
// Davin Benson
// 9/30/19
// Tweaking once more to use as a list of students in a gradebook
// CS 301 Assignment 4
//
// Davin Benson
// 10/15/19
// Tweaking once more to be inventory of items
//
#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

#include "item.h"

struct item;

class inventory
{
private:
    // the linked list routines manage the list "carrier" elements.
    // defined here in the class schema, the ROSTER class is the
    // only code that can see this struct at all.
    // this is "composition", vs. "aggregation" where a class is
    // defined outside the client class and then used within it.
    struct LISTEL
    {
		item *ptr;
        LISTEL *next;
    };

    LISTEL *head;         // the data in the user's list
    bool iterateOK;      // Is it OK to continue an iteration?
    inventory::LISTEL *free;   // maintain free list (reduce heap fragmentation)
    inventory::LISTEL *trav_p;       // for use by iterator
    inventory::LISTEL *getListEl( void );  // Get a carrier node
    void freeListEl( LISTEL *p ); // Free a carrier node
    //void PrintRevHelper( LISTEL *p );  // used for reverse print in PrintList()
public:
    static const int Forward;   // argument values for print direction in PrintList
    static const int Reverse;
    inventory( void );
    ~inventory( void );
    void Empty(void);
    void AddEl( item *e );  // add sorted in ascending order
    item *removeByKey( int num );
    item *PeekByKey( int num ); // peeks without removal
    //void PrintList( int direction );
    int IsInList(  int num );
    int IsEmpty( void );
    item *iterate( int first );  // iterator
    void Print(ostream &out);
	friend ostream &operator <<(ostream &out, inventory &i);
};

#endif // INVENTORY_H_INCLUDED
