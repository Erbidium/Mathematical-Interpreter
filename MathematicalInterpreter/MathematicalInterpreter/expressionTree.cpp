#include "expressionTree.h"
#include <iostream>
#include <ostream>

using namespace std;

expressionTree::expressionTree():
root(nullptr)
{}

expressionTree::~expressionTree()
{
	delete root;
}

void expressionTree::buildTree(std::vector<std::string> tokensFromExpression)
{
	for(int i=0;i<tokensFromExpression.size();i++)
	{
		cout<<tokensFromExpression[i]<< endl;
	}
}
