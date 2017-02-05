#include "Place.h"

#include <iostream>

using std::cout;

Place::Place(int code, string abb, string name, int pop, double area, double lat, double longitude, int intersection, double distToIntersection)
{
	this->numCode = code;
	this->stateAbb = abb;
	this->name = name;
	this->population = pop;
	this->area = area;
	this->latitude = lat;
	this->longitude = longitude;
	this->roadIntersection = intersection;
	this->distToIntersection = distToIntersection;
}

void Place::print()
{
	cout << "Number Code: " << this->numCode << ", State Abbreviation: " << this->stateAbb << "\n";
	cout << "Name: " << this->name << ", Population: " << this->population << "\n";
	cout << "Area: " << this->area << ", (Latitude, Longitude): (" << this->latitude << ", " << this->longitude << ")\n";
	cout << "Intersection Number: " << this->roadIntersection << ", Distance to Intersection: " << this->distToIntersection << "\n";
}

int Place::getNumCode()
{
	return this->numCode;
}

string Place::getStateAbb()
{
	return this->stateAbb;
}

string Place::getName()
{
	return this->name;
}

int Place::getPopulation()
{
	return this->population;
}

double Place::getArea()
{
	return this->area;
}

double Place::getLatitude()
{
	return this->latitude;
}

double Place::getLongitude()
{
	return this->longitude;
}

int Place::getRoadIntersection()
{
	return this->roadIntersection;
}

double Place::getDistToIntersection()
{
	return this->distToIntersection;
}