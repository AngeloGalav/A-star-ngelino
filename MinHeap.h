#pragma once
#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include "Node.h" 

/*
    Ho preso questa classe da https://www.geeksforgeeks.org/binary-heap/, siccome la mia implementazione delle priorityQueue
    stava richiededo troppo tempo. Forse una prossima volta lo rifarò...

    L'ho modificata per farla funzionare con il mio codice.
*/

struct Elem
{
    Node* value;
    int key;
};


class MinHeap
{
    Elem* harr; // pointer to array of elements in heap 
    int capacity; // maximum possible size of min heap 
public:
    // Constructor 
    MinHeap(int capacity);
    int heap_size;


    bool empty() { return heap_size <= 0; }

    // to heapify a subtree with the root at given index 
    void MinHeapify(int);

    int parent(int i) { return (i - 1) / 2; }

    // to get index of left child of node at index i 
    int left(int i) { return (2 * i + 1); }

    // to get index of right child of node at index i 
    int right(int i) { return (2 * i + 2); }

    // to extract the root which is the minimum element 
    Elem extractMin();

    // Decreases key value of key at index i to new_val 
    void decreaseKey(Node* nd, int new_val);

    // Returns the minimum key (key at root) from min heap 
    Node* getMin() { return harr[0].value; }

    // Inserts a new key 'k' 
    void insertKey(int k, Node* node);
};
