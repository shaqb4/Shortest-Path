#ifndef __HASHLIST
#define __HASHLIST

#include "Place.h"
#include "Utility.h"
#include <iostream>

using std::cout;

class HashLink
{
public:
	HashLink(Place * place, HashLink * n);

	Place* getPlace();
	HashLink* getNext();
	void setNext(Place* p, HashLink* n);

protected:
	Place * place;
	HashLink * next;
};

class HashList
{
public:
	HashList();

	~HashList();

	void add(Place * place);

	/*
	* Print the all of the places with the specified name.
	*/
	void displayByName(string name);

	int countItemsWithName(string name);
	
	HashLink *findByName(string name);

	HashLink *findByNameAndState(string name, string state);

	int length();

	HashLink* getFirst();

protected:
	HashLink * first;

};

#endif