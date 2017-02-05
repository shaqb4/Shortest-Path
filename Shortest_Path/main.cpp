#include "Utility.h"
#include "HashTable.h"
#include "DigitalElevationModel.h"
#include "InteractiveMapDisplay.h"
#include "MinHeap.h"
#include "Place.h"
#include "Node.h"
#include "Road.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <time.h>

using std::string;
using std::cout;
using std::ifstream;
using std::stringstream;
using std::getline;
using std::cin;


/*
Take a line from the named-places.txt file and create a Place from the information it contains.
*/
Place * createPlaceFromLine(string line)
{
	string temp = "";
	int pos = 0;

	int code = atoi(line.substr(0, 8).c_str());

	string abb = line.substr(8, 2);

	//set pos to position of end of name
	pos = line.find("  ");
	string name = line.substr(10, pos - 10);

	pos = line.find_first_not_of(' ', pos);

	for (; pos < 66; pos++)
		temp += line[pos];
	int population = atoi(temp.c_str());
	temp = "";

	for (; pos < 80; pos++)
		temp += line[pos];
	double area = atof(temp.c_str());
	temp = "";

	stringstream ss2;
	for (; pos < 90; pos++)
		temp += line[pos];
	double latitude = atof(temp.c_str());
	temp = "";

	for (; pos < 101; pos++)
		temp += line[pos];
	double longitude = atof(temp.c_str());
	temp = "";

	for (; pos < 106; pos++)
		temp += line[pos];
	int intersection = atoi(temp.c_str());
	temp = "";

	for (; pos < line.length(); pos++)
		temp += line[pos];
	double dist = atof(temp.c_str());
	temp = "";

	Place *place = new Place(code, abb, name, population, area, latitude, longitude, intersection, dist);

	return place;
}

/*
* Prompt the user for a location and return the HashLink that stores the specified place
*/
HashLink * getUserLocation(HashTable &hashTable, string prompt)
{
	HashLink * location = nullptr;
	cout << prompt <<":\n";

	string name = "", state = "";
	getline(cin, name);

	int x = hashTable.stringHash(Utility::toLowercase(name));
	if (hashTable.getTableIndex(x).countItemsWithName(name) > 1)
	{
		hashTable.getTableIndex(x).displayByName(name);
		cout << "The previous locations have the name you specified. Please type the state abbreviation of the one you want."
			<< "If you don't see the state you want, make sure you spelled your location correctly.\n\n";
		cin >> state;
		location = hashTable.getTableIndex(x).findByNameAndState(name, state);

		cin.clear();
		cin.ignore();
	}
	else
	{
		location = hashTable.getTableIndex(x).findByName(name);
	}

	return location;
}

void shortestPath(Node* start, Node* dest)
{
	MinHeap PQ;
	PQ.push(start);
	
	while (!PQ.empty())
	{
		Node* current = PQ.pop();
		current->setIndex(-1);
		
		if (current == dest)
		{
			break;
		}

		for (int i = 0; i < current->getNumExits(); i++)
		{
			Road* exit = current->getExit(i);
			double newBestDist = current->getBestDistance() + exit->getLength();
			
			Node* child = exit->getNodeB();
			if (child == current)
			{
				child = exit->getNodeA();
			}

			if (child->getIndex() == 0) //If index is 0, child has not been visited yet
			{
				child->setBestDistance(newBestDist);
				PQ.push(child);
			}
			else if (newBestDist > child->getBestDistance())
			{	}
			else if (child->getIndex() != -1) //If index is -1, child has already been popped from PQ and can't be updated
			{
				PQ.update(child, newBestDist);
			}
		}
	}
}


void main()
{
	string baseDir = "C:\\Users\\shahk_000\\Documents\\College\\UMiami\\EEN318\\geography";

	cout.precision(9);

	HashTable table;

	ifstream file(baseDir+"\\named-places.txt");
	string line = "";

	while (getline(file, line))
	{
		Place *place = createPlaceFromLine(line);

		table.add(place);
	}

	HashLink * location1, *location2;
	location1 = getUserLocation(table, "Please enter the name of your destination city");
	
	location2 = getUserLocation(table, "Please enter the name of the city you're starting at");


	if (location1 == nullptr)
	{
		cout << "The first location isn't in the database.\n";
	}
	else if (location2 == nullptr)
	{
		cout << "The second location isn't in the database.\n";
	}
	else
	{
		double lat1 = location1->getPlace()->getLatitude();
		double long1 = location1->getPlace()->getLongitude();
		double lat2 = location2->getPlace()->getLatitude();
		double long2 = location2->getPlace()->getLongitude();

		//InteractiveMapDisplay deals with getting the neccessary input, reading the files, and drawing the map. 
		InteractiveMapDisplay mapDisplay(baseDir, lat1, long1, lat2, long2, location1->getPlace()->getName(), location2->getPlace()->getName());
		bool success;
		string message = "";

		success = mapDisplay.openDatFile();

		if (!success)
		{
			if (message == "")
				message = "failed to open file.\n";
		}
		else
			success = mapDisplay.readModelFromDummyLine();

		if (!success)
		{
			if (message == "")
				message = "failed to read dummy line.\n";
		}
		else
			success = mapDisplay.drawMap();

		if (!success)
		{
			if (message == "")
				message = "failed to draw map.\n";
		}

		cout << message;

		/*------------------ Shortest Path code starts here ----------*/

		clock_t t1 = clock();

		ifstream fIntersections(baseDir + "\\intersections.txt");
		ifstream fConnections(baseDir+"\\connections.txt");

		vector<Node*> intersections;

		//Create all of the intersections as Nodes and store them in a vector. Their index in the vector is the same as their line number intersections.txt
		while (getline(fIntersections, line))
		{
			double lat, lon, dist;
			string state, name;

			istringstream str(line);
			str >> lon >> lat >> dist >> state;
			getline(str, name);
			if (!str.fail())
			{
				Node* n = new Node(name, dist, lat, lon, state);
				intersections.push_back(n);
			}
		}
		
		//Create the Roads containing the Nodes/intersections that they connect. Then Add the Road to those same Nodes as exits.
		while (getline(fConnections, line))
		{
			string name, type;
			double length;
			int A, B;

			istringstream str(line);
			str >> name >> type >> A >> B >> length;
			if (!str.fail())
			{
				Road* r = new Road(name, type, length);
				Node* nodeA = intersections[A];
				Node* nodeB = intersections[B];
				r->setNodeA(nodeA);
				r->setNodeB(nodeB);

				nodeA->addExit(r);
				nodeB->addExit(r);
			}
			
		}

		//Get the start and destination Nodes/intersections from the locations that the user specified.
		//Note: these are the start & destination NODES used for shortest path algorithm, not the start and destination locations
		Node* start = intersections[location1->getPlace()->getRoadIntersection()];
		Node* dest = intersections[location2->getPlace()->getRoadIntersection()];
		cout << "\n\nStart: " << dest->getName() << ", " << dest->getState() << "\n";
		cout << "Destination: " << start->getName() << ", " << start->getState() << "\n\n";

		//Call the shortest path algorithm
		shortestPath(start, dest);

		//Create two vectors to store the latitudes and longitudes, respectively, of the intersections in the shortest path.
		vector<double> lats, lons;

		lats.push_back(location2->getPlace()->getLatitude()); 
		lons.push_back(location2->getPlace()->getLongitude());

		//Start from the destination node and work backwards to start. Print out directions as it goes and add lat. and long. coordinates.
		Node* n = dest;
		string prevRoadName = "";
		double roadDist = 0.0;
		double totalDist = 0.0;

		while (n != start)
		{			
			//Add the coordinates.
			lats.push_back(n->getLatitude());
			lons.push_back(n->getLongitude());

			//Loop through the exits and get the proper one by tracing back
			for (int i = 0; i < n->getNumExits(); i++)
			{
				Road* exit = n->getExit(i);

				Node* child = exit->getNodeB();
				if (child == n)
				{
					child = exit->getNodeA();
				}

				//Since the distance values are doubles, use a small buffer for equality
				if (std::abs((n->getBestDistance() - exit->getLength()) - child->getBestDistance()) < .001)
				{
					n = child;
					
					//Print the inital directions to the first node.
					if (totalDist == 0)
					{ 
						cout << "Go " << location2->getPlace()->getDistToIntersection() << " miles to get to intersection " << exit->getName() << ".\n";
						totalDist += location2->getPlace()->getDistToIntersection();
					}

					string roadName = exit->getName();
					if (roadName == "?")
					{
						roadName = "the road";
					}

					//If the same road occurs multiple times in a road, sum up the distances and output the directions when a the road changes
					if (prevRoadName == "" || roadName == prevRoadName)
					{
						roadDist += exit->getLength();
					}
					else if (roadName != prevRoadName)//The road changed, so output directions
					{
						cout << "Follow " << prevRoadName << " for " << roadDist << " miles\n";
						roadDist = exit->getLength();
						
					}
					//Output the last set of directions
					if (n == start)
					{
						cout << "Follow " << roadName << " for " << roadDist << " miles\n";
					}
					
					totalDist += exit->getLength();
					prevRoadName = roadName;
					
					break;
				}
			}
		}

		//Output how far the last intersection is from the target destination
		totalDist += location1->getPlace()->getDistToIntersection();
		cout << "You are " << location1->getPlace()->getDistToIntersection() << " miles from " << location1->getPlace()->getName() << ".\n";

		cout << "The total distance is " << totalDist << " miles.\n";

		//Take the vectors with the coordinates and draw the path on the map.
		mapDisplay.drawPath(lats, lons);

		fIntersections.close();
		fConnections.close();

		clock_t t2 = clock();

		cout << "\n\nIt took " << (t2 - t1) / CLOCKS_PER_SEC << " seconds for the shortest path to complete. This includes reading in the data files and initializing the graph.\n\n";
	}
}