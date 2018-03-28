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

    while(cond) {
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

        if(currentBlockNumberWords >= 10000) {
            save();
            reset();
        }
    }

    save();
    reset();
    saveChunkDictionary();
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
	MMDiskHashTable seeker(util::GetCurrentWorkingDir( ) + "/indexer/output/" + to_string( currentFile ) + "-seek.txt", 30, 8 );
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

	for ( auto word : masterDictionary )
		{
			if(word.first.size() > 30) {
				string resized = word.first;
				resized.resize(30);
				seeker.insert(resized, to_string(seekOffset));
			} else {
				seeker.insert(word.first, to_string(seekOffset));
			}

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
	seeker.insert("=docEnding", to_string(seekOffset));

	for ( auto ending : docEndings )
		{
		string docEndString = "[" +
		                      ending.url + ", " +
		                      to_string( ending.docEndPosition ) + ", " +
		                      to_string( ending.docNumWords ) + "]\n";
		write( file, docEndString.c_str( ), strlen( docEndString.c_str( ) ) );
		}

	close( file );
	currentFile++;
	}

void Indexer::saveChunkDictionary ( )
	{
		MMDiskHashTable dhtChunk = MMDiskHashTable(util::GetCurrentWorkingDir() + "/indexer/output/index-master.txt", 30, 168);
		for ( auto word : chunkDictionary )
		{
			string key = word.first;
			if(key.size() > 30) {
				key.resize(30);
			}
			string value = "";
		for ( auto chunk : word.second )
			{
			value += to_string( chunk ) + " ";
			}
			dhtChunk.insert(key, value);
		}
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
