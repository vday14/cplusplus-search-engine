//
// Created by nick on 3/22/18.
//

#include <iostream>
#include <cassert>
#include "Vector.h"
#include <vector>

using namespace std;

// TOOO: COMPREHENSIVE TESTS
int main() {
    Vector<int> test1;
    test1.reserve(20);
    vector<int> test62;
    test62.reserve(20);
    test1[51] = 52;
    test62[51] = 352;
    test1.push_back(50);
    assert(test1[0] == 50);
    assert(test1.size() == 1);
    test1[0] = 150;
    assert(test1[0] == 150);
    assert(test1.size() == 1);
    cout << "ALL VECTOR TESTS PASS :)" << endl;
}

