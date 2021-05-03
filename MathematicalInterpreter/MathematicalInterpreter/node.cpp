#include "node.h"
#include <string>

using namespace std;

node::node()
{
	nodes.resize(2, nullptr);
}

node::node(string data):data(data)
{
	nodes.resize(2, nullptr);
}

node::~node()
{
	for(int i=0;i<nodes.size();i++)
	{
		delete nodes[i];
	}
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
	return nodes[0];
}
node* node::getRight()
{
	return nodes[1];
}
void node::setRight(node* newRight)
{
	nodes[1]=newRight;
}
void node::setLeft(node* newLeft)
{
	nodes[0]=newLeft;
}

void node::setChildren(node* childrenNode, int index)
{
	if(index+1>nodes.size()) 
		nodes.resize(index+1);
	nodes[index]=childrenNode;
}

int node::getNumberOfChildrens()
{
	return nodes.size();
}

node* node::getChildren(int index)
{
	return nodes[index];
}
