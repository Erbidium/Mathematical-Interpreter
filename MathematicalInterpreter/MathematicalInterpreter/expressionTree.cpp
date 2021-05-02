#include "expressionTree.h"

expressionTree::expressionTree():
root(nullptr)
{}

expressionTree::~expressionTree()
{
	delete root;
}
