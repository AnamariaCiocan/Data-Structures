#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
#include <cassert>

bool r22(TComp e1, TComp e2) {
    if (e1 <= e2) {
        return true;
    }
    else {
        return false;
    }
}
using namespace std;

int main() {
	testAll();
	testAllExtended();

    TComp e;

    SortedSet s1(r22);
    s1.add(7);
    s1.add(5);
    s1.add(190);

    SortedSet s2(r22);
    s2.add(5);
    s2.add(6);
    s2.add(9);


	cout << "Test end" << endl;
	system("pause");
}