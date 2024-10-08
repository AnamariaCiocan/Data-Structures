#include <iostream>
#include "PriorityQueue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <cassert>
using namespace std;

bool rel1(TPriority p1, TPriority p2) {
    if (p1 <= p2) {
        return true;
    }
    else {
        return false;
    }
}


int main() {
	testAll();
	testAllExtended();
    PriorityQueue pq(rel1);
    pq.push(8,8);
    pq.push(5,8);
    pq.push(8,9);
    pq.push(9,9);
    assert(pq.priorityOf(3)==-1);
    assert(pq.priorityOf(8)==8);
    assert(pq.priorityOf(9)==9);
	cout << "End" << endl;
	system("pause");

}
