#pragma once
#include <vector>
#include <string>
#include "node.h"
using namespace std;
class expressionTree
{
public:
	node* root;
	expressionTree();
	~expressionTree();
	void buildTree(std::vector<std::string> tokensFromExpression);
	void printTree(const string& prefix, node* node, bool isLeft);
};

