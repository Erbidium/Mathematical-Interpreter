#include "fileReader.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

using namespace std;

void fileReader::readVariablesAndExpression(string fileName, unordered_map<string, int>& variables, string &expression)
{
	ifstream inFile(fileName);
	if(!inFile)
		cout<<"Can't open the file!\n";
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
			//cout<<variableName<<'@'<<endl;
			string numberOfVariable=stringsFromFile[i].substr(indexOfName+3);
			numberOfVariable.pop_back();
			//cout<<numberOfVariable<<endl;
			variables.insert(make_pair(variableName, stoi(numberOfVariable)));
		}
		expression=stringsFromFile.back();
	}
	
	inFile.close();
}
