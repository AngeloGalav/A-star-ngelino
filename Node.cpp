#include "Node.h"

Node::Node(int index, Mark type, sf::Vector2f position) : sf::RectangleShape(position)
{
	gridPos.x = 0;
	gridPos.y = 0;
	parent = nullptr;
	index = 0;
	isExplored = false;
	this->type = type;
}

Node::Node() { parent = nullptr; }

bool Node::isVisited() 
{
	return isExplored;
}

void Node::setExplored() 
{
	isExplored = true;
}

Mark Node::getType() 
{
	return type;
}


void Node::setIndex(int i)
{
	index = i;
}

int Node::getIndex() 
{
	return index;
}

void Node::setType(Mark mark) 
{
	type = mark;
}