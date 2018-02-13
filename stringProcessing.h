//
// Created by anvia on 1/31/2018.
//

#ifndef EECS398_SEARCH_STRINGPROCESSING_H
#define EECS398_SEARCH_STRINGPROCESSING_H

#include <string>
#include <unordered_map>
#include <vector>
#include <iterator>

using namespace std;

//TODO
//remove tag words

//assuming we have a buffer from File Handle
//returns pointer to subStr in original text
/*char* preFindStr(char* originalText, char* subStr)
{
    bool isFound = true;
    char* temp = originalText;
    while ( isFound )
    {
        if ( *originalText == *subStr )
        {

        }
    }
}*/
/*char* postFindStr(char* originalText, char* subStr)
{
    bool isFound = true;
    while ( originalText != nullptr )
    {
        if ( *originalText != *subStr )
        {
            ++originalText;
        }

        if ( *originalText == *substr )
        if (originalText == nullptr || substr == nullptr)
        {
            isFound = false;
        }

        else if ( *originalText != *subStr )
        {
            isFound = false;
        }

        else
        {
            isFound = true;
        }

        ++subStr;
        ++originalText;
    }

    return originalText;

}*/


/*
 * Takes in an iterator to the original text and a substring: specifically for a parser functionality
 * Potentially make one that takes in two strings? Is this needed?
 */
string::iterator findStr(string::iterator originalText, string &subStr)
{

    auto begin_sub = subStr.begin();
    auto begin_original = originalText;

    while ( begin_original != nullptr)
    {
        //keep looking for instance of a match
        if ( *begin_original != *begin_sub )
        {
            ++begin_original;
        }

        else if ( *begin_original == *begin_sub )
        {
            /* want to keep the original iterator where it is so it
               can return the beginning of the matched word if found */
            auto temp = begin_original;
            while ( *temp == *begin_sub )
            {
                ++temp;
                ++begin_sub;
                //if it hits the end of the substring, it signifies an exact match
                if ( begin_sub  == nullptr)
                {
                    //this is pointing at the beginning of the match
                    return begin_original;
                }

            }
            //need to reset because still has to search rest of the string for a match
            begin_sub = subStr.begin();
            //sets the original text pointer to where the last search left off
            begin_original = temp;
        }

        else
        {
            //DO NOTHING
        }
    }

    return begin_original;
}
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
