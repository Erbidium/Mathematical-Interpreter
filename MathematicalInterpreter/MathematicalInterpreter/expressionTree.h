#pragma once
#include "node.h"
#include <vector>
#include <string>
#include <unordered_map>

class expressionTree
{
	node* root;
	std::unordered_map<std::string, double> variables;
	std::vector<std::string> calculatedVariablesAndExpressions;
	double calculateNode(node *);
	node* buildTree(std::vector<std::string> stringsFromFile);
	node* buildExpressionTree(std::vector<std::string> tokensFromExpression);
	void printTree(const std::string& prefix, node* node, bool isLeft);
	void calculateTree(std::vector<std::string> &calculatedVariablesAndExpressions, node * current, int &numberOfExpression);
public:
	expressionTree();
	~expressionTree();
	void build(const std::vector<std::string>& stringsFromFile);
	void print();
	void calculate();
	std::vector<std::string> getCalculatedVariablesAndExpressions();
	std::unordered_map<std::string, double> getVariables();
};

