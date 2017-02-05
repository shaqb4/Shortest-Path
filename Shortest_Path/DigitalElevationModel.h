#ifndef __DIGITALELEVATIONMODEL
#define __DIGITALELEVATIONMODEL

#include <string>

using std::string;

/*
* DigitalElevationModel holds the info that is in the dummy line at the beginnings of .dat files.
*
*/
class DigitalElevationModel
{
public:
	/*
	* Takes the dummy line as a parameter and parses the values from it.
	*/
	DigitalElevationModel(string dummyStr);

	int getNumRows();

	int getNumCols();

	int getBytesPerPixel();

	int getSecondsPerPixel();

	int getLeftLongSeconds();

	int getTopLatSeconds();

	int getMin();

	int getMax();

	int getSpecialValue();

	void print();

protected:
	int numRows, numCols, bytesPerPixel, secondsPerPixel, leftLongSeconds, topLatSeconds, min, max, specialVal;
};

#endif