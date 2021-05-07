#pragma once
#include "node.h"
#include <vector>
#include <string>
#include <unordered_map>

class expressionTree
{
	std::unordered_map<std::string, double> variables;
	double calculateNode(node *);
	node* buildTree(std::vector<std::string> stringsFromFile);
	void printTree(const std::string& prefix, node* node, bool isLeft);
	void calculateTree(std::vector<std::string> &calculatedVariablesAndExpressions, node * current, int &numberOfExpression);
	node* buildExpressionTree(std::vector<std::string> tokensFromExpression);
	double calculateExpression();
	node* root;
public:
	expressionTree();
	~expressionTree();
	void build(const std::vector<std::string>& stringsFromFile);
	void print();
	void calculate(std::vector<std::string> &calculatedVariablesAndExpressions);
	std::unordered_map<std::string, double> getVariables();
};

