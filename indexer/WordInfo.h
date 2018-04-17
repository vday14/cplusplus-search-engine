#pragma once

#include <vector>
#include <cctype>
class WordInfo {

public:

    WordInfo() {
        chunks = std::vector<int>();
        frequency = 0;
        docFrequency = 0;
        lastLocation = 0;
    }

    /**
     * Meant to parse in input from master DHT
     * @param value Value from DHT
     */
    WordInfo(string value) {
        if(value == "") {
            return;
        }
        int part = 0;
        string chunkInput = "";
        for(char val : value) {
            if(isnumber(val)) {
                chunkInput += val;
            } else if(val == ' ') {
                chunks.push_back(stoll(chunkInput));
                chunkInput = "";
            }  else if(val == '\t' && chunkInput != "") {
                if(part == 0) {
                    frequency = stoll(chunkInput);
                } else if(part == 1) {
                    lastLocation = stoll(chunkInput);
                }
                part++;
                chunkInput = "";
            }
        }
        if(chunkInput != "") {
            docFrequency = stoll(chunkInput);
        }
    }

    std::vector<int> chunks;
    size_t frequency;
    size_t docFrequency;
    size_t lastLocation;

};