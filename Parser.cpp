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

//TODO
// get doc id from DocIDqueue (sent from crawler)
// go to disk and get the HTML file
// parse the html file
	// if find url; send to crawler
	// if find title send string to tokenizer
class Parser
{

public:

	/**
	 * Parser
	 * @return
	 */
	string execute()
	{
		ifstream inFile;
		string docid = to_string(DOCID_PQ.top());

		inFile.open(PATH+docid);

		// error checking
		if (!inFile)
			cerr << "Unable to open file datafile.txt";

        Tokenizer tokenizer();
		parse(inFile, &tokenizer);

        return tokenizer.get();



		//TODO
		// close file and remove

	}


private:

	 /**
	  * Parses file
	  * @param inFile
	  * @return
	  */

	 string parse(ifstream inFile, Tokenizer *tokenizer)
	 {
		 //figure out file handle syntax - pointer to file
		 string word = "";
		 while (!inFile.eof())
		 {
			 inFile >> word;

			 // checks for url

			 if (!check_url(word))
             {
                 // checks for title tags
                 tokenizer->execute(check_title(word));

             }


		 }

	 }

    /*
     * Uses findStr function in stringProcessing.h: STILL HAVE TO TEST
     * Instead of bool, just directly adds on to url queue
     */
    void add_urls(string word)
    {
        string http_tag = "<a href=http";

        auto word_iter = word.begin();
        auto http_substr = http_tag.begin();
        string url_name = "";

        //will add all instances of wanted URLs until it hits end of string
        while (word_iter != nullptr)
        {
            // sets word_iterator to next instance of URL from where it currently is
            word_iter = findStr(word_iter, http_substr);
            //in the case there is no url in the word
            if (word_iter != nullptr)
            {
                //sets iterator to start of url content
                word_iter += 12;
                url_name = "http";
                //end of url tag
                auto tag_end = ("</a>", word);
                while (word_iter != tag_end)
                {
                    url_name += *word_iter;
                    ++word_iter;
                }
                //sets iterator to one past the closing tag </a>
                word_iter += 4;
                URL_PQ.push(url_name);
                //resets substr so it can look for next instance
                http_substr = http_tag.begin();
            }
        }
    }
	 /**
	  * Checks for url in string word
	  * @param word
	  */
	 bool check_url(string &word)
	 {
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

     string check_title_handle(string &word)
     {
         string titleTag = "<title>";
         string closeTitleTag = "</title>";
         auto wordBegin = word.begin();

         string allTitles = "";
         while (wordBegin != nullptr)
         {
             wordBegin = findStr(wordBegin, titleTag);

             if (wordBegin == nullptr)
             {
                 return allTitles;
             }

             //increments until first letter past opening title tag
             wordBegin += 7;
             auto end_title = findStr(wordBegin, closeTitleTag);
             while (wordBegin != end_title)
             {
                 allTitles += *wordBegin;
                 ++wordBegin;

                 if (wordBegin == nullptr)
                 {
                     return allTitles;
                 }
             }

             //increments until first letter past closing title tag
             wordBegin += 8;
         }

         return allTitles;
     }
	 string check_title(string &word)
	 {
		 if (char* pos = strstr("<title>", word))
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
		 }

	 }


};