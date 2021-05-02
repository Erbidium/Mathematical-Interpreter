#pragma once
#include <vector>

#include "node.h"

class expressionTree
{
	node * root;
public:
	expressionTree();
	~expressionTree();
	void buildTree(std::vector<std::string> tokensFromExpression);
};

