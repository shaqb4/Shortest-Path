#include "MinHeap.h"
#include <iostream>

/*
* Initialize the vecor with a nullptr at the 0 index because the heap starts at index 1
*/
MinHeap::MinHeap() : size(1), numItems(0)
{
	heap.push_back(nullptr);
}

/*
* Swap the nodes at the two indeces
*/
void MinHeap::swap(int a, int b)
{
	Node* temp = heap[a];
	heap[a] = heap[b];
	heap[b] = temp;
}

/*
* Add an item to the heap
*/
void MinHeap::push(Node* item)
{
	numItems++;
	heap.push_back(item);
	item->setIndex(numItems);
	sortUp(item);

}

/*
* Remove the item with the lowest priority from the top of the heap and return it.
*/
Node* MinHeap::pop()
{
	Node* top = heap[1];
	Node* end = heap[numItems];
	swap(top->getIndex(), end->getIndex());
	heap.pop_back();
	
	int temp = top->getIndex();
	top->setIndex(end->getIndex());
	end->setIndex(temp);
	
	numItems--;

	sortDown(end);

	return top;
}

/*
* Update the priority of an item and make sure the heap is still a heap.
*/
void MinHeap::update(Node* item, double newPriority)
{
	item->setPriority(newPriority);
	sortUp(item);
}

/*
* Starting from item and going up, make sure the heap is still a heap.
*/
void MinHeap::sortUp(Node* item)
{
	int index = item->getIndex() / 2;
	Node* parent = heap[index];
	while (index != 0 && parent->getPriority() > item->getPriority())
	{
		swap(parent->getIndex(), item->getIndex());
		int temp = parent->getIndex();
		parent->setIndex(item->getIndex());
		item->setIndex(temp);

		index = item->getIndex() / 2;
		parent = heap[index];
	}
}

/*
* Starting from item and going down, make sure the heap is still a heap. It continues until there are no more children or the item is in the correct position.
*/
void MinHeap::sortDown(Node* item)
{
	Node* l, *r, *least;
	
	if (item->getIndex() * 2 > numItems)
	{
		l = nullptr;
		r = nullptr;
	}
	else if (item->getIndex() * 2  == numItems)
	{
		l = heap[item->getIndex() * 2];
		r = nullptr;
	}
	else
	{
		l = heap[item->getIndex() * 2];
		r = heap[item->getIndex() * 2 + 1];
	}

	least = l;

	while (l != nullptr)
	{
		if (r == nullptr)
		{
			//l is the only child, so swap it if neccessary
			if (l->getPriority() < item->getPriority())
			{
				swap(item->getIndex(), l->getIndex());
				int temp = item->getIndex();
				item->setIndex(l->getIndex());
				l->setIndex(temp);
			}
			break;	
		}

		//set least to the child with lowest priority
		if (r->getPriority() < l->getPriority())
		{
			least = r;
		}
		
		//Swap least if neccessary
		if (least->getPriority() < item->getPriority())
		{
			swap(item->getIndex(), least->getIndex());
			int temp = item->getIndex();
			item->setIndex(least->getIndex());
			least->setIndex(temp);
		}
		else
		{
			break;
		}
		
		if (item->getIndex() * 2 > numItems)
		{
			l = nullptr;
			r = nullptr;
		}
		else if (item->getIndex() * 2 == numItems)
		{
			l = heap[item->getIndex() * 2];
			r = nullptr;
		}
		else
		{
			l = heap[item->getIndex() * 2];
			r = heap[item->getIndex() * 2 + 1];
		}
		least = l;
	}
}

void MinHeap::print()
{
	for (int i = 1; i <= numItems; i++)
	{
		std::cout << "(" << heap[i] << ") " << heap[i]->getName() << ", " << heap[i]->getState() << ": " << heap[i]->getPriority() << "\n";
	}
}

bool MinHeap::empty()
{
	return numItems == 0;
}