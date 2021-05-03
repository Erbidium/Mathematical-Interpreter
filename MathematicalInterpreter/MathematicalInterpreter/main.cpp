#include <iostream>
#include <unordered_map>
#include <string>
#include "fileReader.h"
#include "view.h"
#include "tokenizer.h"
#include "expressionTree.h"

using namespace std;

int main()
{
	unordered_map<string, string> variables;
	string fileName, expression;
    fileName=view::enterNameOfFile();
	fileReader::readVariablesAndExpression(fileName, variables, expression);
	vector<string> tokensFromExpression=tokenizer::splitExpressionIntoTokens(expression);
	expressionTree currentTree;
	currentTree.setVariables(variables);
	currentTree.buildTree(tokensFromExpression);
	currentTree.printTree("", currentTree.root, false);
	cout<<"Result: "<<currentTree.calculate()<<endl;
}
