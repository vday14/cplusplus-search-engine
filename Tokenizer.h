//
// Created by anvia on 1/31/2018.
//

#include <string>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <stringProcessing.h>
using namespace std;

class Tokenizer
{
public:
    Tokenizer() {}

    const unordered_map<string, vector<int>> & get() const
    {
        return &doc_index;
    }

    void execute(string originalText)
    {
        int offset = 0;
        vector<string> splitText = splitStr(originalText, ' ');
        string lowerString = "";
        for (int i = 0; i < splitText.size(); ++i)
        {
            lowerString = toLower(splitText);
            if (!isStopWord(lowerString))
            {
                doc_index[lowerString].push_back(offset);
                ++offset;
            }
        }
    }

private:
    unordered_map<string, vector<int>> doc_index;
};
