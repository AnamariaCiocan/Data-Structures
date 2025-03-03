#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

ListIterator::ListIterator(const IndexedList& list) : list(list){
    this->current = list.first;
}

void ListIterator::first(){
    this->current = this->list.first;
}

void ListIterator::next(){
    if(!valid()){
        throw std::exception();
    }
    else{
        this->current = current->next();
    }
}

bool ListIterator::valid() const{
    return (this->current!=nullptr);
}

TElem ListIterator::getCurrent() const{
   if(!valid()){
       throw std::exception();
   }
   else{
       return this->current->element();
   }
}