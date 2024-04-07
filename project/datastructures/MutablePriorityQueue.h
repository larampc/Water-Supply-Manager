#ifndef WATERSUPPLYMANAGER_MUTABLEPRIORITYQUEUE
#define WATERSUPPLYMANAGER_MUTABLEPRIORITYQUEUE

#include <vector>
#include "Graph.h"

class MutablePriorityQueue {
    std::vector<Vertex* > H;
    void heapifyUp(unsigned i);
    void heapifyDown(unsigned i);
    inline void set(unsigned i, Vertex* x);
public:
    /**
     * \brief Creates a new mutable priority queue
     */
    MutablePriorityQueue();
    /**
     * \brief Inserts a new element into the mutable priority queue.
     * @param x A pointer to the element to be inserted.
     *
     * @par Complexity
     * O(log n), in which n is the number of elements in the queue.
     */
    void insert(Vertex* x);
    /**
     * \brief Extracts the minimum element from the mutable priority queue, removing it from the queue.
     *
     * @return A pointer to the minimum element in the queue.
     *
     * @par Complexity
     * O(log n), in which n is the number of elements in the queue.
     */
    Vertex* extractMin();
    /**
     * \brief Decreases the key of an element in the queue, moving it up in priority.
     * @param x A pointer to the element whose key is to be decreased.
     *
     * @par Complexity
     * O(log n), in which n is the number of elements in the queue.
     */
    void decreaseKey(Vertex* x);
    /**
     * \brief This function checks whether the mutable priority queue is empty or not.
     *
     * @return True if the heap doesn't have any elements, false otherwise.
     */
    bool empty();
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

MutablePriorityQueue::MutablePriorityQueue() {
    H.push_back(nullptr);
    // indices will be used starting in 1
    // to facilitate parent/child calculations
}


bool MutablePriorityQueue::empty() {
    return H.size() == 1;
}

Vertex* MutablePriorityQueue::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if(H.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

void MutablePriorityQueue::insert(Vertex* x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

void MutablePriorityQueue::decreaseKey(Vertex* x) {
    heapifyUp(x->queueIndex);
}

void MutablePriorityQueue::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

void MutablePriorityQueue::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k+1 < H.size() && *H[k+1] < *H[k])
            ++k; // right child of i
        if ( ! (*H[k] < *x) )
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

void MutablePriorityQueue::set(unsigned i, Vertex* x) {
    H[i] = x;
    x->queueIndex = i;
}

#endif /* WATERSUPPLYMANAGER_MUTABLEPRIORITYQUEUE */
