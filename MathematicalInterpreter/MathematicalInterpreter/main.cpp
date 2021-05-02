#include <iostream>
#include <unordered_map>
#include <string>
#include "fileReader.h"
#include "view.h"
#include "tokenizer.h"

using namespace std;

int main()
{
	unordered_map<string, string> variables;
	string fileName, expression;
    fileName=view::enterNameOfFile();
	fileReader::readVariablesAndExpression(fileName, variables, expression);
	vector<string> tokensFormExpression=tokenizer::splitExpressionIntoTokens(expression);
}
