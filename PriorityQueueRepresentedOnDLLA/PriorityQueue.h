#pragma once
#include <vector>
#include <utility>

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool (*Relation)(TPriority p1, TPriority p2);
#define NULL_TELEM pair<TElem, TPriority> (-11111,-11111);

class DLLANode{
private:
    Element info;
    int next;
    int prev;
public:
    DLLANode();
    DLLANode(Element i, int next, int prev);
    Element get_info() const;
    int get_next() const;
    int get_prev() const;
    void set_prev(int p);
    void set_next(int n);
    ~DLLANode();
};

class PriorityQueue {
private:
    int cp;
	DLLANode* nodes;
    int head;
    int tail;
    int firstEmpty;
    int size;
    Relation r;
    int allocate_node(const DLLANode& d);
    void deallocate_node(int pos);
    void resize();

public:

	//implicit constructor
	PriorityQueue(Relation r);

	//pushes an element with priority to the queue
	void push(TElem e, TPriority p);

	//returns the element with the highest priority with respect to the order relation
	//throws exception if the queue is empty
	Element top()  const;

	//removes and returns the element with the highest priority
	//throws exception if the queue is empty
	Element pop();

	//checks if the queue is empty
	bool isEmpty() const;

    //returns the priority of elem. If elem appears multiple times the priority of one of them should be returned
    //if elem is not in the PriorityQueue, return -1
    TPriority priorityOf(TElem elem) const;

	//destructor
	~PriorityQueue();


};