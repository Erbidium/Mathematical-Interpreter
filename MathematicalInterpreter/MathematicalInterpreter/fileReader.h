#pragma once
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
class fileReader
{
public:
	static vector<string> readVariablesAndExpression(std::string fileName);
};
