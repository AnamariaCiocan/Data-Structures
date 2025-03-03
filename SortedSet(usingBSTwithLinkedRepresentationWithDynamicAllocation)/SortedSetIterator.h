#pragma once

#include <stack>
#include "SortedSet.h"



//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
    const SortedSet& set;
    SortedSetIterator(const SortedSet& m);
    std::stack<const SortedSet::Node*> stack;
    void pushLeft(const SortedSet::Node* node);


public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};

