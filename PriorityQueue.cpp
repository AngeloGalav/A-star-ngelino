#include "PriorityQueue.h"

template <class T>
PriorityQueue<T>::PriorityQueue() {}

template <class T>
T PriorityQueue<T>::findMin() 
{
	return root.treeElem.value;
}

template <class T>
void PriorityQueue<T>::pop()
{
	//return root.treeElem.value;
}

template <class T>
void PriorityQueue<T>::moveUp(BinTreeElem<T>* toMov) //TODO: Add element swapping list support
{
	while (toMov != root && toMov->treeElem.key < toMov->parent->treeElem.key)
	{
		BinTreeElem<T>* father = toMov->parent;
		toMov->parent = toMov->parent->parent;
		toMov->parent->parent = toMov;

		if (father->l_son == toMov) 
		{
			father->l_son = toMov->l_son;
			father->r_son = toMov->r_son;
			toMov->l_son = father;
		}
		else 
		{
			father->l_son = toMov->l_son;
			father->r_son = toMov->r_son;
			toMov->r_son = father;
		}
	}

}

template <class T>
void PriorityQueue<T>::moveDown(BinTreeElem<T>* toMov)
{
	//TO IMPLEMENT

}

template <class T>
void PriorityQueue<T>::print()
{
	printRec(root);
}

template <class T>
void PriorityQueue<T>::printRec(BinTreeElem<T>* toPrint)
{
	if (toPrint != NULL) 
	{
		std::cout << root.treeElem.key << " " << std::endl;
		printRec(toPrint->l_son);
		printRec(toPrint->r_son);
	}
}



template <class T>
void PriorityQueue<T>::insert(Elem<T> toInsert)
{
	BinTreeElem<T>* toIns = new BinTreeElem<T>();

	toIns.parent = tail;
	toIns.treeElem = toInsert;
	toIns.l_son = NULL;
	toIns.r_son = NULL;

	if (tail->l_son == NULL) tail->l_son = toIns;
	else if (tail->r_son == NULL) tail->r_son = toIns;
	else
	{
		//devo trovare un nuovo nodo libero

		//per trovare questo nuovo nodo libero mi conviene fare in modo che ciascun nodo contenga il puntatore al prossimo come una lista. (treeList???)

		BinTreeElem<T>* pos = tail;

		while (pos->parent != NULL) 
		{
			if (pos->parent->l_son == pos) 
			{
			
			}
			
			pos = pos->parent;
		}
	
	}

}


template <class T>
void PriorityQueue<T>::fixTree()
{
	std::queue<BinTreeElem<T>> queue;

	queue.push(root);

	while (!queue.empty()) 
	{
		BinTreeElem<T> p = queue.front();
		queue.pop();
		if (p.l_son != NULL) queue.push(*(p.l_son));

		if (p.r_son != NULL) queue.push(*(p.r_son));

	}
}
