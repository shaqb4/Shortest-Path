#ifndef __INTERACTIVEMAPDISPLAY
#define __INTERACTIVEMAPDISPLAY

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "DigitalElevationModel.h"

using std::string;
using std::ifstream;
using std::istringstream;


/**
* InteractiveMapDisplay deals with getting the neccessary input, reading the files, and drawing the map.
*
*/
class InteractiveMapDisplay
{
protected:
	std::string baseDirectory;
	ifstream datFile;
	DigitalElevationModel * model;
	double userLat1, userLat2, userLong1, userLong2;
	std::string locName1, locName2;

	/*
	* Get the name of the smallest .dat file based on the user locations and using coverage.txt.
	*
	*/
	std::string getMinTileFileName();

	/*
	* Draw white dots where the user specified locations are.
	*
	*/
	void drawUserLocations();

public:
	/*
	* The baseDir is the directory on your computer that contains "coverage.txt" and the .dat files. The path of coverage.txt should be in "{baseDir}\coverage.txt".
	* The .dat files should be in "{baseDir}\geo_bin\*.dat"
	*
	*/
	InteractiveMapDisplay(std::string baseDir);

	InteractiveMapDisplay(std::string baseDir, double lat1, double long1, double lat2, double long2, std::string name1, std::string name2);

	~InteractiveMapDisplay();

	/*
	* Read the latitude and longitude of two locations from the user. Return true if successful, false otherwise.
	*
	*/
	bool readInUserLocations();

	/*
	* Open the dat file reading the user input. Return true if successful, false otherwise.
	*
	*/
	bool openDatFile();

	/*
	* Read the dummy line from the dat file and initialize the DigitalElevationModel. Return true if successful, false otherwise.
	*
	*/
	bool readModelFromDummyLine();

	/*
	* Draw the map and the two user locations specified. Return true if successful, false otherwise.
	*
	*/
	bool drawMap();

	/*
	* Given two vectors with coordinates for latitude and longitude, respectively, draw a path following the coordinates.
	*/
	void drawPath(std::vector<double> lats, std::vector<double> lons);

	/*
	* Convert latitude and longitude coordinates to coordinates on the map window and draw a point there.
	*/
	void drawPoint(double lat, double lon);
};

#endif