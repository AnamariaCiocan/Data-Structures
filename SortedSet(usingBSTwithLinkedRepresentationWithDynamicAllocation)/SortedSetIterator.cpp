#include "SortedSetIterator.h"
#include <exception>
#include <iostream>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : set(m)
{
    first();

}

void SortedSetIterator::pushLeft(const SortedSet::Node *node) {
    while (node) {
        stack.push(node);
        node = node->left;
    }
}

void SortedSetIterator::first() {
    while (!stack.empty()) {
        stack.pop();
    }
    if (set.root != nullptr) {
        pushLeft(set.root);
    }
}


void SortedSetIterator::next() {
    if (!stack.empty()) {
        const SortedSet::Node* node = stack.top();
        stack.pop();
        pushLeft(node->right);
    }
    else{
        throw std::exception();
    }
}


TElem SortedSetIterator::getCurrent()
{
    if (!valid()) {
        throw std::exception();
    }
    return stack.top()->info;
}

bool SortedSetIterator::valid() const {
	return !stack.empty();
}

