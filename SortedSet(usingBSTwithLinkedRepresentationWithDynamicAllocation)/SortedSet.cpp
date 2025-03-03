#include <iostream>
#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
    this->root = nullptr;
    this->sz = 0;
    this->rel = r;
}

SortedSet::Node* SortedSet::insertNod(Node *nod, TComp e, bool &added) {
    //BC=o(log2(n)) WC=TC=o(n)
    if (!nod) {
        nod = new Node(e);
        added = true;
        sz++;
        return nod;
    }
    if (rel(e, nod->info)) {
        nod->left = insertNod(nod->left, e, added);
    } else if (rel(nod->info, e)) {
        nod->right = insertNod(nod->right, e, added);
    }
    return nod;
}


bool SortedSet::add(TComp elem) {
    //BC=o(log(n)) WC=TC=o(n)
    bool added = false;
    if (!search(elem)) {
        root = insertNod(root, elem, added);
    }
    return added;
}


bool SortedSet::remove(TComp elem) {
    //BC=o(log2(n)) WC=TC=o(n)
    bool removed = false;
    if(search(elem))
        root = removeNod(root, elem, removed);
    return removed;
}

SortedSet::Node* SortedSet::mini(Node *nod) const {
    //BC=WC=TC=o(log(n))
    while (nod && nod->left) {
        nod = nod->left;
    }
    return nod;
}

SortedSet::Node* SortedSet::removeNod(Node *nod, TComp e, bool &removed) {
    //BC=o(log(n)) WC=TC=o(n)
    if (!nod) {
        return nullptr;
    }

    if (nod->info == e) {
        if (!nod->left && !nod->right) {
            delete nod;
            sz--;
            removed = true;
            return nullptr;
        }


        if (!nod->left || !nod->right) {
            Node* temp;
            if (nod->left) {
                temp = nod->left;
            } else {
                temp = nod->right;
            }
            delete nod;
            sz--;
            removed = true;
            return temp;
        }


        Node* temp = mini(nod->right);
        nod->info = temp->info;
        nod->right = removeNod(nod->right, temp->info, removed);
        return nod;
    }


    if (rel(e, nod->info)) {
        nod->left = removeNod(nod->left, e, removed);
    } else if (rel(nod->info, e)) {
        nod->right = removeNod(nod->right, e, removed);
    } else {
        if (!nod->left || !nod->right) {
            Node* temp;
            if (nod->left) {
                temp = nod->left;
            } else {
                temp = nod->right;
            }
            delete nod;
            sz--;
            removed = true;
            return temp;
        }
        Node* temp = mini(nod->right);
        nod->info = temp->info;
        nod->right = removeNod(nod->right, temp->info, removed);
    }
    return nod;
}

bool SortedSet::search(TComp elem) const {
    //BC=o(log(n)) WC=TC=o(n)
	return searchNode(root, elem);
}

bool SortedSet::searchNode(Node *nod, TElem elem) const {
    //BC=o(log(n)) WC=TC=o(n)
    if (!nod) {
        return false;
    }
    if (nod->info == elem) {
        return true;
    }
    if (rel(elem, nod->info)) {
        return searchNode(nod->left, elem);
    } else {
        return searchNode(nod->right, elem);
    }
}

int SortedSet::size() const {
    //theta(1)
	return sz;
}



bool SortedSet::isEmpty() const {
    //theta(1)
	return sz==0;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


void SortedSet::clearNod(Node *nod) {
    //BC=WC=TC=o(n)
    if(nod){
        clearNod(nod->right);
        clearNod(nod->left);
        delete nod;
    }
}

SortedSet::~SortedSet() {
    clearNod(root);
}

int SortedSet::difference(const SortedSet &s) {
    //BC=WC=TC=o(n)
    int nb=0;

    for(int i=0;i<s.sz;i++){
        bool rmv=false;

        if(search(s.root[i].info)){
            removeNod(root,s.root[i].info,rmv);
            if(rmv)
                nb++;
        }



    }
    return nb;
}





