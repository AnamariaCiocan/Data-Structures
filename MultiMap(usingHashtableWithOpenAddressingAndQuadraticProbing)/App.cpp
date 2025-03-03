#include <iostream>
#include <cassert>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"

using namespace std;


int main() {


	testAll();
	testAllExtended();
    MultiMap m;
    m.add(1, 100);
    m.add(2, 200);
    m.add(3, 300);
    m.add(4,4);
    MultiMap p;
    p.add(1,1);
    p.add(2,33);
    p.add(7,9);
    p.add(3,309);
    assert(m.updateValues(p)==3);
	cout << "End" << endl;
	system("pause");

}
