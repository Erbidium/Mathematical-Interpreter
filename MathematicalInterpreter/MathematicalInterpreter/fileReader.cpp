#include "fileReader.h"
#include "view.h"
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

vector<string> fileReader::readVariablesAndExpression(string fileName)
{
	vector<string> stringsFromFile;
	ifstream inFile(fileName);
	if(!inFile)
		view::unsuccessfulOpening();
	else
	{
		string tempStr;
		while (getline(inFile, tempStr))
		{
			if (tempStr.length() > 0) stringsFromFile.push_back(tempStr);
		}
	}
	inFile.close();
	return stringsFromFile;
}
