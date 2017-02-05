#include "HashList.h"

/*
* ---------------------------------- HashLink ------------------------------------------
*/

HashLink::HashLink(Place * place, HashLink * n)
{
	this->place = place;
	this->next = n;
}

Place* HashLink::getPlace()
{
	return this->place;
}

HashLink* HashLink::getNext()
{
	return this->next;
}

void HashLink::setNext(Place* p, HashLink* n)
{
	this->next = new HashLink(p, n);
}


/*
* ---------------------------------- HashList ------------------------------------------
*/


HashList::HashList()
{
	first = nullptr;
}

HashList::~HashList()
{
	HashLink * ptr = first;
	while (ptr != nullptr)
	{
		HashLink * n = ptr->getNext();
		delete ptr;
		ptr = n;
	}
}

void HashList::add(Place * place)
{
	bool exists = false;
	HashLink * ptr = first;
	while (ptr != nullptr)//Store places with the same name next to each other.
	{
		if (place->getName() == ptr->getPlace()->getName())
		{
			ptr->setNext(place, ptr->getNext());
			exists = true;
			break;
		}
		ptr = ptr->getNext();
	}
	if (!exists)
	{
		first = new HashLink(place, first);
	}
}

/*
* Print the all of the places with the specified name.
*/
void HashList::displayByName(string name)
{
	HashLink *ptr = first;
	while (ptr != nullptr)
	{
		if (Utility::toLowercase(ptr->getPlace()->getName()) == Utility::toLowercase(name))
			break;
		ptr = ptr->getNext();
	}
	while (ptr != nullptr && Utility::toLowercase(ptr->getPlace()->getName()) == Utility::toLowercase(name))
	{
		ptr->getPlace()->print();
		cout << "\n\n";
		ptr = ptr->getNext();
	}
	if (ptr == nullptr)
		cout << "That place was not in the file.\n";
}

int HashList::countItemsWithName(string name)
{
	int count = 0;
	HashLink *ptr = first;
	while (ptr != nullptr)
	{
		if (Utility::toLowercase(ptr->getPlace()->getName()) == Utility::toLowercase(name))
			break;
		ptr = ptr->getNext();
	}
	while (ptr != nullptr && Utility::toLowercase(ptr->getPlace()->getName()) == Utility::toLowercase(name))
	{
		count++;
		ptr = ptr->getNext();
	}

	return count;
}

HashLink* HashList::findByName(string name)
{
	HashLink *ptr = first;
	while (ptr != nullptr)
	{
		if (Utility::toLowercase(ptr->getPlace()->getName()) == Utility::toLowercase(name))
		{
			return ptr;
		}
		ptr = ptr->getNext();
	}
	return nullptr;
}

HashLink* HashList::findByNameAndState(string name, string state)
{
	HashLink *ptr = first;
	while (ptr != nullptr)
	{
		if (Utility::toLowercase(ptr->getPlace()->getName()) == Utility::toLowercase(name) && Utility::toLowercase(ptr->getPlace()->getStateAbb()) == Utility::toLowercase(state))
		{
			return ptr;
		}
		ptr = ptr->getNext();
	}
	return nullptr;
}

int HashList::length()
{
	int n = 0;
	HashLink * ptr = first;
	while (ptr != nullptr)
	{
		n += 1;
		ptr = ptr->getNext();
	}
	return n;
}

HashLink* HashList::getFirst()
{
	return this->first;
}