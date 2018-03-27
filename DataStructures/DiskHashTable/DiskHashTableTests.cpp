#include <iostream>
#include <vector>
#include <chrono>
#include <cassert>
#include <unordered_map>
#include "DiskHashTable.h"

using namespace std;

string randomString(int length) {
    string set = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string randomString = "";
    for(int i = 0; i < length; i++) {
        randomString += set[rand() % 61 + 1];
    }
    return randomString;
}

int main() {
    DiskHashTable dht = DiskHashTable("DataStructures/DiskHashTable/test.txt", 10, 8);

    vector<pair<string, string>> data;
//    data.push_back({"sherlock", "holmes"});
//    data.push_back({"kendrick", "lamar"});
//    data.push_back({"hello", "goodbye"});
//    data.push_back({"moon", "landing"});
//    data.push_back({"barack", "obama"});
//    data.push_back({"katy", "perry"});
//    data.push_back({"anderson", "paak"});
//    data.push_back({"dunder", "mifflin"});
//    data.push_back({"university", "michigan"});
//    data.push_back({"abel", "tesfaye"});
//    data.push_back({"vince", "staples"});
//    data.push_back({"danny", "brown"});
//    data.push_back({"ann", "arbor"});
//    data.push_back({"tame", "impala"});
//    data.push_back({"machine", "learning"});
//    data.push_back({"north", "face"});
//    data.push_back({"eecs", "398"});
//    data.push_back({"intel", "corei7"});
//    data.push_back({"constraint", "solver"});
//    data.push_back({"multi", "threaded"});
//    data.push_back({"march", "madness"});
//    data.push_back({"sister", "nation"});
//    data.push_back({"daft", "punk"});
//    data.push_back({"the god", "anddevil"});
//    data.push_back({"are raging", "insideme"});
//    data.push_back({"hiatus", "kaiyote"});
//    data.push_back({"jai", "wolf"});
//    data.push_back({"griz", "psgfy"});
//    data.push_back({"stack", "overflow"});
//    data.push_back({"carpenter", "brut"});
//    data.push_back({"harry", "potter"});
//    data.push_back({"fall out", "boy"});
//    data.push_back({"red hot", "chili"});
//    data.push_back({"after", "laughter"});
//    data.push_back({"carly rae", "jepsen"});
//    data.push_back({"lana del", "rey"});
//    data.push_back({"system of", "a down"});

    auto startInsertionTime = clock();
    double totalInsertionTime = 0.0;
    for(size_t i = 0; i < 1000000; i++) {
        auto start = clock();
        dht.insert(to_string(i), to_string(i));
        auto end = clock();
        totalInsertionTime += (end - start) / (double) CLOCKS_PER_SEC;
    }
    auto endInsertionTime = clock();
    cout << "Total time to insert 1000000 key-value pairs into DHT: " << (endInsertionTime - startInsertionTime) /
            (double) CLOCKS_PER_SEC << endl;
    cout << "Average insertion time for DHT: " << totalInsertionTime / 1000000.0 << endl;

    double totalLookupTime = 0.0;
    for(size_t i = 0; i < 1000000; i++) {
        auto start = clock();
        assert(dht.find(to_string(i)) == to_string(i));
        auto end = clock();
        totalLookupTime += (end - start) / (double) CLOCKS_PER_SEC;
    }
    cout << "Average lookup time for DHT: " << totalLookupTime / 1000000.0 << endl;

    unordered_map<string, string> stlTest;

    totalInsertionTime = 0.0;
    for (size_t i = 0; i < 1000000; i++) {
        auto start = clock();
        stlTest[to_string(i)] = to_string(i);
        auto end = clock();
        totalInsertionTime += (end - start) / (double) CLOCKS_PER_SEC;
    }
    cout << "Average insertion time for STL unordered_map: " << totalInsertionTime / 1000000.0 << endl;

    totalLookupTime = 0.0;
    for (size_t i = 0; i < 1000000; i++) {
        auto start = clock();
        assert(stlTest[to_string(i)] == to_string(i));
        auto end = clock();
        totalLookupTime += (end - start) / (double) CLOCKS_PER_SEC;
    }
    cout << "Average lookup time for STL unordered_map: " << totalLookupTime / 1000000.0 << endl;

    assert(dht.find("macos") == "");
}
