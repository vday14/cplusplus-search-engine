//
// Created by Veronica Day on 1/28/18.
//

#include <string>
#include <functional>
#include <queue>
#include <iostream>
#include <fstream>

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


		parse(inFile);




		//TODO
		// close file and remove

	}


private:

	 /**
	  * Parses file
	  * @param inFile
	  * @return
	  */
	 string parse(ifstream inFile)
	 {
		 string word = "";
		 while (!inFile.eof())
		 {
			 inFile >> word;

			 // checks for url
			 check_url(word);

			 // checks for title tags
			 Tokenizer.execute(check_title(word));
		 }

	 }

	 /**
	  * Checks for url in string word
	  * @param word
	  */
	 void check_url(string &word)
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
				 url += *pos;
			 }

			 // send it back to the crawler
			 URL_PQ.push(url);
		 }
	 }

	 /**
	  * <title >AJF</title>
	  * @param word
	  */
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