#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "node.h"

class expressionTree
{
	double calculateNode(node *);
public:
	std::unordered_map<std::string, double> variables;
	void setVariables(const std::unordered_map<std::string, double>& variables);
	node* root;
	expressionTree();
	~expressionTree();
	node* buildExpressionTree(std::vector<std::string> tokensFromExpression);
	node* buildTree(std::vector<std::string> stringsFromFile);
	void printTree(const std::string& prefix, node* node, bool isLeft);
	double calculateExpression();
	void calculateTree(std::vector<std::string> &calculatedVariablesAndExpressions, node * current, int &numberOfExpression);
};

