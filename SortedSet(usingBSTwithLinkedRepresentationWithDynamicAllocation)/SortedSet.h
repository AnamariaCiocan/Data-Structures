#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111
class SortedSetIterator;


class SortedSet {
	friend class SortedSetIterator;
private:
    struct Node{
        TComp info;
        Node *left;
        Node *right;
        Node(TComp v): info(v), left(nullptr), right(nullptr){}
    };
    Node *root;
    Relation rel;
    int sz;
	Node* insertNod(Node* nod, TComp e, bool &added);
    Node* removeNod(Node* nod, TComp e, bool &removed);
    bool searchNode(Node* nod, TElem elem) const;
    Node* mini(Node* nod) const;
    void clearNod(Node* nod);


public:


	//constructor
	SortedSet(Relation r);

	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);

	
	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//checks if an element is in the sorted set
	bool search(TElem elem) const;


	//returns the number of elements from the sorted set
	int size() const;

	//checks if the sorted set is empty
	bool isEmpty() const;

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;

    //keep only those elements that do not appear in s
    //returns the number of removed elements
    int difference(const SortedSet& s);

	// destructor
	~SortedSet();


};
