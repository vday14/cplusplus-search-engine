#include "Indexer.h"

Indexer::Indexer() {

}

void Index::run() {
    while(!pointersToDirectories.empty()) {
        hashtable<string, vector<int>>* dicitonary = pointersToDirectories.pop();
        for(iterator it : dicitonary) {
            open/create it->first file;
            for(int num : it->second) {
                it->first.append(num + currentidcount)
            }
            save and close it->first
        }
    }
}