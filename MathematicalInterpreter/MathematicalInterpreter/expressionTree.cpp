#include "expressionTree.h"
#include "node.h"
#include <iostream>
#include <cmath>
#include <stack>
#include <ostream>
#include "operation.h"

using namespace std;

double expressionTree::calculateNode(node* current)
{
	if(isdigit(current->getData()[0]))
	{
		return stod(current->getData());
	}
    else if(isalpha(current->getData()[0]))
	{
		return stod(variables.at(current->getData()));
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

void expressionTree::setVariables(const unordered_map<string, string> &variables)
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

void expressionTree::buildTree(std::vector<std::string> tokensFromExpression)
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
    root = nodes.top();
    /*while (!nodes.empty()) {
        cout << nodes.top()->getData() << endl;
        cout << nodes.top()->getLeft()->getData() << endl;
        cout << nodes.top()->getRight()->getData() << endl;
        cout << endl;l
        nodes.pop();
    }
    */
    cout << operations.size();
}

void expressionTree::printTree(const string& prefix, node* node, bool isLeft)
{
    if (node != nullptr) {
        cout << prefix;
        cout << (isLeft ? char(195) : char(192)) << char(196) << char(196);
        cout << node->getData() << endl;
        expressionTree::printTree(prefix + (isLeft ? "|   " : "    "), node->getLeft(), true);
        expressionTree::printTree(prefix + (isLeft ? "|   " : "    "), node->getRight(), false);
    }
}

double expressionTree::calculate()
{
	return calculateNode(root);
}
