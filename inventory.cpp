//
// inventory.cpp
//
// Keith Mehl
// 1/31/17
// A simple single linked ordered list class
//
//
// Davin Benson
// 5/14/19
// tweaking to use UN_FILE objects for a simplified UNIX-like file system
// CS20 assign 5 (Final Project)
//
// Davin Benson
// 9/30/19
// tweaking once more to use as a roster for a gradebook
//
//
// Davin Benson
// 10/15/19
// Tweaking once more to be an inventory of item structs
//
// Plan to next turn this into a template class (maybe)
#include "item.h"
#include "inventory.h"
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

const int inventory::Forward = 1;
const int inventory::Reverse = -1;

// create a new empty inventory
inventory::inventory( void )
{
    head = NULL;  // no elements yet
    free = NULL;  // no carriers yet
    trav_p = NULL;
    iterateOK = false;  // cannot iterate yet
}

// allocate storage for a carrier node, unless one is stashed on free list
inventory::LISTEL *inventory::getListEl( void )
{
    LISTEL *p;
    if( free != NULL )
    {
        p = free;
        free = free->next;
    }
    else
    {
        p = new LISTEL;
    }
    p->ptr = NULL;
    p->next = NULL;
    return p;
}

// 'deallocate' carrier node storage
// actually just stash it on free list for reuse later
void inventory::freeListEl( inventory::LISTEL *p )
{
    p->next = free;
    p->ptr = NULL;
    free = p;
    return;
}

// destructor - free all carrier **and data** nodes
// This is the only place where the List touches data (except looking at key)
inventory::~inventory( void )
{
    Empty();
}
void inventory::Empty( void )
{
    LISTEL *p = head, *q;
    while( p != NULL )
    {
        q = p;
        p = p->next;    // here and in an init() method are the
        delete q->ptr;  // only times the list routines change the data!
        delete q;
    }
    p = free;
    while( p != NULL )    // remember to clean out the free list too
    {
        q = p;
        p = p->next;
        delete q;
    }

    head = NULL;  // no elements yet
    free = NULL;  // no carriers yet
    trav_p = NULL;
    iterateOK = false;  // cannot iterate yet
}
#if 0
// print a single element.  This could have an ostream & parameter too
void inventory::PrintRevHelper( LISTEL *p )
{
    if( p != NULL )
    {
        PrintRevHelper( p->next );
        // in a "real" OO environment, we could use a "call-back"
        // function into the client here to print the data...
        // e.g., use a class with a data print method or an operator <<
        cout << p->ptr->key << '\t' << p->ptr->data << endl;
    }
    return;
}
#endif
// add an element at its ordered position into the list
void inventory::AddEl( item *e )
{
    LISTEL *d = getListEl();
    LISTEL *p, *q;
    iterateOK = false;  // if inside a traversal now, stop it
    d->ptr = e;
    // "inchworm" down the list to find insert position
    // notice the comma operator ',' to separate initialization
    // and progress statements in the loop
    for( p = head, q = NULL;
         p != NULL &&  p->ptr->id < d->ptr->id ; // changed
         q = p, p = p->next );
    if( q == NULL )  // empty or before first element
    {
        d->next = head;
        head = d;
    }
    else              // inside list or after last element
    {
        d->next = p;
        q->next = d;
    }
    return;
}

// remove the first match to key (may have duplicates)
item *inventory::removeByKey( int num )
{
    LISTEL*p = head, *q = NULL;
    item *d;
    while( p != NULL && p->ptr->id != num) // changed
    {
        q = p;
        p = p->next;
    }
    if( p == NULL )
    {
        return NULL;  // indicate key not found
    }
    else if( q == NULL )
    {
        head = head->next;
    }
    else
    {
        q->next = p->next;
    }
    d = p->ptr;          // remove data to return to client
    freeListEl( p );     // don't delete carrier here to manage fragmentation
    iterateOK = false;  // if inside a traversal now, stop it
    return d;
}
#if 0
// print the list, given a direction
// this would normally have a ostream & parameter too
void inventory::PrintList( int direction )
{
    LISTEL *p = head;
    if( direction == Forward )
    {
        while( p != NULL )
        {
            // in a "real" OO environment, we would use a "call-back"
            // method or operator << into the client here to print the data...
            cout << p->ptr->key << '\t' << p->ptr->data << endl;
            p = p->next;
        }
    }
    else // reverse
    {
        PrintRevHelper( p );
    }
    return;
}
#endif
// return true if the key is in the list
int inventory::IsInList( int num )
{
    LISTEL *p = head;
    while( p != NULL && p->ptr->id != num) // changed
    {
        p = p->next;
    }
    return p != NULL && p->ptr->id == num; // changed
}

int inventory::IsEmpty( void )
{
    return head == NULL;
}

// iterator, either first call or subsequent call, returns pointer to
// element's data or NULL if we've iterated off the list or list is empty
item * inventory::iterate( int first )
{
    if( first )
    {
        trav_p = head;
        iterateOK = true;
    }
    else if( iterateOK == false )      // no traversal if list changed
    {
        return NULL;                     // since start of last traversal
    }
    else if( trav_p != NULL )
    {
        trav_p = trav_p->next;
    }
    if( trav_p != NULL )    // trav_p points to carrier, return data
    {
        return trav_p->ptr;
    }
    return NULL;
}

// return a pointer to the first match to key (may have duplicates)
item *inventory::PeekByKey( int num )
{
    LISTEL*p = head;
    while( p != NULL && p->ptr->id != num) // changed
    {
        p = p->next;
    }
    if( p == NULL )
    {
        return NULL;  // indicate key not found
    }
    return p->ptr;
}

void inventory::Print( ostream &out )
{
    item* ptr = iterate(true);
    while ( ptr != nullptr )
    {
        out << ptr->name << ": " << ptr->descrip << "id: " << ptr->id << endl;
        ptr = iterate(false);
    }
    out << endl;
}
ostream &operator <<( ostream &out, inventory &i)
{
    i.Print(out);
    return out;
}
