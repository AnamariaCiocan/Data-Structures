
#include "PriorityQueue.h"
#include <exception>
#include <iostream>

using namespace std;


PriorityQueue::PriorityQueue(Relation rel) :r(rel), cp(1000){
    this->head = -1;
    this->tail = -1;
    this->firstEmpty = 0;
    this->size = 0;

    nodes = new DLLANode[cp];

    for (int i = 0; i < cp - 1; i++) {
        this->nodes[i] = DLLANode(std::make_pair(-11111,-11111), i + 1, -1);
    }
    this->nodes[cp - 1] = DLLANode(std::make_pair(-11111,-11111), -1, -1);

}


void PriorityQueue::push(TElem e, TPriority p) {
    //bc: o(1), wc: o(n), tc: o(n), n=capacity
    if (size == cp) {
        resize();
    }

    int current = head;
    int prev = -1;

    // Find the correct position to insert the new element based on its priority
    while (current != -1 && r(nodes[current].get_info().second, p)) {
        prev = current;
        current = nodes[current].get_next();
    }

    int newNodeIndex = firstEmpty;
    firstEmpty = nodes[firstEmpty].get_next();

    // Insert the new element into the priority queue
    nodes[newNodeIndex] = DLLANode(Element(e, p), current, prev);

    if (current != -1) {
        nodes[current].set_prev(newNodeIndex);
    } else {
        tail = newNodeIndex;
    }

    if (prev != -1) {
        nodes[prev].set_next(newNodeIndex);
    } else {
        head = newNodeIndex;
    }

    size++;}


Element PriorityQueue::top() const {
    //bc:o(1)= wc:o(1)= tc:o(1)
    if (isEmpty()) {
        throw std::exception();
    }
    return nodes[head].get_info();
}

Element PriorityQueue::pop() {
    //bc:o(1) wc:o(1) tc:o(1)
    if (isEmpty()) {
        throw std::exception();
    }

    Element topElement = nodes[head].get_info();
    int nextHead = nodes[head].get_next();

    // Free the node at the head of the queue
    nodes[head] = DLLANode(std::make_pair(-11111, -11111), firstEmpty, -1);
    firstEmpty = head;

    head = nextHead;
    if (head != -1) {
        nodes[head].set_prev(-1);
    } else {
        tail = -1;
    }
    size--;
    return topElement;
}

bool PriorityQueue::isEmpty() const {
    //bc:o(1)=wc:o(1)=tc:o(1)
	return size==0;
}


PriorityQueue::~PriorityQueue() {
    delete []nodes;
}

int PriorityQueue::allocate_node(const DLLANode& d) {
    //bc:o(1), wc:o(1), tc:o(1)
    if (firstEmpty == -1) {
        throw std::exception(); // No empty slots available
    }

    int index = firstEmpty;
    firstEmpty = nodes[firstEmpty].get_next();

    // Copy the new node data into the allocated slot
    nodes[index] = d;
    return index;
}

void PriorityQueue::deallocate_node(int pos) {
    nodes[pos] = DLLANode(std::make_pair(-11111, -11111), firstEmpty, -1);
    firstEmpty = pos;
}

TPriority PriorityQueue::priorityOf(TElem elem) const{
    //wc:o(n); bc:o(1), tc: o(n) n=capacity
    for (int i = 0; i < cp; ++i) {
        if (nodes[i].get_info().first == elem) {
            return nodes[i].get_info().second;
        }
    }
    return -1;
}

void PriorityQueue::resize() {
    int newCapacity = cp * 2;
    auto* newNodes = new DLLANode[newCapacity];

    for (int i = 0; i < cp; ++i) {
        newNodes[i] = nodes[i];
    }

    // Update the links for the new nodes
    for (int i = cp; i < newCapacity - 1; ++i) {
        newNodes[i] = DLLANode(std::make_pair(-11111, -11111), i + 1, i - 1);
    }
    newNodes[newCapacity - 1] = DLLANode(std::make_pair(-11111, -11111), -1, cp - 2);

    cp = newCapacity;

    delete[] nodes;
    nodes = newNodes;

    // Update firstEmpty to point to the first empty slot in the new array
    firstEmpty = cp / 2;
    }



DLLANode::DLLANode(Element i, int next, int prev) {
    this->info.first = i.first;
    this->info.second = i.second;
    this->next = next;
    this->prev = prev;
}

Element DLLANode::get_info() const{
    return this->info;
}

int DLLANode::get_next() const {
    return this->next;
}

int DLLANode::get_prev() const {
    return this->prev;
}

void DLLANode::set_prev(int p) {
    this->prev = p;
}

void DLLANode::set_next(int n){
    this->next = n;
}

DLLANode::~DLLANode() = default;

DLLANode::DLLANode() {
    this->next = -1;
    this->prev = -1;
    this->info = std::make_pair(-11111,-11111);
}
