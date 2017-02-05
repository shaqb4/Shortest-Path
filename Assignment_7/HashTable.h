#ifndef __HASHTABLE
#define __HASHTABLE

#include "HashList.h"
#include "Utility.h"


class HashTable
{
public:
	HashTable();

	~HashTable();

	void add(Place * place);

	int getSize();

	int getNumItems();
	
	HashList& getTableIndex(int i);

	unsigned int stringHash(string s);

protected:
	//The size of the array of linked lists (table property).
	int size;
	//The number of items in the hash table
	int numItems;
	//The array of linked lists
	HashList * table;

	/*
	* Resize the table and rehash all items/places.
	*/
	void resize();
};

#endif