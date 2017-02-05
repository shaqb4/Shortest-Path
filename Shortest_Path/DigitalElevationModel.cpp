#include "DigitalElevationModel.h"
#include <iostream>
#include <sstream>

using std::istringstream;
using std::cout;

/*
* Takes the dummy line as a parameter and parses the values from it.
*/
DigitalElevationModel::DigitalElevationModel(string dummyStr)
{
	istringstream iss(dummyStr);
	string valName;
	int val, count = 0;
	iss >> valName;
	iss >> val;

	while (!iss.fail() && count < 9 && valName != ".")
	{
		if (valName == "rows")
			this->numRows = val;
		else if (valName == "columns")
			this->numCols = val;
		else if (valName == "bytesperpixel")
			this->bytesPerPixel = val;
		else if (valName == "secondsperpixel")
			this->secondsPerPixel = val;
		else if (valName == "leftlongseconds")
			this->leftLongSeconds = val;
		else if (valName == "toplatseconds")
			this->topLatSeconds = val;
		else if (valName == "min")
			this->min = val;
		else if (valName == "max")
			this->max = val;
		else if (valName == "specialval")
			this->specialVal = val;
		else
			break;

		iss >> valName;
		iss >> val;
		count++;
	}
}

int DigitalElevationModel::getNumRows()
{
	return this->numRows;
}

int DigitalElevationModel::getNumCols()
{
	return this->numCols;
}

int DigitalElevationModel::getBytesPerPixel()
{
	return this->bytesPerPixel;
}

int DigitalElevationModel::getSecondsPerPixel()
{
	return this->secondsPerPixel;
}

int DigitalElevationModel::getLeftLongSeconds()
{
	return this->leftLongSeconds;
}

int DigitalElevationModel::getTopLatSeconds()
{
	return this->topLatSeconds;
}

int DigitalElevationModel::getMin()
{
	return this->min;
}

int DigitalElevationModel::getMax()
{
	return this->max;
}

int DigitalElevationModel::getSpecialValue()
{
	return this->specialVal;
}

void DigitalElevationModel::print()
{
	cout << "rows " << this->numRows << " columns " << this->numCols << " bytesperpixel " << this->bytesPerPixel << " secondsperpixel " << this->secondsPerPixel
		<< " leftlongseconds " << this->leftLongSeconds << " toplatseconds " << this->topLatSeconds << " min " << this->min << " max " << this->max << " specialval "
		<< this->specialVal << " .\n";
}