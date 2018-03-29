//
// Created by nick on 3/16/18.
//

#include <iostream>
#include <set>
#include "../../indexer/DocumentEnding.h"
#include "../ISRWord.h"
#include "../ISREndDoc.h"


using namespace std;

int main ( )
{
    char* query;
    ISRWord queryWord("aare");
    ISREndDoc endDocs;
    vector<size_t> locations;
    vector<DocumentEnding> docEnds;
    set<string> urls;
    while(queryWord.getCurrentLocation() != MAX_Location) {
        locations.push_back(queryWord.Next());
    }
    while(endDocs.next().url != "aaa")
        {
        for(auto locs : locations)
            {
            if(locs < endDocs.getCurrentDoc().docEndPosition &&
               locs >= (endDocs.getCurrentDoc().docEndPosition - endDocs.getCurrentDoc().docNumWords)) {
                urls.insert(endDocs.getCurrentDoc().url);
            }
        }

        }
    for(auto urrl : urls) {
        cout << urrl << endl;
    }
    return 0;
}