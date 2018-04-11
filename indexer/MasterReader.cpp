#include <iostream>
#include "../DataStructures/DiskHashTable/MMDiskHashTable.h"
#include "../util/util.h"

int main() {
    string fileName = util::GetCurrentWorkingDir() + "/build/master.txt";
    MMDiskHashTable master = MMDiskHashTable(fileName, 30, 168);
    int currentChunk = 0;
    string key = "=totalDocsIndexed";
    string value = master.find(key);
    cout << value << endl;
}
