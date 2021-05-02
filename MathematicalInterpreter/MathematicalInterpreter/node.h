#pragma once
#include <string>

class node
{
	std::string data;
	node *left, *right;
public:
	node();
	node(std::string);
	~node();
	std::string getData();
	void setData(std::string newData);
	node* getLeft();
	node* getRight();
	void setRight(node* newRight);
	void setLeft(node* newLeft);
};
