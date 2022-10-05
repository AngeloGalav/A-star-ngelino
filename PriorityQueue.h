#pragma once
#include <cmath>
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

/*
	Classe della PriorityQueue fatta da me.
	Un giorno forse la rifar� meglio...

	TODO: Add puntatore al nodo adiacente in modo da creare una lista monodirezionale di nodi sullo stesso layer.
*/

template <class T>
struct Elem
{
	T value;
	int key;
};

template <class T>
struct BinTreeElem 
{
	BinTreeElem<T>* parent;
	BinTreeElem<T>* l_son;
	BinTreeElem<T>* r_son;

	BinTreeElem<T>* next;	//puntatore al prossimo elemento della lista dei nodi dello stesso layer, aggiunto per fare una ez insertion

	Elem<T> treeElem;
};

template <class T>
class PriorityQueue
{
private:
	int lastFreeLayer;
	int remainingNodesInLayer;
	void moveUp(BinTreeElem<T>* toMov);	//permettono di normalizzare l'albero, in modo che rimanga sempre una priority queue.
	void moveDown(BinTreeElem<T>* toMov);
	void printRec(BinTreeElem<T>* toPrint);
public:
	PriorityQueue();
	BinTreeElem<T>* root;
	BinTreeElem<T>* tail;
	T findMin();
	void print();
	void insert(Elem<T> toInsert);
	void getLastLayer();
	void pop();
	void fixTree();
};

