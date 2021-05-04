#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "node.h"

class expressionTree
{
	std::unordered_map<std::string, double> variables;
	double calculateNode(node *);
	node* root;
public:
	void setVariables(const std::unordered_map<std::string, double>& variables);
	expressionTree();
	~expressionTree();
	node* buildExpressionTree(std::vector<std::string> tokensFromExpression);
	node* buildTree(std::vector<std::string> stringsFromFile);
	void printTree(const std::string& prefix, node* node, bool isLeft);
	double calculateExpression();
	void calculateTree(std::vector<std::string> &calculatedVariablesAndExpressions, node * current, int &numberOfExpression);
	std::unordered_map<std::string, double> getVariables();
	node* getRoot();
	void setRoot(node* root);
};

