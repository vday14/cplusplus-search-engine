#include "Indexer.h"

Indexer::Indexer ( ProducerConsumerQueue< DocIndex * > *doc_index_queue_in ) : pointerToDictionaries(
		doc_index_queue_in )
	{
	currentFile = 0;
	currentlyIndexed = 0;

	currentBlockNumberWords = 0;
	currentBlockNumberDocs = 0;

	}

void Indexer::run ( )
	{

	bool cond = true;

    while(alive) {

        DocIndex * dictionary = pointerToDictionaries->Pop();
		 cout << "INDEX GOT A NEW Dictionary" << endl;
        DocumentEnding docEnd = DocumentEnding();
        size_t indexedCount = 0;
        currentBlockNumberDocs++;

        for(auto word : *dictionary) {
            if(word.first.at(0) == '=') {
                docEnd.url = word.first.substr(1, word.first.length());
                continue;
            }

            indexedCount += word.second.size();
            currentBlockNumberWords += word.second.size();

            for(auto location : word.second) {
                masterDictionary[word.first].push_back(currentlyIndexed + location);
            }
        }

        currentlyIndexed += indexedCount;
        docEnd.docEndPosition = currentlyIndexed;
        docEnd.docNumWords = indexedCount;
        docEndings.push_back(docEnd);

        if(currentBlockNumberWords >= 100000 || alive == false) {
            save();
            reset();
        }
    }

    save();
    reset();
    saveChunkDictionary();
	cout << "Indexer has finished running" << endl;
	return ;
}

void Indexer::verbose_run() {
	/*
    while(pointerToDictionaries.Size() != 0) {
		 	DocIndex *pointerToDictionaries.Pop();
        for(auto word : dictionary) {
	        for(auto location : word.second) {
//                indexedCount++;
                masterDictionary[word.first].push_back(location);
                }
            }
        }
        */
	}

void Indexer::save ( )
	{
	map< string, vector< size_t > > maps( masterDictionary.begin( ), masterDictionary.end( ) );
	map< string, size_t > seeker;
	string fileName = util::GetCurrentWorkingDir( ) + "/indexer/output/" + to_string( currentFile ) + ".txt";
	int file = open( fileName.c_str( ), O_CREAT | O_WRONLY, S_IRWXU );

	// TODO: these should really be c strings
	string statsHeader = "===STATS==="
			                     "\nunique words: " + to_string( masterDictionary.size( ) ) +
	                     "\nnumber words: " + to_string( currentBlockNumberWords ) +
	                     "\nnumber docs: " + to_string( currentBlockNumberDocs ) +
	                     "\n===========\n";
	write( file, statsHeader.c_str( ), strlen( statsHeader.c_str( ) ) );

	// REALLY GROSS HACK
	size_t seekOffset = strlen( statsHeader.c_str( ) );

	for ( auto word : maps )
		{
		seeker[ word.first ] = seekOffset;
		chunkDictionary[ word.first ].push_back( currentFile );
//        string wordBreak = word.first + "\n";
//        write(file, wordBreak.c_str(), strlen(wordBreak.c_str()));
//        seekOffset += strlen(wordBreak.c_str());
		bool firstPost = true;
		size_t lastOne = 0;
		int numIndexed = 0;
		for ( auto location : word.second )
			{
			numIndexed++;
			if ( numIndexed >= 100 )
				{
				PostingsSeekTableEntry entry = PostingsSeekTableEntry( );
				entry.offset = seekOffset;
				entry.realLocation = location;
				postingsSeekTable[ word.first ].push_back( entry );
				numIndexed = 0;
				}
			if ( firstPost )
				{
				string locationSpace = to_string( location ) + " ";
				write( file, locationSpace.c_str( ), strlen( locationSpace.c_str( ) ) );
				seekOffset += strlen( locationSpace.c_str( ) );
				firstPost = false;
				}
			else
				{
				size_t delta = location - lastOne;
				string deltaSpace = to_string( delta ) + " ";
				write( file, deltaSpace.c_str( ), strlen( deltaSpace.c_str( ) ) );
				seekOffset += strlen( deltaSpace.c_str( ) );
				}
			lastOne = location;
			}
		write( file, "\n", 1 );
		seekOffset += 1;
		}

	string docEndingHeader = "===Document Endings===\n";
	write( file, docEndingHeader.c_str( ), strlen( docEndingHeader.c_str( ) ) );
	seekOffset += strlen( docEndingHeader.c_str( ) );
	seeker[ "=docEnding" ] = seekOffset;

	for ( auto ending : docEndings )
		{
		string docEndString = "[" +
		                      ending.url + ", " +
		                      to_string( ending.docEndPosition ) + ", " +
		                      to_string( ending.docNumWords ) + "]\n";
		write( file, docEndString.c_str( ), strlen( docEndString.c_str( ) ) );
		}

	// TODO: seek dictionary
	string seekFileName = util::GetCurrentWorkingDir( ) + "/indexer/output/" + to_string( currentFile ) + "-seek.txt";
	int seekFile = open( seekFileName.c_str( ), O_CREAT | O_WRONLY, S_IRWXU );
	for ( auto word : seeker )
		{
		string line = word.first + " " + to_string( word.second ) + "\n";
		write( seekFile, line.c_str( ), strlen( line.c_str( ) ) );
		if ( postingsSeekTable.find( word.first ) != postingsSeekTable.end( ) )
			{
			string offsetLine = "\t";
			for ( int i = 0; i < postingsSeekTable[ word.first ].size( ); i++ )
				{
				offsetLine += "<" +
				              to_string( postingsSeekTable[ word.first ][ i ].realLocation ) +
				              ", " +
				              to_string( postingsSeekTable[ word.first ][ i ].offset ) +
				              "> ";
				}
			offsetLine += "\n";
			write( seekFile, offsetLine.c_str( ), strlen( offsetLine.c_str( ) ) );
			}
		}

	close( file );
	currentFile++;
	}

void Indexer::saveChunkDictionary ( )
	{
	string fileName = util::GetCurrentWorkingDir( ) + "/indexer/output/master-index.txt";
	int file = open( fileName.c_str( ), O_CREAT | O_WRONLY, S_IRWXU );
	for ( auto word : chunkDictionary )
		{
		string wordDictionary = word.first + " ";
		for ( auto chunk : word.second )
			{
			wordDictionary += to_string( chunk ) + " ";
			}
		wordDictionary += "\n";
		write( file, wordDictionary.c_str( ), strlen( wordDictionary.c_str( ) ) );
		}
	close( file );
	}

void Indexer::verbose_save ( )
	{
	map< string, vector< size_t > > maps( masterDictionary.begin( ), masterDictionary.end( ) );
	for ( auto word : maps )
		{
		cout << word.first << endl;
		for ( auto location : word.second )
			{
			cout << location << " ";
			}
		cout << endl;
		}
	currentFile++;
	}

void Indexer::reset ( )
	{
	masterDictionary.clear( );
	docEndings.clear( );
	postingsSeekTable.clear( );

	currentBlockNumberWords = 0;
	currentBlockNumberDocs = 0;
	}


void Indexer::Kill()
	{
	this->alive = false;
	}