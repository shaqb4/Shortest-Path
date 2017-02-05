#include "Road.h"

Road::Road(string n, string t, double l)
{
	this->name = n;
	this->type = t;
	this->length = l;
	this->A = nullptr;
	this->B = nullptr;
}

void Road::setNodeA(Node* n)
{
	this->A = n;
}

Node* Road::getNodeA()
{
	return this->A;
}

void Road::setNodeB(Node* n)
{
	this->B = n;
}

Node* Road::getNodeB()
{
	return this->B;
}

double Road::getLength()
{
	return this->length;
}

string Road::getName()
{
	return this->name;
}

string Road::getType()
{
	return this->type;
}