#include "Node.h"
#include "MinHeap.h"
#include <functional>
#include <queue>
#include <vector>
#include <windows.h>
#include <iostream>
#define GRIDSIZE 20
#define WINDOWSIZE 900

float dist[(WINDOWSIZE / GRIDSIZE)* (WINDOWSIZE / GRIDSIZE)];
float cost[(WINDOWSIZE / GRIDSIZE) * (WINDOWSIZE / GRIDSIZE)];



//std::priority_queue<std::pair<float, Node*> > Q;


void Djikstra(Node grid[][WINDOWSIZE / GRIDSIZE], Node* src);

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOWSIZE, WINDOWSIZE), "A* Test");
  
    Node nodes[WINDOWSIZE / GRIDSIZE][WINDOWSIZE / GRIDSIZE];

    for (int i = 0; i < WINDOWSIZE/GRIDSIZE; i++) 
    {
        for (int j = 0; j < WINDOWSIZE/GRIDSIZE; j++)
        {
            dist[(WINDOWSIZE/GRIDSIZE) * i + j] = INFINITY;
            nodes[i][j] = Node((WINDOWSIZE / GRIDSIZE) *i + j, Normal, sf::Vector2f(GRIDSIZE-1, GRIDSIZE-1));
            nodes[i][j].setPosition(sf::Vector2f(GRIDSIZE*i, GRIDSIZE*j));
            nodes[i][j].setFillColor(sf::Color::White);
            nodes[i][j].gridPos.x = i;
            nodes[i][j].gridPos.y = j;
            nodes[i][j].setIndex((WINDOWSIZE / GRIDSIZE) * i + j);
        }
    }

    Node* source = nullptr;
    Node* dest = nullptr;
    MinHeap Q(1000);

    bool completed = false;
    bool letsgo = false;

    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i MousePos = sf::Mouse::getPosition(window);

                for (int i = 0; i < WINDOWSIZE / GRIDSIZE; i++)
                {
                    for (int j = 0; j < WINDOWSIZE / GRIDSIZE; j++)
                    {
                        if (nodes[i][j].getPosition().x < MousePos.x && MousePos.x < nodes[i][j].getPosition().x + GRIDSIZE
                            && nodes[i][j].getPosition().y < MousePos.y && MousePos.y < nodes[i][j].getPosition().y + GRIDSIZE)
                        {

                            if (source == nullptr)
                            {
                                nodes[i][j].setFillColor(sf::Color::Blue);
                                source = &nodes[i][j];
                            }
                            else if (source != nullptr && dest == nullptr)
                            {
                                nodes[i][j].setFillColor(sf::Color::Red);
                                dest = &nodes[i][j];

                                dist[source->getIndex()] = 0;
                                Q.insertKey(dist[source->getIndex()], source);
                                source->parent = NULL;
                                source->setExplored();
                            }
                            else 
                            {
                                nodes[i][j].setFillColor(sf::Color::Black);
                                nodes[i][j].setType(Obstacle);
                            }
                        }
                    }
                }
            }


            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter) letsgo = true;
            }
        }

        
        if (letsgo && !Q.empty() && !completed)
        {
            Node* u = Q.extractMin().value;

            std::cout << "CHOSEN: " << u->getIndex() << std::endl;
            nodes[u->gridPos.x][u->gridPos.y].setFillColor(sf::Color::Green);

            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (j != 0 || i != 0) 
                    {
                        int cachx = u->gridPos.x + i;
                        int cachy = u->gridPos.y + j;

                        int w = 10;
                        if (i == j) w = 14;

                        if (cachx > -1 && cachy > -1 && cachx < (WINDOWSIZE / GRIDSIZE) && cachy < (WINDOWSIZE / GRIDSIZE)
                            && (nodes[cachx][cachy]).getType() != Obstacle)
                        {
                            
                            Node* v = &(nodes[cachx][cachy]);
                            std::cout << "\nV is: " << v->getIndex() << std::endl;

                            if (!(v->isVisited()))
                            {
                                
                                v->setExplored();
                                std::cout << "BEFORE: " << dist[v->getIndex()] + cost[v->getIndex()] << std::endl;
                                dist[v->getIndex()] = dist[u->getIndex()] + w;
                                cost[v->getIndex()] = sqrt(pow((v->gridPos.x - dest->gridPos.x), 2) + pow((v->gridPos.y - dest->gridPos.y), 2))*14;
                                std::cout << "AFTER: " << dist[v->getIndex()] + cost[v->getIndex()] << std::endl;
                                Q.insertKey(cost[v->getIndex()] + dist[v->getIndex()], v);
                                
                                v->parent = u;

                                std::cout << "BIAS: " << dist[v->getIndex()] + cost[v->getIndex()] << std::endl;

                                if (v == dest)
                                {
                                    completed = true;
                                    break;
                                }
                                nodes[cachx][cachy].setFillColor(sf::Color::Yellow);
                            }
                            else if (dist[v->getIndex()] > dist[u->getIndex()] + w)
                            {
                                dist[v->getIndex()] = dist[u->getIndex()] + w;
                                Q.decreaseKey(v, cost[v->getIndex()] + dist[v->getIndex()]);
                                v->parent = u;                                
                            }
                        }
                    }
                }
            }
        }

        //stuff here gets drawn
        window.clear();
        for (int i = 0; i < WINDOWSIZE / GRIDSIZE; i++)
        {
            for (int j = 0; j < WINDOWSIZE / GRIDSIZE; j++)
            {
                window.draw(nodes[i][j]);
            }
        }

        if (completed)
        {
            Node* cursor = dest;
            while (cursor != NULL)
            {
                cursor->setFillColor(sf::Color::Cyan);
                cursor = cursor->parent;
            }
        }
        window.display();
    }

    return 0;
}



//LEGACY FUNCTION
void Djikstra(Node grid[][WINDOWSIZE/GRIDSIZE], Node* src) 
{
    MinHeap Q(1000);

    dist[src->getIndex()] = 0;
    Q.insertKey(dist[src->getIndex()], src);
    src->parent = NULL;

    while (!Q.empty()) 
    {
        Node* u = Q.extractMin().value;

        for (int i = -1; i < 3; i+=2) 
        {
            for (int j = -1; j < 3; j+=2) 
            {
                int cachx = u->gridPos.x + i;
                int cachy = u->gridPos.y + j;

                if (cachx >= 0 && cachy >= 0)
                {
                    Node* v = &grid[cachx][cachy];

                    if (!(v->isVisited())) 
                    {
                        v->setExplored();
                        dist[v->getIndex()] = dist[u->getIndex()] + 1;
                        Q.insertKey(dist[v->getIndex()], v);
                        v->parent = u;
                    }
                    else if (dist[v->getIndex()] > dist[u->getIndex()] + 1)
                    {
                        Q.decreaseKey(v, dist[u->getIndex()] + 1);
                        dist[v->getIndex()] = dist[u->getIndex()] + 1;
                        v->parent = u;
                    }
                }

            }
        }
    }
}