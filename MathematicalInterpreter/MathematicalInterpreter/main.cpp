#include "fileReader.h"
#include "view.h"
#include "tokenizer.h"
#include "expressionTree.h"
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main()
{
	string fileName;
    fileName=view::enterNameOfFile();
	vector<string> stringsFromFile = fileReader::readVariablesAndExpression(fileName);
	expressionTree currentTree;
	currentTree.buildTree(stringsFromFile);
	currentTree.printTree("", currentTree.root, false);
	//cout<<"Result: "<<currentTree.calculate()<<endl;
}
