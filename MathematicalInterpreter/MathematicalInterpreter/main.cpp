#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include "fileReader.h"

using namespace std;

int main()
{
	unordered_map<string, int> variables;
	string expression;
    cout<<"Enter the name of the file: ";
	string fileName;
	cin>>fileName;
	fileReader::readVariablesAndExpression(fileName, variables, expression);
}
