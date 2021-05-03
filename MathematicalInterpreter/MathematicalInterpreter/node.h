#pragma once
#include <string>
#include <vector>

class node
{
	std::string data;
	std::vector<node*>nodes;
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
