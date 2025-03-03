#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

Node::Node(TElem e, PNode nxt){
    this->e = e;
    this->nextNode = nxt;
}

TElem Node::element() {
    return this->e;
}

PNode Node::next() {
    return this->nextNode;
}

IndexedList::IndexedList() {
	this->first = nullptr;
}

int IndexedList::size() const {
    //wc:o(n), bc:o(1), tc: o(n)
    int nr = 0;
    PNode p = this->first;
    while (p!=nullptr){
        nr++;
        p = p->next();
    }
    return nr;
}


bool IndexedList::isEmpty() const {
    //bc=wc=tc=o(1)
    return (this->first == nullptr);
}

TElem IndexedList::getElement(int pos) const {
    //wc:o(n), bc:o(1), tc:o(n)
    if(pos<0){
        throw std::exception();
    }
    else{
        int nr = 0;
        PNode p = this->first;
        while (p!=nullptr){
            if(nr==pos){
                return p->element();
            }
            nr++;
            p = p->next();
        }
        throw std::exception();
    }

}

TElem IndexedList::setElement(int pos, TElem e) {
    //bc:o(1), wc:o(n), tc:o(n)
    if(pos<0)
	    throw std::exception();
    else{
        int nr = 0;
        PNode p = this->first;
        while (p!=nullptr){
            if(nr==pos){
                TElem oe = p->element();
                p->e = e;
                return oe;

            }
            nr++;
            p = p->next();
    }
       throw std::exception();
}}

void IndexedList::addToEnd(TElem e) {
    //bc:o(1), wc:o(n), tc:o(n)
    PNode pr = new Node(e, nullptr);
    if(first==nullptr){
        first=pr;
    }
    else{
        PNode p = first;
        while(p->next() != nullptr){
            p = p->next();
        }
        p->nextNode = pr;
    }
}

void IndexedList::addToPosition(int pos, TElem e) {
    //bc:o(1), wc:o(n), tc:o(n)
    if(pos<0)
        throw std::exception();


    PNode newN = new Node(e, nullptr);
    if(pos == 0){
        newN->nextNode = first;
        first = newN;
    }
    else{
        int nr = 0;
        PNode p = this->first;

        while (p!=nullptr && nr<pos-1){
            nr++;
            p = p->next();
        }
        if(p!=nullptr){
            newN -> nextNode = p->next();
            p->nextNode = newN;
        }
        else{
            throw std::exception();
        }
    }

}

TElem IndexedList::remove(int pos) {
    //bc:o(1), wc:o(n), tc:o(n)
    if(pos<0)
        throw std::exception();
    PNode p = this->first;
    if(pos==0){
        if(p==nullptr)
            throw std::exception();
        this->first = p->next();
        TElem rv = p->element();
        delete p;
        return rv;
    }
    else{
        int nr=0;
        while(p!=nullptr && nr<pos-1){
            p = p->next();
            nr++;
        }
        if(p==nullptr || p->next()==nullptr){
            throw std::exception();
        }
        PNode t = p->next();
        p->nextNode = t->next();
        TElem re = t->element();
        delete t;
        return re;

    }
}

int IndexedList::search(TElem e) const{
    //wc: o(n), bc:o(1), tc:o(n)
    int nr=0;
    PNode p = first;
    while(p!=nullptr){
        if(p->element()==e){
            return nr;
        }
        nr++;
        p=p->next();
    }
    return -1;
}

ListIterator IndexedList::iterator() const {
    //bc=wc=tc=o(1)
    return ListIterator(*this);        
}

int IndexedList::lastIndexOf(TElem elem) const{
    int nr=0;
    int pos=-1;
    PNode p = first;
    while(p!=nullptr){
        if(p->element()==elem){
            pos = nr;
        }
        nr++;
        p=p->next();
    }
    if(pos==-1)
        return -1;
    else
        return pos;
}

IndexedList::~IndexedList() {
	while(first!=nullptr){
        PNode p = first;
        first = first->nextNode;
        delete p;
    }
}