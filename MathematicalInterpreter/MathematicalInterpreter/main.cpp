#include "fileReader.h"
#include "view.h"
#include "expressionTree.h"
#include <unordered_map>
#include <string>

using namespace std;

int main()
{
	string fileName=view::enterNameOfFile();
	vector<string> stringsFromFile = fileReader::readVariablesAndExpression(fileName);
	expressionTree currentTree;
	currentTree.build(stringsFromFile);
	currentTree.print();
	currentTree.calculate();
	view::printResultsOfCalculations(currentTree.getCalculatedVariablesAndExpressions(), currentTree.getVariables());
}
