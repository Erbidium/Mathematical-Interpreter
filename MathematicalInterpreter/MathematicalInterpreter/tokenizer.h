#pragma once
#include <string>
#include <vector>
class tokenizer
{
public:
	static std::vector<std::string> splitExpressionIntoTokens(std::string expression);
	static std::string deleteWhiteSpaces(std::string str);
};

