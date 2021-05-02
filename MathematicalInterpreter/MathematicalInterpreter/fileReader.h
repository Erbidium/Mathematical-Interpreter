#pragma once
#include <string>
#include <unordered_map>


class fileReader
{
public:
	static void readVariablesAndExpression(std::string fileName, std::unordered_map<std::string, int>& variables, std::string &expression);
};
