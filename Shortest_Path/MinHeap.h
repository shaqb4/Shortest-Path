#ifndef __MINHEAP
#define __MINHEAP

#include "Node.h"
#include <vector>

class MinHeap
{
public:
	/*
	* Initialize the vecor with a nullptr at the 0 index because the heap starts at index 1
	*/
	MinHeap();

	/*
	* Add an item to the heap
	*/
	void push(Node* item);

	/*
	* Remove the item with the lowest priority from the top of the heap and return it.
	*/
	Node* pop();
	
	/*
	* Update the priority of an item and make sure the heap is still a heap.
	*/
	void update(Node* item, double newPriority);
	
	bool empty();
	
	void print();

protected:
	std::vector<Node*> heap;

	int size;
	int numItems;

	/*
	* Starting from item and going up, make sure the heap is still a heap.
	*/
	void sortUp(Node* item);

	/*
	* Starting from item and going down, make sure the heap is still a heap. It continues until there are no more children or the item is in the correct position.
	*/
	void sortDown(Node* item);

	/*
	* Swap the nodes at the two indeces
	*/
	void swap(int a, int b);
};

#endif