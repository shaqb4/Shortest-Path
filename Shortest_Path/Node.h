#ifndef __NODE
#define __NODE

#include <string>
#include <vector>

using std::vector;

using std::string;

class Road;

class Node
{
public:
	Node(string name, double distNear, double lat, double lon, string st);

	double getBestDistance();
	void setBestDistance(double dist);
	
	double getDistToNearest();
	void setDistToNearest(double dist);

	/*
	* getPriority() just returns the bestDistance for the purpose of being used in the heap. I figured the heap would be easier to turn into a template or use inheritance later
	* if I used a general method like getPriority()
	*/
	double getPriority();
	
	/*
	* setPriority() just returns the bestDistance for the purpose of being used in the heap. I figured the heap would be easier to turn into a template or use inheritance later
	* if I used a general method like setPriority()
	*/
	void setPriority(double dist);

	int getIndex();
	void setIndex(int i);

	double getLatitude();
	double getLongitude();

	string getState();

	string getName();

	void addExit(Road* e);
	Road* getExit(int i);
	int getNumExits();
	
protected:
	vector<Road *> exits;
	double bestDistance;
	double distToNearest;
	int index;
	double latitude, longitude;
	string name, state;
};

#endif