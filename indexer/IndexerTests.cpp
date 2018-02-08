//
// Created by nick on 2/6/18.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Indexer.h"

using namespace std;

int main() {
    Indexer indexer = Indexer();
    unordered_map<string, vector<int>> test1;
    unordered_map<string, vector<int>> test2;
    unordered_map<string, vector<int>> test3;
    unordered_map<string, vector<int>> test4;
    ifstream ifstream1("tests/test1.txt");
    ifstream ifstream2("tests/test2.txt");
    ifstream ifstream3("tests/test3.txt");
    ifstream ifstream4("tests/test4.txt");
    string word = "";
    int id = 0;
    while(ifstream1 >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } ), word.end());
        if(word != "")
            test1[word].push_back(id);
        id++;
    }
    while(ifstream2 >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } ), word.end());
        if(word != "")
            test2[word].push_back(id);
        id++;
    }
    while(ifstream3 >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } ), word.end());
        if(word != "")
            test3[word].push_back(id);
        id++;
    }
    while(ifstream4 >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } ), word.end());
        if(word != "")
            test4[word].push_back(id);
        id++;
    }
    indexer.pointerToDictionaries.Push(&test1);
    indexer.pointerToDictionaries.Push(&test2);
    indexer.pointerToDictionaries.Push(&test3);
    indexer.pointerToDictionaries.Push(&test4);
    indexer.run();
}