//
// Created by nick on 2/6/18.
//

#ifndef EECS398_SEARCH_INDEXSTREAMREADER_H
#define EECS398_SEARCH_INDEXSTREAMREADER_H

#include <iostream>

using namespace std;

class IndexStreamReader {
public:
    int first();
    int last();
    int next(int location);
private:
    IndexStreamReader(string word);
    string word;
};

#endif //EECS398_SEARCH_INDEXSTREAMREADER_H
