#include <iostream>
#include <fstream>
#include <unordered_map>
#include <thread>
#include "../ISRWord.h"
#include "../ISRAnd.h"
#include "../../indexer/json.hpp"
#include "../../indexer/IndexerConstants.h"

using namespace std;
using json = nlohmann::json;

vector<ifstream *> files;
vector<thread> threads;

void run(int file);

int main() {
    for (int i = 0; i < 3; i++) {
        string fileName = util::GetCurrentWorkingDir() + "/indexer/tests/twitter/" + to_string(i) + ".json";
        if (i < 10) {
            fileName = util::GetCurrentWorkingDir() + "/indexer/tests/twitter/0" + to_string(i) + ".json";
        }
        files.push_back(new ifstream(fileName));
    }
    for(int i = 0; i < 3; i++) {
        threads.push_back(thread(run, i));
    }
    for(int i = 0; i < 3; i++) {
        threads[i].join();
    }
    return 0;
}

void run(int file) {
    ofstream integrityFile(util::GetCurrentWorkingDir() + IndexerConstants::pathToIndex + "integrity" + to_string(file) + ".txt");
    double bestTime = numeric_limits<double>().max();
    double worstTime = numeric_limits<double>().min();
    int correct = 0;
    int number = 0;
    string line = "";
    while (getline(*files[file], line)) {
        json j = json::parse(line);
        if (j.find("text") != j.end()) {
            vector<ISR*> words;
            string text = j.at("text");
            string word = "";
            bool midword = false;
            for (auto character : text) {
                switch (character) {
                    case '\n':
                    case ' ':
                        if (midword) {
                            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                            word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }),
                                       word.end());
                            if (word != "") {
                                if(word.size() > IndexerConstants::maxWordSize) {
                                    word.resize(IndexerConstants::maxWordSize);
                                }
                                words.push_back(new ISRWord(word));
                            }
                            word = "";
                        }
                        midword = false;
                        break;
                    default:
                        word += character;
                        midword = true;
                }
            }
            if(!word.empty()) {
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }),
                           word.end());
                if (word != "") {
                    if(word.size() > IndexerConstants::maxWordSize) {
                        word.resize(IndexerConstants::maxWordSize);
                    }
                    words.push_back(new ISRWord(word));
                }
                word = "";
            }
            if(words.size() > 1) {
                size_t id = j.at("id");
                string realUrl = "file" + to_string(file) + "tweet" + to_string(id);
                unordered_map<string, int> urls;
                ISRAnd *query = new ISRAnd(words);
                clock_t start = clock();
                while (query->GetCurrentLocation() != MAX_Location) {
                    auto url = query->GetEndDocument()->getCurrentDoc().url;
                    urls[url] = 1;
                    if (url == realUrl) {
                        break;
                    }
                    query->NextDocument();
                }
                // assert(urls[realUrl] == 1);
                if(urls[realUrl] == 1) {
                    correct++;
                    clock_t end = clock();
                    double time = (end - start) / (double) CLOCKS_PER_SEC;
                    if (time < bestTime) {
                        bestTime = time;
                    }
                    if (time > worstTime) {
                        worstTime = time;
                    }
                    integrityFile << "PASSED FOR LINE: " << text << " in " << time << " seconds!!!" << endl;
                } else {
                    integrityFile << "QUERY FAILED FOR LINE: " << text << endl;
                }
                number++;
            }
        }
    }
    cout << "Read " << file << endl;
    integrityFile << "Percentage correct: " << (double) correct / number << endl;
    integrityFile << "\tNumber correct: " << correct << endl;
    integrityFile << "\tNumber queries: " << number << endl;
    integrityFile << "Worst lookup time: " << worstTime << endl;
    integrityFile << "Best lookup time: " << bestTime << endl;
}