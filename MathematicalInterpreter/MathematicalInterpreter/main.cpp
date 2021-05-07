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
	string fileName=view::enterNameOfFile();
	int numberOfExpression=1;
	vector<string> stringsFromFile = fileReader::readVariablesAndExpression(fileName);
	expressionTree currentTree;
	currentTree.setRoot(currentTree.buildTree(stringsFromFile));
	currentTree.printTree("", currentTree.getRoot(), false);
	vector<string> calculatedVariablesAndExpressions;
	currentTree.calculateTree(calculatedVariablesAndExpressions, currentTree.getRoot(), numberOfExpression);
	view::printResultsOfCalculations(calculatedVariablesAndExpressions, currentTree.getVariables());
}
