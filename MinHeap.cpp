#include "MinHeap.h"

void swap(Elem* x, Elem* y);

// Constructor: Builds a heap from a given array a[] of given size 
MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new Elem[cap];
}

// Inserts a new key 'k' 
void MinHeap::insertKey(int k, Node* node)
{
    if (heap_size == capacity)
    {
        std::cout << "\nOverflow: Could not insertKey\n";
        return;
    }

    // First insert the new key at the end 
    heap_size++;
    int i = heap_size - 1;
    
    Elem toIns;
    toIns.key = k;
    toIns.value = node;

    harr[i] = toIns;

    // Fix the min heap property if it is violated 
    while (i != 0 && harr[parent(i)].key > harr[i].key)
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// Decreases value of key at index 'i' to new_val.  It is assumed that 
// new_val is smaller than harr[i]. 
void MinHeap::decreaseKey(Node* nd, int new_val)
{
    int i = -1;
    for (int j = 0; j < heap_size; j++)
    {
        if (harr[j].value == nd) 
        {
            i = j;
            break;
        }
    }

    if (i != -1) 
    {
        harr[i].key = new_val;
        while (i != 0 && harr[parent(i)].key > harr[i].key)
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }
    else 
    {
        std::cout << "ERROR ELEMENT NOT FOUNDDDD!!!!" << std::endl;
    }
}

// Method to remove minimum element (or root) from min heap 
Elem MinHeap::extractMin()
{

    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }
    else if (heap_size > 1)
    {
        // Store the minimum value, and remove it from heap 
        Elem root = harr[0];
        harr[0] = harr[heap_size - 1];
        heap_size--;
        MinHeapify(0);

        return root;
    }
}

// A recursive method to heapify a subtree with the root at given index 
// This method assumes that the subtrees are already heapified 
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l].key < harr[i].key)
        smallest = l;
    if (r < heap_size && harr[r].key < harr[smallest].key)
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

// A utility function to swap two elements 
void swap(Elem* x, Elem* y)
{
    Elem temp = *x;
    *x = *y;
    *y = temp;
}