#include "tokenizer.h"
#include <iostream>

using namespace std;


vector<string> tokenizer::splitExpressionIntoTokens(string expression)
{
	vector<string>tokens;
	while(expression!=";")
	{
		if((expression.front()=='(')||(expression.front()==')')||(expression.front()=='+')||(expression.front()=='-')||
		(expression.front()=='*')||(expression.front()=='/')||(expression.front()=='^'))
		{
			tokens.emplace_back(string(1, expression.front()));
			expression.erase(0, 1);
		}
		else
		{
			string currentToken;
			while((expression.size()>0)&&(expression.front()!='(')&&(expression.front()!=')')&&(expression.front()!='+')&&(expression.front()!='-')&&
			(expression.front()!='*')&&(expression.front()!='/')&&(expression.front()!='^')&&(expression.front()!=';'))
			{
				currentToken=currentToken+expression.front();
				expression.erase(0, 1);
			}
			tokens.push_back(currentToken);
		}
	}
	return tokens;
}

std::string tokenizer::deleteWhiteSpaces(std::string str)
{
	string newStr;
	for(int i=0;i<str.size();i++)
	{
		if((str[i]!=' ')&&(str[i]!='\t')) newStr+=str[i];
	}
	return newStr;
}
