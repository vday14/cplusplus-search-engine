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
    char* query = "iphone";
    ISRWord queryWord("fsfasfas");
    ISREndDoc endDocs;
    vector<size_t> locations;
    vector<DocumentEnding> docEnds;
    set<string> urls;
    locations.push_back(queryWord.getCurrentLocation());
    while(queryWord.getCurrentLocation() != MAX_Location) {
        locations.push_back(queryWord.Next());
    }
    for(auto loc : locations) {
        cout << loc << endl;
    }
//    while(endDocs.next().url != "aaa")
//        {
//        for(auto locs : locations)
//            {
//            if(locs < endDocs.getCurrentDoc().docEndPosition &&
//               locs >= (endDocs.getCurrentDoc().docEndPosition - endDocs.getCurrentDoc().docNumWords)) {
//                urls.insert(endDocs.getCurrentDoc().url);
//            }
//        }
//
//        }
//    for(auto urrl : urls) {
//        cout << urrl << endl;
//    }
    return 0;
}