//
// Created by anvia on 1/31/2018.
//

#ifndef EECS398_SEARCH_STRINGPROCESSING_H
#define EECS398_SEARCH_STRINGPROCESSING_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

//TODO
//remove tag words

set<string> stopWords = {"a", "all", "an", "and", "any", "are", "as", "at", "be", "been", "but", "by", "few", "from", "for", "have", "he", "her", "here", "him", "his", "how",
                         "i", "in", "is", "it", "its", "many ","me", "my", "none", "of", "on", "or", "our", "she", "some", "the", "their", "them", "there", "they", "that",
                         "this", "to", "us", "was", "what", "when", "where", "which", "who", "why", "will", "with", "you", "your" };

vector<string> splitStr(string &originalText, char delim)
{
    vector<string> splitWords;
    auto begin = originalText.begin();
    auto end = originalText.end();
    while (begin != end)
    {
        string word = "";
        while (begin != delim && begin != end)
        {
            word += *begin;
            ++begin;
        }

        splitWords.push_back(word);
    }

    return splitWords;

}

bool isStopWord(string &word)
{
    return stopWords.find(word) != nullptr;

}

string toLower(string &word)
{
    auto iter = word.begin();
    lowerWord = "";
    while (iter != word.end())
    {
        if (*iter < 65 || *iter > 90)
        {
            lowerWord += (*iter + 32);
        }

        else
        {
            lowerWord += *iter;
        }
    }

    return lowerWord;
}

#endif //EECS398_SEARCH_STRINGPROCESSING_H
