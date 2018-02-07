//
// Created by nick on 2/6/18.
//

#include <iostream>
#include <thread>
#include "Indexer.h"

using namespace std;

int main() {
    Indexer indexer = Indexer();
    unordered_map<string, vector<int>> test1;
    test1["cat"] = { 12, 15, 17 };
    test1["dog"] = { 1, 5, 15 };
    indexer.pointerToDictionaries.Push(&test1);
    indexer.run();
}