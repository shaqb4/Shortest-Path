#ifndef __ROAD
#define __ROAD

#include <string>

using std::string;

class Node;

class Road
{
public:
	Road(string name, string type, double length);

	void setNodeA(Node* n);
	Node* getNodeA();
	void setNodeB(Node* n);
	Node* getNodeB();

	double getLength();
	string getName();
	string getType();
protected:
	string name;
	string type;
	double length;
	Node* A;
	Node* B;
};

#endif