#include <vector>
#include <string>
#include "classes_and_functions.h"
using namespace std;

//Recall Max Heap logic: Complete binary tree, each parent bigger than children. It can be stored like a vector
//Let's say each node is i, then left child is 2i + 1, right child is 2i + 2, parent is (i-1)/2
class MaxHeap{
    vector<Player> heap;
    int find_parent(int i){
        return (i-1)/2;
    }
    int find_left_child(int i){
        return 2*i + 1;
    }
    int find_right_child(int i){
        return 2*i + 2;
    }
    bool has_left_child(int i){
        return find_left_child(i) < heap.size();
    }
    bool has_right_child(int i){
        return find_right_child(i) < heap.size();
    }

    void heapify_up(int i){ //Used for inserting a new node, if the value is greater then needs to be heapified up
        while (i > 0 && heap[i].grade > heap[find_parent(i)].grade){
            swap(heap[i], heap[find_parent(i)]);
            i = find_parent(i);
        }
    }
    void heapify_down(int i){ //Used for after extracting the max, the last node placed at root might be too small => heapify down
        int largest = i;
        if (has_left_child(i) && heap[find_left_child(i)].grade > heap[largest].grade){
            largest = find_left_child(i);
        }
        if (has_right_child(i) && heap[find_right_child(i)].grade > heap[largest].grade){
            largest = find_right_child(i);
        }
        if (largest != i){
            swap(heap[i], heap[largest]);
            heapify_down(largest);
        }
    }
    
public:
    int get_size(){
        return heap.size();
    }
    bool is_empty(){
        return heap.empty();
    }
    //Insert a new player into the heap
};