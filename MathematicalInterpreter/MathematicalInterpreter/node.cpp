#include "node.h"
#include <string>

using namespace std;

node::node():
left(nullptr), right(nullptr)
{}

node::node(string data):
left(nullptr), right(nullptr), data(data)
{}

node::~node()
{
	delete left;
	delete right;
}

string node::getData()
{
	return data;
}
void node::setData(string newData)
{
	data=newData;
}
node* node::getLeft()
{
	return left;
}
node* node::getRight()
{
	return right;
}
void node::setRight(node* newRight)
{
	right=newRight;
}
void node::setLeft(node* newLeft)
{
	left=newLeft;
}