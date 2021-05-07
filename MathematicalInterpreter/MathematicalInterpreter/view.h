#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class view
{
public:
	static std::string enterNameOfFile();
	static void unsuccessfulOpening();
	static void printResultsOfCalculations(const std::vector<std::string> &calculatedVariablesAndExpressions, const std::unordered_map<std::string, double> & variables);
};

