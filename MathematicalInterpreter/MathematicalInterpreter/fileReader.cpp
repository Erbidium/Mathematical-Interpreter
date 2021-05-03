#include "fileReader.h"
#include "view.h"
#include <unordered_map>
#include <fstream>
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
		while(getline(inFile, tempStr))
		{
			stringsFromFile.push_back(tempStr);
		}
	}
	inFile.close();
	return stringsFromFile;
}
