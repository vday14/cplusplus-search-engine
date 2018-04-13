// download and drag and drop .json files from 00 to 59 into tests/twitter
// https://archive.org/download/archiveteam-json-twitterstream/twitter-stream-2011-12-26.zip

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "../shared/ProducerConsumerQueue.h"
#include "json.hpp"
#include "../util/util.h"
#include "Indexer.h"

using namespace std;
using json = nlohmann::json;

using DocIndex = const unordered_map< string, vector< unsigned long > >;

int main ( ) {
	vector<ifstream *> files;
	ProducerConsumerQueue< DocIndex * > *IndexerQueue = new ProducerConsumerQueue< DocIndex * >( );
	ProducerConsumerQueue< unordered_map<string , DocIndex * >  > *AnchorQueue = new ProducerConsumerQueue< unordered_map<string , DocIndex * >  >( );
	for (int i = 0; i < 60; i++) {
		string fileName = util::GetCurrentWorkingDir() + "/indexer/tests/twitter/" + to_string(i) + ".json";
		if (i < 10) {
			fileName = util::GetCurrentWorkingDir() + "/indexer/tests/twitter/0" + to_string(i) + ".json";
		}
		files.push_back(new ifstream(fileName));
	}
	string line = "";
	for (int i = 0; i < 60; i++) {
		int tweetId = 0;
		while (getline(*files[i], line)) {
			json j = json::parse(line);
			auto local = new unordered_map< string, vector< unsigned long > >();
			int id = 0;
			if (j.find("text") != j.end()) {
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
									local->operator[](word).push_back(id);
									id++;
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
						local->operator[](word).push_back(id);
						id++;
					}
					word = "";
				}
				if (local->size() != 0) {
					size_t id = j.at("id");
					local->operator[]("=file " + to_string(i) + " tweet " + to_string(id)).push_back(0);
					local->operator[]("=" + text).push_back(1);
					tweetId++;
				}
			}
			if (local->size() != 0) {
				IndexerQueue->Push(local);
			}
		}
	}
	Indexer indexer = Indexer(IndexerQueue, AnchorQueue);
    indexer.StartThread( );
    indexer.WaitForFinish();
    return 0;
	/*
	string query;
	cout << "What is your query?" << endl;
	getline( cin, query );
	istringstream ss( query );
	vector< string > queryTokens;
	while ( ss >> query )
		{
		queryTokens.push_back( query );
		}
	vector< vector< size_t > > seekLocations;
	vector< size_t > docEndingLocations;
	vector< vector< DocumentEnding > > docEndings( 9 );
	// open up seek files
	for ( int i = 0; i < 9; i++ )
		{
		string seekFileName = "index" + to_string( i ) + "-seek.txt";
		vector< size_t > locs;
		int seekFile = open( seekFileName.c_str( ), O_RDONLY );
		char character[1];
		string word;
		string seek;
		bool midword = false;
		bool midseek = false;
		// one char buffer haha use a mem map
		while ( read( seekFile, character, 1 ) )
			{
			if ( isalpha( character[ 0 ] ) )
				{
				midword = true;
				word += character[ 0 ];
				}
			else if ( midword )
				{
				midword = false;
				}
			if ( isnumber( character[ 0 ] ) )
				{
				midseek = true;
				seek += character[ 0 ];
				}
			else if ( midseek )
				{
				for ( auto query : queryTokens )
					{
					if ( query == word )
						{
						locs.push_back( stoll( seek ) );
						}
					}
				if ( word == "docEnding" )
					{
					docEndingLocations.push_back( stoll( seek ) );
					}
				midseek = false;
				word = "";
				seek = "";
				}
			}
		seekLocations.push_back( locs );
		}
	cout << endl << "These are the locations in the indexes where we can find respective words." << endl;
	for ( auto fileLoc : seekLocations )
		{
		bool hasLoc = false;
		for ( auto loc : fileLoc )
			{
			cout << loc << " ";
			hasLoc = true;
			}
		if ( hasLoc ) cout << endl;
		}
	// open up indexes and get locs and doc ends
	vector< vector< size_t > > locations( queryTokens.size( ) );
	cout << endl << "These are some of the locations of those words" << endl;
	for ( int i = 0; i < 9; i++ )
		{
		string indexFileName = "index" + to_string( i ) + ".txt";
		int indexFile = open( indexFileName.c_str( ), O_RDONLY );
		char buffer[1024];
		cout << "\tin file " << i << ": " << endl;
		for ( int j = 0; j < seekLocations[ i ].size( ); j++ )
			{
			cout << "\t\tfor word " << queryTokens[ j % seekLocations.size( ) ] << ": ";
			lseek( indexFile, seekLocations[ i ][ j ], SEEK_SET );
			read( indexFile, buffer, 1024 );
			string loc = "";
			bool midloc = false;
			for ( int k = 0; k < 1024; k++ )
				{
				if ( buffer[ k ] == '\n' )
					{
					break;
					}
				if ( buffer[ k ] == ' ' )
					{
					if ( midloc )
						{
						locations[ j % seekLocations.size( ) ].push_back( stoll( loc ) );
						cout << loc << " ";
						loc = "";
						}
					midloc = false;
					}
				else if ( buffer[ k ] )
					{
					midloc = true;
					loc += buffer[ k ];
					}
				}
			cout << endl;
			}
		char docEndBuffer[1];
		lseek( indexFile, docEndingLocations[ i ], SEEK_SET );
		DocumentEnding ending;
		string input;
		enum ENDING_PART
			{
			URL, ENDING_LOC, SIZE
			};
		ENDING_PART part = URL;
		while ( read( indexFile, docEndBuffer, 1 ) )
			{
			if ( docEndBuffer[ 0 ] == '[' )
				{
				ending = DocumentEnding( );
				}
			else if ( docEndBuffer[ 0 ] != ' ' && docEndBuffer[ 0 ] != ',' && docEndBuffer[ 0 ] != ']' &&
			          docEndBuffer[ 0 ] != 'n' )
				{
				input += docEndBuffer[ 0 ];
				}
			else if ( docEndBuffer[ 0 ] == ',' )
				{
				if ( part == URL )
					{
					ending.url = input;
					part = ENDING_LOC;
					}
				else if ( part == ENDING_LOC )
					{
					ending.docEndPosition = stoll( input );
					part = SIZE;
					}
				else
					{
					ending.docNumWords = stoll( input );
					}
				input = "";
				}
			else if ( docEndBuffer[ 0 ] == ']' )
				{
				docEndings[ i ].push_back( ending );
				part = URL;
				}
			}
		}

//    for(auto doc : docEndings) {
//        for(auto loc : doc) {
//            cout << loc.url << endl;
//        }
//    }

	cout << endl << "These are the tweets that match the query." << endl;
	for ( int i = 0; i < 9; i++ )
		{

		}

	}
	 */
}
