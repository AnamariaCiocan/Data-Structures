#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>
#include <cmath>
using namespace std;

//symbolic constant that indicates a free location in the hash table
#define NIL -1
#define DELETED -2
//function that gives the hashCode of an element
int hashCode(TKey k){
    return std::abs(k);
}

// Hash function with quadratic probing
int MultiMap::h(TKey key, int i) const {
    return (hashCode(key)%capacity + i * i) % capacity;
}

MultiMap::MultiMap() {
    capacity = MAX;
    sz = 0;
    e = new TElem[capacity];
    for (int i = 0; i < capacity; i++) {
        e[i] = NULL_TELEM;
    }
}


void MultiMap::add(TKey c, TValue v) {
    //BC=o(1), WC=TC=o(n), n=capacity
    int i = 0;
    int index = h(c, i);

    while (e[index] != NULL_TELEM) {
        i++;
        index = h(c, i);
    }

    e[index] = make_pair(c, v);
    sz++;

    if (sz >= capacity / 2) {
        resize();
    }
}
void MultiMap::resize() {
    //BC=WC=TC=o(n)
    int newCapacity = capacity * 2;
    TElem* newElements = new TElem[newCapacity];
    for (int i = 0; i < newCapacity; i++) {
        newElements[i] = NULL_TELEM;
    }
    for (int i = 0; i < capacity; i++) {
        if (e[i] != NULL_TELEM) {
            int j = 0;
            int index = h(e[i].first, j);
            while (newElements[index] != NULL_TELEM) {
                j++;
                index = h(e[i].first, j);
            }
            newElements[index] = e[i];
        }
    }

    delete[] e;
    e = newElements;
    capacity = newCapacity;
}

bool MultiMap::remove(TKey c, TValue v) {
    //BC=o(1), WC=TC=o(n)
    for (int i = 0; i < capacity; i++) {
        if (e[i].first == c && e[i].second == v) {
            e[i] = NULL_TELEM;
            sz--;
            return true;
        }
    }

    return false;
}


vector<TValue> MultiMap::search(TKey c) const {
    //BC=o(1), WC=TC=o(n)
    vector<TValue> values;

    int i = 0;
    int index = h(c, i);

    while (i < sz+1) {
        if (e[index].first == c) {
            values.push_back(e[index].second);
        }
        i++;
        index = h(c, i);
    }

    return values;

}


int MultiMap::size() const {
	return this->sz;
}


bool MultiMap::isEmpty() const {
	return this->sz == 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	delete[] e;
}

int MultiMap::updateValues(MultiMap &m) {
    //BC=WC=TC=o(n)
    int mdf = 0;
    int i = 0;
    int index=h(e[i].first,i);
    if(m.capacity>capacity){
        while(i<m.capacity){
            if(e[i].first == m.e[i].first && e[index].second!=m.e[index].second){
                e[i].second = m.e[i].second;
                mdf++;
            }
            i++;
            index=h(e[i].first,i);
        }
    }
    else{
        while(i<capacity){
            if(e[index].first == m.e[index].first and e[index].second!=m.e[index].second){
                e[index].second = m.e[index].second;
                mdf++;
            }
            i++;
            index=h(e[index].first,i);
        }
    }
    return mdf;
}

