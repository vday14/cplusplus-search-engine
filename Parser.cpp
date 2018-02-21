//
// Created by Veronica Day on 1/28/18.
//

// keep running count of offset, if stop word: don't incrememnt and remove stopword
// tokenizer returns pointer to document dictionary, parser puts it on the indexer's queue
//


#include <string>
#include <functional>
#include <queue>
#include <iostream>
#include <fstream>
#include <stringProcessing.h>

using namespace std;

// Doc Id
std::priority_queue<int> DOCID_PQ;
std::priority_queue<string> URL_PQ;
string PATH = "/doc";

//TEMP - remove once getting actual crawler input


//TODO
// get doc id from DocIDqueue (sent from crawler)
// go to disk and get the HTML file
// parse the html file
// if find url; send to crawler
// if find title send string to tokenizer
class Parser
{

public:

    struct raw_data {
        string url;
        string html_data;

        raw_data(string u, string h) : url(u), html_data(h){}
    };


    /**
     * Parser
     * @return
     */
    // input: object with char*  and URL string
    //
    string execute()
    {
        Tokenizer tokenizer();
        //TEMP - until we get real input from crawler
        raw_data data("url", "html");
        parse(data.html_data, &tokenizer);
        return tokenzier.get();


    }


private:

    /**
     * Parses file
     * @param inFile
     * @return
     */

    string parse(string &html_data, Tokenizer *tokenizer)
    {
        //figure out file handle syntax - pointer to file
        tokenizerInput = "";
        currentTerm = "";
        for (int i = 0; i < html_data.size(); ++i) {
            while (html_data[i] != ' ') {
                currentTerm += html_data[i];
            }

            //one method that directly adds urls onto frontier instead of checking for them
            if (!check_title(currentTerm)) {
                add_urls(current_term);
            }

            else {
                tokenizerInput += currentTerm;
                //can also pass titles individually through tokenizer instead of concatonating (idk how to spell)
            }
        }

        tokenizer->execute(tokenizerInput);
    }

    /*
     * Uses findStr function in stringProcessing.h: STILL HAVE TO TEST
     * Instead of bool, just directly adds on to url queue
     */
    void add_urls(string &word)
    {
        string a_tag = "<a";
        string http_start = "href=http";
        string http_end_tag = ">";

        auto word_iter = word.begin();
        url = "";
        word_iter = findStr(word_iter, a_tag);
        if (word_iter) {
            auto found_http = findStr(word_iter, http_start);
            if (found_http) {
                url = "http";
                found_http += 9;
                auto end_http = findStr(word_iter, http_end_tag);
                while (found_http != end_http) {
                    url += *found_http;
                    ++found_http;
                }
            }
        }

        else {
            return;
        }

        if (url != "") {
            URL_PQ.push(url);
        }


    }
    /**
     * Checks for url in string word
     * @param word
     */
    bool check_url(string &word)
    {
        //need to add string processing function where you check in a specified range of positions
        if (char* pos = strstr("href", word))
        {
            while (pos != "\"" && pos != "\'")
                ++pos;

            // take everything until next quote
            string url = "";
            ++pos;
            while (pos != "\"" && pos != "\'")
            {
                //filter out everything except http, https
                url += *pos;
            }

            // send it back to the crawler
            URL_PQ.push(url);
            return true;

        }

        return false;
    }

    /**
     * <title >AJF</title>
     * @param word
     */

    bool check_title(string &word)
    {
        /*if (char* pos = strstr("<title>", word))
        {
            pos += 6;
            end_pos = strstr("</title>", word);
            string title = "";
            while (pos != end_pos)
            {
                ++pos;
                title += *pos;

            }

            return title;
        }*/

        begin_title = "<title>";
        auto word_begin = word.begin();
        auto word_iter = findStr();

    }


};
