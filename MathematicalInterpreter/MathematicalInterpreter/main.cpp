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
	currentTree.root = currentTree.buildTree(stringsFromFile);
	currentTree.printTree("", currentTree.root, false);
	vector<string> calculatedVariablesAndExpressions;
	int numberOfExpression=1;
	currentTree.calculateTree(calculatedVariablesAndExpressions, currentTree.root, numberOfExpression);
	for(int i=0;i<calculatedVariablesAndExpressions.size();i++)
	{
		cout<<calculatedVariablesAndExpressions[i]<<" = "<<currentTree.variables.at(calculatedVariablesAndExpressions[i])<<endl;
	}
}
