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
	vector<string> calculatedVariablesAndExpressions;
	expressionTree currentTree;
	currentTree.build(stringsFromFile);
	currentTree.print();
	currentTree.calculate(calculatedVariablesAndExpressions);
	view::printResultsOfCalculations(calculatedVariablesAndExpressions, currentTree.getVariables());
}
