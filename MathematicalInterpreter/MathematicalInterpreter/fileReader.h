#pragma once
#include <string>
#include <unordered_map>


class fileReader
{
public:
	static void readVariablesAndExpression(std::string fileName, std::unordered_map<std::string, std::string>& variables, std::string &expression);
};
