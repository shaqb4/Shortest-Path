#include "Utility.h"

using std::string;

/*
* Return the specified string as all lowercase
*/
string Utility::toLowercase(string s)
{
	string lower = "";
	int length = s.length();

	for (int i = 0; i < length; i++)
	{
		lower += tolower(s[i]);
	}

	return lower;
}