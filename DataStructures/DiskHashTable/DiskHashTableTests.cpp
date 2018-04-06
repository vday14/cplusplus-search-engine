#include <iostream>
#include <vector>
#include <chrono>
#include <cassert>
#include <unordered_map>
#include "MMDiskHashTable.h"
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
    const size_t NUMBER_OF_ELEMENTS = 10000;
    DiskHashTable dht = DiskHashTable("DataStructures/DiskHashTable/test1.txt", 10, 8);

    vector<pair<string, string>> data;

    double totalInsertionTime = 0.0;
    for(size_t i = 0; i < NUMBER_OF_ELEMENTS; i++) {
        auto start = clock();
        dht.insert(to_string(i), to_string(i));
        auto end = clock();
        totalInsertionTime += (end - start) / (double) CLOCKS_PER_SEC;
    }
    cout << "Total time to insert " << NUMBER_OF_ELEMENTS << " key-value pairs into DHT: " << totalInsertionTime << endl;
    cout << "Average insertion time for DHT: " << totalInsertionTime / NUMBER_OF_ELEMENTS << endl;

    double totalLookupTime = 0.0;
    for(size_t i = 0; i < NUMBER_OF_ELEMENTS; i++) {
        auto start = clock();
        assert(dht.find(to_string(i)) == to_string(i));
        auto end = clock();
        totalLookupTime += (end - start) / (double) CLOCKS_PER_SEC;
    }
    cout << "Average lookup time for DHT: " << totalLookupTime / NUMBER_OF_ELEMENTS << endl << endl;

    MMDiskHashTable mmdht = MMDiskHashTable("DataStructures/DiskHashTable/test.txt", 10, 8);
    totalInsertionTime = 0.0;
    for(size_t i = 0; i < NUMBER_OF_ELEMENTS; i++) {
        auto start = clock();
        mmdht.insert(to_string(i), to_string(i));
        auto end = clock();
        totalInsertionTime += (end - start) / (double) CLOCKS_PER_SEC;
    }
    cout << "Total time to insert " << NUMBER_OF_ELEMENTS << " key-value pairs into MMDHT: " << totalInsertionTime << endl;
    cout << "Average insertion time for MMDHT: " << totalInsertionTime / NUMBER_OF_ELEMENTS << endl;

    totalLookupTime = 0.0;
    for(size_t i = 0; i < NUMBER_OF_ELEMENTS; i++) {
        auto start = clock();
        assert(mmdht.find(to_string(i)) == to_string(i));
        auto end = clock();
        totalLookupTime += (end - start) / (double) CLOCKS_PER_SEC;
    }
    cout << "Average lookup time for MMDHT: " << totalLookupTime / NUMBER_OF_ELEMENTS << endl << endl;

    unordered_map<string, string> stlTest;
    totalInsertionTime = 0.0;
    for (size_t i = 0; i < NUMBER_OF_ELEMENTS; i++) {
        auto start = clock();
        stlTest[to_string(i)] = to_string(i);
        auto end = clock();
        totalInsertionTime += (end - start) / (double) CLOCKS_PER_SEC;
    }
    cout << "Total time to insert " << NUMBER_OF_ELEMENTS << " key-value pairs into unordered_map: " << totalInsertionTime << endl;
    cout << "Average insertion time for STL unordered_map: " << totalInsertionTime / NUMBER_OF_ELEMENTS << endl;

    totalLookupTime = 0.0;
    for (size_t i = 0; i < NUMBER_OF_ELEMENTS; i++) {
        auto start = clock();
        assert(stlTest[to_string(i)] == to_string(i));
        auto end = clock();
        totalLookupTime += (end - start) / (double) CLOCKS_PER_SEC;
    }
    cout << "Average lookup time for STL unordered_map: " << totalLookupTime / NUMBER_OF_ELEMENTS << endl;

    assert(dht.find("macos") == "");
    assert(mmdht.find("macos") == "");
}
