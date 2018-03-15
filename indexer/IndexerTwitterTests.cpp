// download and drag and drop .json files from 00 to 59 into tests/twitter
// https://archive.org/download/archiveteam-json-twitterstream/twitter-stream-2011-12-26.zip

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "json.hpp"
#include "Indexer.h"

using namespace std;
using json = nlohmann::json;

int main() {
//    Indexer indexer = Indexer();
//
//    vector<ifstream*> files;
//    for(int i = 0; i < 60; i++) {
//        string fileName = "tests/twitter/" + to_string(i) + ".json";
//        if(i < 10) {
//            fileName = "tests/twitter/0" + to_string(i) + ".json";
//        }
//        files.push_back(new ifstream(fileName));
//    }
//    string line = "";
//    for(int i = 0; i < 60; i++) {
//        int tweetId = 0;
//        while(getline(*files[i], line)) {
//            json j = json::parse(line);
//            auto local = new unordered_map<string, vector<int> >();
//            int id = 0;
//            if(j.find("text") != j.end()) {
//                string text = j.at("text");
//                string word = "";
//                bool midword = false;
//                for(auto character : text) {
//                    switch(character) {
//                        case '\n':
//                        case ' ':
//                            if(midword) {
//                                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
//                                word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } ), word.end());
//                                if(word != "") {
//                                    local->operator[](word).push_back(id);
//                                    id++;
//                                }
//                                word = "";
//                            }
//                            midword = false;
//                            break;
//                        default:
//                            word += character;
//                            midword = true;
//                    }
//                }
//                if(local->size() != 0) {
//                    size_t id = j.at("id");
//                    local->operator[]("=file " + to_string(i) + " tweet " + to_string(id)).push_back(0);
//                    tweetId++;
//                }
//            }
//            if(local->size() != 0) {
//                indexer.pointerToDictionaries.Push(local);
//            }
//        }
//    }
//    indexer.run();
    string query;
    cout << "What is your query?" << endl;
    getline(cin, query);
    istringstream ss(query);
    vector<string> queryTokens;
    while (ss >> query) {
        queryTokens.push_back(query);
    }
    vector<vector<size_t> > seekLocations;
    // open up seek files
    for(int i = 0; i < 9; i++) {
        string seekFileName = "index" + to_string(i) + "-seek.txt";
        vector<size_t> locs;
        int seekFile = open(seekFileName.c_str(), O_RDONLY);
        char character[1];
        string word;
        string seek;
        bool midword = false;
        bool midseek = false;
        // one char buffer haha use a mem map
        while(read(seekFile, character, 1)) {
            if(isalpha(character[0])) {
                midword = true;
                word += character[0];
            } else if(midword) {
                midword = false;
            }
            if(isnumber(character[0])) {
                midseek = true;
                seek += character[0];
            } else if(midseek) {
                for(auto query : queryTokens) {
                    if(query == word) {
                        locs.push_back(stoll(seek));
                    }
                }
                midseek = false;
                word = "";
                seek = "";
            }
        }
        seekLocations.push_back(locs);
    }
    cout << endl << "These are the locations in the indexes where we can find respective words." << endl;
    for(auto fileLoc : seekLocations) {
        for (auto loc : fileLoc) {
            cout << loc << " ";
        }
        cout << endl;
    }
    // open up indexes and get locs and doc ends
    vector<DocumentEnding> endings;
    cout << endl << "These are the locations of those words" << endl;
    for(int i = 0; i < 9; i++) {
        string indexFileName = "index" + to_string(i) + ".txt";
        int indexFile = open(indexFileName.c_str(), O_RDONLY);
        char buffer[100];
        for(int j = 0; j < seekLocations[i].size(); j++) {
            lseek(indexFile, seekLocations[i][j], SEEK_SET);
            read(indexFile, buffer, 100);
            for(int k = 0; k < 100; k++) {
                if(buffer[k] == '\n') {
                    break;
                }
                if(buffer[k]) {
                    cout << buffer[k];
                }
            }
            cout << endl;
        }
    }

    cout << endl << "These are the tweets with the query." << endl;
    for(int i = 0; i < 9; i++) {

    }

}
