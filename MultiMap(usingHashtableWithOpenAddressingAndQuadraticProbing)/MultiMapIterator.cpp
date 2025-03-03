#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    currentIdx=0;
    move();
}

void MultiMapIterator::move() {
    while ((currentIdx < col.capacity) && col.e[currentIdx] == NULL_TELEM)
        currentIdx++;
}

TElem MultiMapIterator::getCurrent() const{
    if (!valid()) {
        throw std::exception();
    }
    return col.e[currentIdx];
}

bool MultiMapIterator::valid() const {
    return currentIdx< col.capacity;
}

void MultiMapIterator::next() {
    if(!valid()){
        throw std::exception();
    }
    currentIdx++;
    move();
}

void MultiMapIterator::first() {
    currentIdx = 0;
    move();

}


