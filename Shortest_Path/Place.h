#ifndef __PLACE
#define __PLACE

#include <string>

using std::string;

class Place
{
public:

	Place(int code, string abb, string name, int pop, double area, double lat, double longitude, int intersection, double distToIntersection);

	void print();

	int getNumCode();
	string getStateAbb();
	string getName();
	int getPopulation();
	double getArea();
	double getLatitude();
	double getLongitude();
	int getRoadIntersection();
	double getDistToIntersection();

protected:

	int numCode;
	string stateAbb;
	string name;
	int population;
	double area;
	double latitude, longitude;
	int roadIntersection;
	double distToIntersection;
};

#endif