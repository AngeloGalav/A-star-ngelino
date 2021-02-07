#pragma once
#include <SFML/Graphics.hpp>

enum Mark
{
	Normal,
	Obstacle
};

class Node : public sf::RectangleShape
{
private:
	int index;
	bool isExplored;
	Mark type;
	
public:
	sf::Vector2i gridPos;
	Node();
	Node(int index, Mark type, sf::Vector2f position);
	Node* parent;
	void setIndex(int i);
	int getIndex();
	void setExplored();
	bool isVisited();
	Mark getType();
	void setType(Mark type);
};

