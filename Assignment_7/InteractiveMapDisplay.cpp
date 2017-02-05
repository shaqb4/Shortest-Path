#include "library.h"
#include "InteractiveMapDisplay.h"
#include "DigitalElevationModel.h"

/*
* Get the name of the smallest .dat file based on the user locations and using coverage.txt.
*
*/
std::string InteractiveMapDisplay::getMinTileFileName()
{
	int minLatRange = 0;
	int minLongRange = 0;
	std::string minTileFileName;
	std::string coverageFile = this->baseDirectory + "\\coverage.txt";

	ifstream coverage(coverageFile);
	std::string line, fileName = "";
	int currentLat1, currentLat2, currentLong1, currentLong2;

	std::getline(coverage, line);
	while (!coverage.fail())
	{
		istringstream iss(line);

		iss >> currentLat1 >> currentLat2 >> currentLong1 >> currentLong2 >> fileName;
		if ((this->userLat1 <= currentLat1 && this->userLat1 >= currentLat2) && (this->userLat2 <= currentLat1 && this->userLat2 >= currentLat2)
			&& (this->userLong1 >= currentLong1 && this->userLong1 <= currentLong2) && (this->userLong2 >= currentLong1 && this->userLong2 <= currentLong2))
		{
			int latRange = currentLat1 - currentLat2, longRange = currentLong2 - currentLong1;


			if ((minLatRange == 0 || minLongRange == 0) || (latRange*longRange < minLatRange*minLongRange))
			{
				minLatRange = latRange;
				minLongRange = longRange;
				minTileFileName = this->baseDirectory + "\\geo_bin\\" + fileName;
			}
		}
		std::getline(coverage, line);
	}

	return minTileFileName;
}

/*
* Draw white dots where the user specified locations are.
*
*/
void InteractiveMapDisplay::drawUserLocations()
{
	set_pen_color(color::white);
	set_pen_width(8);

	double x1, y1, x2, y2;
	int strWidth = 0, strHeight = 0;

	x1 = ((this->userLong1 * 3600) - this->model->getLeftLongSeconds()) / (this->model->getSecondsPerPixel());
	y1 = (this->model->getTopLatSeconds() - (this->userLat1 * 3600)) / (this->model->getSecondsPerPixel());

	x2 = ((this->userLong2 * 3600) - this->model->getLeftLongSeconds()) / (this->model->getSecondsPerPixel());
	y2 = (this->model->getTopLatSeconds() - (this->userLat2 * 3600)) / (this->model->getSecondsPerPixel());

	draw_point(x1, y1);
	if (this->locName1 != "")
	{
		measure_string(this->locName2, strWidth, strHeight);
		if ((x1 + strWidth / 2) > this->model->getNumCols())
		{
			x1 = this->model->getNumCols() - (double)strWidth / 2 - get_pen_width();
		}
		else if ((x1 - strWidth / 2) < 0)
			x1 = strWidth / 2 + get_pen_width();

		move_to(x1, y1);

		if (y1 - strHeight < 0)
			write_string(this->locName1, direction::south);
		else
			write_string(this->locName1, direction::north);
	}


	draw_point(x2, y2);
	if (this->locName2 != "")
	{
		measure_string(this->locName2, strWidth, strHeight);
		if ((x2 + strWidth / 2) > this->model->getNumCols())
			x2 = this->model->getNumCols() - (double)strWidth / 2 - get_pen_width();
		else if ((x2 - strWidth / 2) < 0)
			x2 = strWidth / 2 + get_pen_width();

		move_to(x2, y2);

		if (y2 - strHeight < 0)
			write_string(this->locName2, direction::south);
		else
			write_string(this->locName2, direction::north);
	}
}

/*
* The baseDir is the directory on your computer that contains "coverage.txt" and the .dat files. The path of coverage.txt should be in "{baseDir}\coverage.txt".
* The .dat files should be in "{baseDir}\geo_bin\*.dat"
*
*/
InteractiveMapDisplay::InteractiveMapDisplay(std::string baseDir)
{
	this->baseDirectory = baseDir;
	this->model = nullptr;
	this->userLat1 = -1;
	this->userLat2 = -1;
	this->userLong1 = -1;
	this->userLong2 = -1;
	this->locName1 = "";
	this->locName2 = "";
}

InteractiveMapDisplay::InteractiveMapDisplay(std::string baseDir, double lat1, double long1, double lat2, double long2, std::string name1, std::string name2)
{
	this->baseDirectory = baseDir;
	this->model = nullptr;
	this->userLat1 = lat1;
	this->userLat2 = lat2;
	this->userLong1 = long1;
	this->userLong2 = long2;
	this->locName1 = name1;
	this->locName2 = name2;
}

InteractiveMapDisplay::~InteractiveMapDisplay()
{
	delete this->model;
	this->datFile.close();
}



/*
* Read the latitude and longitude of two locations from the user. Return true if successful, false otherwise.
*
*/
bool InteractiveMapDisplay::readInUserLocations()
{
	cout << "Enter the latitude and longitude of a place in North America.\nLatitude: ";
	cin >> this->userLat1;
	if (cin.fail())
	{
		return false;
	}
	cout << "Longitude: ";
	cin >> this->userLong1;
	if (cin.fail())
	{
		return false;
	}

	cout << "Enter the latitude and longitude of a second place in North America.\nLatitude: ";
	cin >> this->userLat2;
	if (cin.fail())
	{
		return false;
	}
	cout << "Longitude: ";
	cin >> this->userLong2;
	if (cin.fail())
	{
		return false;
	}

	return true;
}

/*
* Open the dat file reading the user input. Return true if successful, false otherwise.
*
*/
bool InteractiveMapDisplay::openDatFile()
{
	std::string fileName = this->getMinTileFileName();
	this->datFile.open(fileName, ios::in | ios::binary);
	if (this->datFile.fail())
	{
		return false;
	}

	return true;
}

/*
* Read the dummy line from the dat file and initialize the DigitalElevationModel. Return true if successful, false otherwise.
*
*/
bool InteractiveMapDisplay::readModelFromDummyLine()
{
	this->datFile.seekg(0, ios::beg);

	char* dummy = new char[200];

	this->datFile.read(dummy, 200);
	if (this->datFile.fail())
		return false;

	int i = 0;
	while (dummy[i] != '.')
	{
		i++;
	}
	dummy[i + 1] = '\0';

	std::string str(dummy);

	delete[] dummy;

	this->model = new DigitalElevationModel(str);

	return true;
}

/*
* Draw the map and the two user locations specified. Return true if successful, false otherwise.
*
*/
bool InteractiveMapDisplay::drawMap()
{
	this->datFile.seekg(2 * this->model->getNumCols(), ios::beg);

	make_window(this->model->getNumCols(), this->model->getNumRows());

	short int *elevation = new short int[this->model->getNumCols()];

	this->datFile.read((char *)elevation, 2 * this->model->getNumCols());
	int row = 0;
	float lowHue = 0.37, highHue = 0.0, currentHue;
	float lowLightness = .16, highLightness = .5, currentLightness;
	int numBytes = 0;

	while (!this->datFile.fail())
	{
		move_to(0, row);
		for (int i = 0; i < this->model->getNumCols(); i++)
		{
			if (elevation[i] == this->model->getSpecialValue())
			{
				set_pixel_color(i, row, color::blue);
			}
			else
			{
				//linear interpolation of low elevation and high elevation hls colors to produce a smooth gradient
				currentHue = (highHue - lowHue) * ((float)elevation[i] / this->model->getMax()) + lowHue;
				currentLightness = (highLightness - lowLightness) * ((float)elevation[i] / this->model->getMax()) + lowLightness;

				int elevationColor = make_color_hls(currentHue, currentLightness, 1);
				set_pixel_color(i, row, elevationColor);
			}
		}
		row++;
		numBytes = this->datFile.tellg();
		this->datFile.read((char *)elevation, 2 * this->model->getNumCols());
	}

	this->drawUserLocations();

	delete[] elevation;

	if (numBytes != 2 * (1 + this->model->getNumRows()) * this->model->getNumCols())
	{
		return false;
	}

	return true;
}

/*
* Given two vectors with coordinates for latitude and longitude, respectively, draw a path following the coordinates.
*/
void InteractiveMapDisplay::drawPath(vector<double> lats, vector<double> lons)
{
	set_pen_color(color::black);
	set_pen_width(2);

	double x1, y1, x2, y2;

	x1 = ((lons[0] * 3600) - this->model->getLeftLongSeconds()) / (this->model->getSecondsPerPixel());
	y1 = (this->model->getTopLatSeconds() - (lats[0] * 3600)) / (this->model->getSecondsPerPixel());

	move_to(x1, y1);

	for (int i = 1; i < lats.size(); i++)
	{
		x2 = ((lons[i] * 3600) - this->model->getLeftLongSeconds()) / (this->model->getSecondsPerPixel());
		y2 = (this->model->getTopLatSeconds() - (lats[i] * 3600)) / (this->model->getSecondsPerPixel());

		draw_to(x2, y2);
	}
}

/*
* Convert latitude and longitude coordinates to coordinates on the map window and draw a point there.
*/
void InteractiveMapDisplay::drawPoint(double lat, double lon)
{
	double x = ((lon * 3600) - this->model->getLeftLongSeconds()) / (this->model->getSecondsPerPixel());
	double y = (this->model->getTopLatSeconds() - (lat * 3600)) / (this->model->getSecondsPerPixel());
	
	set_pen_color(color::black);

	draw_point(x, y);
}