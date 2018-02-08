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
    test1["whale"] = { 3, 6, 12 };
    test1["dog"] = { 1, 5, 15 };
    test1["agouti"] = {2, 8, 41 };
    indexer.pointerToDictionaries.Push(&test1);
    indexer.run();
}