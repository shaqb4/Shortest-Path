#include "Node.h"

Node::Node(string name, double distNear, double lat, double lon, string st)
{
	this->distToNearest = distNear;
	this->name = name;
	this->latitude = lat;
	this->longitude = lon;
	this->state = st;
	this->index = 0;
	this->bestDistance = 0;
}

string Node::getState()
{
	return this->state;
}

double Node::getBestDistance()
{
	return this->bestDistance;
}

void Node::setBestDistance(double dist)
{
	this->bestDistance = dist;
}

double Node::getDistToNearest()
{
	return this->distToNearest;
}

void Node::setDistToNearest(double dist)
{
	this->distToNearest = dist;
}

/*
* getPriority() just returns the bestDistance for the purpose of being used in the heap. I figured the heap would be easier to turn into a template or use inheritance later
* if I used a general method like getPriority()
*/
double Node::getPriority()
{
	return this->bestDistance;
}

/*
* setPriority() just sets the bestDistance for the purpose of being used in the heap. I figured the heap would be easier to turn into a template or use inheritance later
* if I used a general method like setPriority()
*/
void Node::setPriority(double dist)
{
	this->bestDistance = dist;
}

int Node::getIndex()
{
	return this->index;
}

void Node::setIndex(int i)
{
	this->index = i;
}

double Node::getLatitude()
{
	return this->latitude;
}

double Node::getLongitude()
{
	return this->longitude;
}

string Node::getName()
{
	return this->name;
}

void Node::addExit(Road* e)
{
	this->exits.push_back(e);
}

Road* Node::getExit(int i)
{
	return exits[i];
}

int Node::getNumExits()
{
	return exits.size();
}