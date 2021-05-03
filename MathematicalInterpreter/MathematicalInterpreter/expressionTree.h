#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "node.h"

class expressionTree
{
	double calculateNode(node *);
	std::unordered_map<std::string, std::string> variables;
public:
	void setVariables(const std::unordered_map<std::string, std::string>& variables);
	node* root;
	expressionTree();
	~expressionTree();
	node* buildExpressionTree(std::vector<std::string> tokensFromExpression);
	void buildTree(std::vector<std::string> stringsFromFile);
	void printTree(const std::string& prefix, node* node, bool isLeft);
	double calculate();
};

