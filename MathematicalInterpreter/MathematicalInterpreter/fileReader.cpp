#include "fileReader.h"
#include "view.h"
#include <unordered_map>
#include <fstream>
#include <string>

using namespace std;

void fileReader::readVariablesAndExpression(string fileName, unordered_map<string, string>& variables, string &expression)
{
	ifstream inFile(fileName);
	if(!inFile)
		view::unsuccessfulOpening();
	else
	{
		vector<string> stringsFromFile;
		string tempStr;
		while(getline(inFile, tempStr))
		{
			stringsFromFile.push_back(tempStr);
		}
		for(int i=0;i<stringsFromFile.size()-1;i++)
		{
			int indexOfName=stringsFromFile[i].find('=')-1;
			string variableName=stringsFromFile[i].substr(0, indexOfName);
			string numberOfVariable=stringsFromFile[i].substr(indexOfName+3);
			numberOfVariable.pop_back();
			variables.insert(make_pair(variableName, numberOfVariable));
		}
		expression=stringsFromFile.back();
	}
	
	inFile.close();
}
