#include "expressionTree.h"
#include "node.h"
#include "operation.h"
#include "tokenizer.h"
#include <iostream>
#include <cmath>
#include <stack>
#include <ostream>

using namespace std;

double expressionTree::calculateNode(node* current)
{
	if(isdigit(current->getData()[0]))
	{
		return stod(current->getData());
	}
    else if(isalpha(current->getData()[0]))
	{
		return variables.at(current->getData());
	}
	else if((current->getData()=="-")&&(current->getLeft()==nullptr))
        return -1*calculateNode(current->getRight());
    else
    {
	    if(current->getData()=="-")
            return calculateNode(current->getLeft())-calculateNode(current->getRight());
        else if(current->getData()=="*")
            return calculateNode(current->getLeft())*calculateNode(current->getRight());
    	else if(current->getData()=="/")
            return calculateNode(current->getLeft())/calculateNode(current->getRight());
    	else if(current->getData()=="+")
            return calculateNode(current->getLeft())+calculateNode(current->getRight());
    	else if(current->getData()=="^")
            return pow(calculateNode(current->getLeft()), calculateNode(current->getRight()));
    }
}

void expressionTree::build(const std::vector<std::string>& stringsFromFile)
{
	delete root;
	root=(buildTree(stringsFromFile));
}

void expressionTree::print()
{
	printTree("", root, false);
}

void expressionTree::calculate()
{
	int numberOfExpression=1;
	calculatedVariablesAndExpressions.clear();
	calculateTree(calculatedVariablesAndExpressions, root, numberOfExpression);
}

std::vector<std::string> expressionTree::getCalculatedVariablesAndExpressions()
{
	return calculatedVariablesAndExpressions;
}

expressionTree::expressionTree():
root(nullptr)
{}

expressionTree::~expressionTree()
{
	delete root;
}

node* expressionTree::buildExpressionTree(std::vector<std::string> tokensFromExpression)
{
    stack<node*> nodes;
    stack<char> operations;
	for(int i=0;i<tokensFromExpression.size();i++)
	{
        string currentToken = tokensFromExpression[i];
        if (i == 0 && currentToken == "-")operations.push('m');
        else
        if (currentToken.length() >= 1 && (isdigit(currentToken[0])||isalpha(currentToken[0]))) {
            node* tempNode = new node(currentToken);
            nodes.push(tempNode);
        }
        else {
            if (operations.empty()) {
                operations.push(currentToken[0]);
            }
            else {
                operation currentOperation(currentToken[0]);
                operation previousOperation(operations.top());
                if(currentOperation.name ==  '-' && tokensFromExpression[i-1] == "(")operations.push('m');
                else
                if (((previousOperation.name == '(' && currentOperation.name == ')'))) {
                    operations.pop();
                }
                else if ((currentOperation.name == '(') || (previousOperation.name == '('))
                {
                    operations.push(currentOperation.name);
                }
                else if (currentOperation.name == ')')
                {
                    while (previousOperation.name != '(')
                    {
                        node* operationsTop;
                        if (previousOperation.name == 'm') {
                            operationsTop = new node(string(1, '-'));
                            operationsTop->setRight(nodes.top());
                            nodes.pop();
                        }
                        else {
                            operationsTop = new node(string(1, previousOperation.name));
                        	operationsTop->setRight(nodes.top());
                            nodes.pop();
                            operationsTop->setLeft(nodes.top());
                            nodes.pop();
                        }
                        nodes.push(operationsTop);
                        operations.pop();
                        if (!operations.empty()) previousOperation = operations.top();
                    }
                    operations.pop();
                }
                else
                {
                    while (currentOperation.priority <= previousOperation.priority && !(operations.empty()) && ((previousOperation.name != '(')))
                    {
                        node* operationsTop;
                        if (previousOperation.name == 'm') {
                            operationsTop = new node(string(1, '-'));
                            operationsTop->setRight(nodes.top());
                            nodes.pop();
                        }
                        else {
                            operationsTop = new node(string(1, previousOperation.name));
                        	operationsTop->setRight(nodes.top());
                            nodes.pop();
                            operationsTop->setLeft(nodes.top());
                            nodes.pop();
                        }
                        nodes.push(operationsTop);
                        operations.pop();
                        if (!operations.empty()) previousOperation = operations.top();
                    }
                    operations.push(currentToken[0]);
                }
            }
        }
	}
    while (!operations.empty()) {
        node* operationsTop;
        if (operations.top() == 'm') {
            operationsTop = new node(string(1, '-'));
            operationsTop->setRight(nodes.top());
            nodes.pop();
        }
        else {
            operationsTop = new node(string(1, operations.top()));
        	operationsTop->setRight(nodes.top());
            nodes.pop();
            operationsTop->setLeft(nodes.top());
            nodes.pop();
        }
        nodes.push(operationsTop);
        operations.pop();
    }
    return nodes.top();
}

node* expressionTree::buildTree(std::vector<string> stringsFromFile)
{
    node* statementsList = new node("St. list");
    int counter = 0;
    for (int i = 0; i < stringsFromFile.size(); i++) {
        string str = tokenizer::deleteWhiteSpaces(stringsFromFile[i]);
        if (str.find('=') != (-1)) {
            node* statement = new node("=");
            int equalPosition = str.find('=');
            string variableName = str.substr(0, equalPosition);
            string value = str.substr(equalPosition + 1);
            value = tokenizer::deleteWhiteSpaces(value);
            statement->setLeft(new node (tokenizer::deleteWhiteSpaces(variableName)));
            statement->setRight(buildExpressionTree(tokenizer::splitExpressionIntoTokens(value)));
            statementsList->setChildren(statement, counter++);
        }
        else {
            if (str[0] == 'i' && str[1] == 'f'){
                string condition = str.substr(str.find('(')+1);
                condition[condition.length() - 1] = ';';
                node* statement = new node("if");
                statement->setLeft(buildExpressionTree(tokenizer::splitExpressionIntoTokens(condition)));
                statementsList->setChildren(statement, counter++);
                vector<string> substringForIf;
                i++;
            	int bracketsInIfCounter=1;
                	
                while(bracketsInIfCounter!=0)
                {
                	i++;
                	if(tokenizer::deleteWhiteSpaces(stringsFromFile[i])[0] == '}')
					    bracketsInIfCounter--;
                    else if(tokenizer::deleteWhiteSpaces(stringsFromFile[i])[0] == '{')
                        bracketsInIfCounter++;
                	if(bracketsInIfCounter!=0)
                		substringForIf.push_back(tokenizer::deleteWhiteSpaces(stringsFromFile[i]));
                }
                statement->setRight(buildTree(substringForIf));
                if ((i + 1) < stringsFromFile.size() && tokenizer::deleteWhiteSpaces(stringsFromFile[i + 1]).find("else") != -1) {
                    vector<string> substringForElse;
                    i+=2;
                	int bracketsInElseCounter=1;
                	while(bracketsInElseCounter!=0)
                	{
                		i++;
                		if(tokenizer::deleteWhiteSpaces(stringsFromFile[i])[0] == '}')
                            bracketsInElseCounter--;
                        else if(tokenizer::deleteWhiteSpaces(stringsFromFile[i])[0] == '{')
                            bracketsInElseCounter++;
                		if(bracketsInElseCounter!=0){
                			substringForElse.push_back(tokenizer::deleteWhiteSpaces(stringsFromFile[i]));
                        }
                	}
                    statement->setChildren(buildTree(substringForElse), 2);
                }
            }
            else if (str[0] == 'd' && str[1] == 'o') {
                node* statement = new node("do");
                statementsList->setChildren(statement, counter++);
                if ((i + 1) < stringsFromFile.size() ) {
                    vector<string> substringForWhile;
                    i++;
                    int bracketsInElseCounter = 1;
                    while (bracketsInElseCounter != 0)
                    {
                        i++;
                        if (tokenizer::deleteWhiteSpaces(stringsFromFile[i])[0] == '}')
                            bracketsInElseCounter--;
                        else if (tokenizer::deleteWhiteSpaces(stringsFromFile[i])[0] == '{')
                            bracketsInElseCounter++;
                        if (bracketsInElseCounter != 0) {
                            substringForWhile.push_back(tokenizer::deleteWhiteSpaces(stringsFromFile[i]));
                        }
                    }
                    statement->setLeft(buildTree(substringForWhile));
                    string str = tokenizer::deleteWhiteSpaces(stringsFromFile[++i]);
                    string condition = str.substr(str.find('(') + 1);
                    condition[condition.length() - 1] = ';';
                    cout << condition << endl;
                    statement->setRight(buildExpressionTree(tokenizer::splitExpressionIntoTokens(condition)));
                }
            }
            else {
                statementsList->setChildren(buildExpressionTree(tokenizer::splitExpressionIntoTokens(str)), counter++);
            }
        }
    }
    return statementsList;
}

void expressionTree::printTree(const string& prefix, node* node, bool isLeft)
{
    if (node != nullptr) {
        cout << prefix;
        cout << (isLeft ? char(195) : char(192)) << char(196) << char(196);
        cout << node->getData() << endl;
        if (node->getRight() == nullptr) {
            printTree(prefix + (isLeft ? "|   " : "    "), node->getChildren(0), false);
        }
        else {
            for (int i = 0; i < node->getNumberOfChildrens() - 1; i++) {
                printTree(prefix + (isLeft ? "|   " : "    "), node->getChildren(i), true);
            }
            printTree(prefix + (isLeft ? "|   " : "    "), node->getChildren(node->getNumberOfChildrens() - 1), false);
        }
    }
}

void expressionTree::calculateTree(std::vector<std::string> &calculatedVariablesAndExpressions, node * current, int &numberOfExpression)
{
	if((current!=nullptr)&&(current->getData()=="St. list"))
	{
		for(int i=0;i<current->getNumberOfChildrens();i++)
		{
			node * children=current->getChildren(i);
			if(children!=nullptr)
			{
				if(children->getData()=="=")
				{
					string variableName=children->getLeft()->getData();
					double variableValue=calculateNode(children->getRight());
					if(variables.contains(variableName)) variables.erase(variableName);
					variables.insert(make_pair(variableName, variableValue));
					auto itBegin=calculatedVariablesAndExpressions.begin();
					auto itEnd=calculatedVariablesAndExpressions.end();
					auto positionOfVarName=find(itBegin, itEnd, variableName);
					if(positionOfVarName!=itEnd)
                        calculatedVariablesAndExpressions.erase(positionOfVarName);
					calculatedVariablesAndExpressions.push_back(variableName);
				}
                else if(children->getData()=="if")
                {
	                double condition=calculateNode(children->getLeft());
                	if(condition!=0)
                	{
                		calculateTree(calculatedVariablesAndExpressions, children->getRight(), numberOfExpression);
                	}
                    else
                    {
                        if (children->getNumberOfChildrens() > 2) {
                            calculateTree(calculatedVariablesAndExpressions, children->getChildren(2), numberOfExpression);
                        }
                    }
                }
                else if(children->getData()=="do")
                {
                	do
                	{
                		calculateTree(calculatedVariablesAndExpressions, children->getLeft(), numberOfExpression);
                	}
                	while(calculateNode(children->getRight()));
                }
                else
                {
	                double expressionValue=calculateNode(children);
                	calculatedVariablesAndExpressions.push_back("expression "+to_string(numberOfExpression));
                	variables.insert(make_pair("expression "+to_string(numberOfExpression), expressionValue));
                	numberOfExpression++;
                }
			}
		}
	}
}

std::unordered_map<std::string, double> expressionTree::getVariables()
{
    return variables;
}
