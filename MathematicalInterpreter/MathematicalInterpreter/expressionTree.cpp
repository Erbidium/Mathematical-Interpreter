#include "expressionTree.h"
#include "node.h"
#include <iostream>
#include <cmath>
#include <stack>
#include <ostream>
#include "operation.h"
#include "tokenizer.h"

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
            return calculateNode(current->getRight())-calculateNode(current->getLeft());
        else if(current->getData()=="*")
            return calculateNode(current->getRight())*calculateNode(current->getLeft());
    	else if(current->getData()=="/")
            return calculateNode(current->getRight())/calculateNode(current->getLeft());
    	else if(current->getData()=="+")
            return calculateNode(current->getRight())+calculateNode(current->getLeft());
    	else if(current->getData()=="^")
            return pow(calculateNode(current->getRight()), calculateNode(current->getLeft()));
    }
}

void expressionTree::setVariables(const unordered_map<string, double> &variables)
{
	this->variables=variables;
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
                            operationsTop->setLeft(nodes.top());
                            nodes.pop();
                            operationsTop->setRight(nodes.top());
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
                            operationsTop->setLeft(nodes.top());
                            nodes.pop();
                            operationsTop->setRight(nodes.top());
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
            operationsTop->setLeft(nodes.top());
            nodes.pop();
            operationsTop->setRight(nodes.top());
            nodes.pop();
        }
        nodes.push(operationsTop);
        operations.pop();
    }
    return nodes.top();
}

node* expressionTree::buildTree(std::vector<string> stringsFromFile)
{
    node* stList = new node("St. list");
    int counter = 0;
    for (int i = 0; i < stringsFromFile.size(); i++) {
        string str = tokenizer::deleteWhiteSpaces(stringsFromFile[i]);
        cout << str << endl;
        if (str.find('=') != (-1)) {
            node* statement = new node("=");
            int equalPosition = str.find('=');
            string variableName = str.substr(0, equalPosition);
            string value = str.substr(equalPosition + 1);
            value = tokenizer::deleteWhiteSpaces(value);
            statement->setLeft(new node (tokenizer::deleteWhiteSpaces(variableName)));
            statement->setRight(buildExpressionTree(tokenizer::splitExpressionIntoTokens(value)));
            stList->setChildren(statement, counter++);
        }
        else {
            if (str[0] == 'i' && str[1] == 'f'){
                string condition = str.substr(str.find('(')+1);
                condition[condition.length() - 1] = ';';
                node* statement = new node("if");
                //cout << "cond " << condition << endl;
                statement->setLeft(buildExpressionTree(tokenizer::splitExpressionIntoTokens(condition)));
                //cout << "Check" << endl;
                stList->setChildren(statement, counter++);
                vector<string> substrings;
                i++;
            	int bracketsCounter=1;
                	
                while(bracketsCounter!=0)
                {
                	i++;
                	
                	cout<<i<<endl;
                	if(tokenizer::deleteWhiteSpaces(stringsFromFile[i])[0] == '}')
					    bracketsCounter--;
                    else if(tokenizer::deleteWhiteSpaces(stringsFromFile[i])[0] == '{')
                        bracketsCounter++;
                	if(bracketsCounter!=0)
                		substrings.push_back(tokenizer::deleteWhiteSpaces(stringsFromFile[i]));
                }
            	//i++;
            	cout<<"i: "<<i<<endl;
                statement->setRight(buildTree(substrings));
                if ((i + 1) < stringsFromFile.size() && tokenizer::deleteWhiteSpaces(stringsFromFile[i + 1]).find("else") != -1) {
                    vector<string> substrings2;
                    i+=2;
                	int bracketsCounter2=1;
                	
                	while(bracketsCounter2!=0)
                	{
                		i++;
                		cout<<i<<endl;
                		if(tokenizer::deleteWhiteSpaces(stringsFromFile[i])[0] == '}')
                            bracketsCounter2--;
                        else if(tokenizer::deleteWhiteSpaces(stringsFromFile[i])[0] == '{')
                            bracketsCounter2++;
                		if(bracketsCounter!=0)
                			substrings2.push_back(tokenizer::deleteWhiteSpaces(stringsFromFile[i]));
                	}
                	//cout<<endl;
                    statement->setChildren(buildTree(substrings2), 2);
                	//i++;
                }
            }
            else {
                stList->setChildren(buildExpressionTree(tokenizer::splitExpressionIntoTokens(str)), counter++);
            }
        }
    }
    return stList;
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

double expressionTree::calculateExpression()
{
	return calculateNode(root);
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
					variables.insert(make_pair(variableName, variableValue));
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
	                    calculateTree(calculatedVariablesAndExpressions, children->getChildren(2), numberOfExpression);
                    }
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
