#include "view.h"
#include <iostream>

using namespace std;

string view::enterNameOfFile()
{
	string fileName;
	cout<<"Enter the name of the file: ";
	cin>>fileName;
	return fileName;
}

void view::unsuccessfulOpening()
{
	cout<<"Can't open the file!\n";
}

void view::printResultsOfCalculations(const std::vector<std::string> &calculatedVariablesAndExpressions, const std::unordered_map<std::string, double> & variables)
{
	for(int i=0;i<calculatedVariablesAndExpressions.size();i++)
	{
		cout<<calculatedVariablesAndExpressions[i]<<" = "<<variables.at(calculatedVariablesAndExpressions[i])<<endl;
	}
}
