#include "HashTable.h"

HashTable::HashTable()
{
	this->size = 10000;
	this->numItems = 0;
	this->table = new HashList[size];
}

HashTable::~HashTable()
{
	delete[] this->table;
}

void HashTable::add(Place * place)
{
	int x = stringHash(Utility::toLowercase(place->getName()));
	table[x].add(place);
	
	numItems++;
	if ((double)numItems / size > 1.0)
	{
		resize();
	}
}

int HashTable::getSize()
{
	return this->size;
}

int HashTable::getNumItems()
{
	return this->numItems;
}

HashList& HashTable::getTableIndex(int i)
{
	return this->table[i];
}

unsigned int HashTable::stringHash(string s)
{
	unsigned int h = 278364;
	int len = s.length();
	for (int i = 0; i < len; i += 1)
	{
		h = h * 69 + s[i];
	}
	return h % this->size;
}

/*
* Resize the table and rehash all items/places.
*/
void HashTable::resize()
{
	int oldSize = size;
	size *= 2;

	HashList *temp = table;
	HashLink * ptr = nullptr;
	table = new HashList[size];
	for (int i = 0; i < oldSize; i++)
	{
		ptr = temp[i].getFirst();
		while (ptr != nullptr)
		{
			this->add(ptr->getPlace());
			ptr = ptr->getNext();
		}
	}
	delete[] temp;
	delete ptr;
}