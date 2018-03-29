//
// Created by nick on 3/23/18.
//

#include <iostream>
#include "HashTable.h"

using namespace std;

int main() {
    HashTable<string, string> ht;

    ht["hello"] = "goodbye";
    assert(ht["hello"] == "goodbye");
    ht["i want you to feel"] = "surreal";
    assert(ht["i want you to feel"] == "surreal");


    return 0;
}