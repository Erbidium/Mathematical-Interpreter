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
