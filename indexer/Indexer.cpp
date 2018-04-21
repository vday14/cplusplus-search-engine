#include "Indexer.h"

Indexer::Indexer( ProducerConsumerQueue < DocIndex * > *doc_index_queue_in, size_t doc_to_crawl_in) :
		pointerToDictionaries( doc_index_queue_in ), docsToCrawl( doc_to_crawl_in)

	{
	currentFile = 0;
	currentlyIndexed = 0;
	currentBlockNumberWords = 0;
	currentBlockNumberDocs = 0;
	numberDocsIndexed = 0;
	}

void Indexer::run()
	{
	while ( *alive || pointerToDictionaries->Size( ) > 0 )
		{
		if( pointerToDictionaries->Size( ) > 0 )
			{
			DocIndex *dictionary = pointerToDictionaries->Pop( );
			if( ( numberDocsIndexed++ ) % 100 == 0 ) 
				{
				std::cout << "Number of documents indexed :: " 
					<< to_string(numberDocsIndexed) << "\n";
				}

			if ( numberDocsIndexed == docsToCrawl )
				break;

			DocumentEnding docEnd = DocumentEnding( );
			size_t indexedCount = 0;
			currentBlockNumberDocs++;

			for ( auto word : *dictionary )
				{
				if ( word.first.at( 0 ) == '=' )
					{
                    if( word.second.front( ) == 0) 
                        docEnd.url = word.first.substr(1, word.first.length());
                    else if( word.second.front( ) == 1 ) 
						{
						docEnd.title = "No title";
						string title = word.first.substr(1, word.first.length());
						if(title != "")
                        	docEnd.title = word.first.substr(1, word.first.length());
						}
					continue;
					}

				string resized = word.first;

				if(resized.size() > IndexerConstants::maxWordSize)
					resized.resize(IndexerConstants::maxWordSize);

				chunkDictionary[ resized ].docFrequency++;
                indexedCount += word.second.size( );
				currentBlockNumberWords += word.second.size( );
				
				for ( auto location : word.second )
					{
					masterDictionary[ resized ].push_back( currentlyIndexed + 
						location );
					}
				}

			currentlyIndexed += indexedCount;
			docEnd.docEndPosition = currentlyIndexed;
			docEnd.docNumWords = indexedCount;
			docEndings.push_back( docEnd );

			if ( currentBlockNumberWords >= IndexerConstants::chunkSizeLimit )
				{
				std::cout << " --- Saving current chunk ---\n";
				save( );
				saveWordSeek( );
				reset( );
				}
			delete dictionary;
			}
		}
	std::cout << "Indexer is shutting down\n";
	save( );
	saveWordSeek( );
	reset( );
	saveChunkDictionary( );
	std::cout << " Indexer has finished running\n";
	return;
	}

void Indexer::save()
	{
	MMDiskHashTable seeker( util::GetCurrentWorkingDir( ) +
							IndexerConstants::pathToIndex +
							to_string( currentFile ) + "-seek.txt",
							IndexerConstants::chunkSeekKeySize, 
							IndexerConstants::chunkSeekValueSize );
	string fileName = util::GetCurrentWorkingDir( ) +
                      IndexerConstants::pathToIndex +
                      to_string( currentFile ) + ".txt";
	int file = open( fileName.c_str( ), O_CREAT | O_WRONLY, S_IRWXU );

	seeker.insert("=numberUniqueWords", to_string( masterDictionary.size( ) ) );
	seeker.insert("=numberWords", to_string( currentBlockNumberWords ) );
	seeker.insert("=numberDocs", to_string( currentBlockNumberDocs ) );

	string statsHeader = "===STATS==="
                        "\nunique words: " + to_string( masterDictionary.size( )) +
                        "\nnumber words: " + to_string( currentBlockNumberWords ) +
                        "\nnumber docs: " + to_string( currentBlockNumberDocs ) +
                        "\n===========\n";
	write( file, statsHeader.c_str( ), strlen( statsHeader.c_str( )));

	size_t seekOffset = strlen( statsHeader.c_str( ) );
	size_t chunkEnd = 0;

	for ( auto word : masterDictionary )
		{
		if ( word.first.size( ) > IndexerConstants::maxWordSize )
			{
			string resized = word.first;
			resized.resize( IndexerConstants::maxWordSize );
			seeker.insert( resized, to_string( seekOffset ) );
			}
		else
			{
			seeker.insert( word.first, to_string( seekOffset ) );
			}

		chunkDictionary[ word.first ].chunks.push_back( currentFile );

		bool firstPost = true;
		size_t lastOne = 0;
		int numIndexed = 0;
		for ( auto location : word.second )
			{
			if( chunkEnd < location ) {
				chunkEnd = location;
			}
			chunkDictionary[ word.first ].frequency++;
			numIndexed++;
			if ( firstPost )
				{
				string locationSpace = to_string( location ) + " ";
				write( file, locationSpace.c_str( ), strlen( locationSpace.c_str( )));
				seekOffset += strlen( locationSpace.c_str( ));
				firstPost = false;
				}
			else
				{
				size_t delta = location - lastOne;
				string deltaSpace = to_string( delta ) + " ";
				write( file, deltaSpace.c_str( ), strlen( deltaSpace.c_str( )));
				seekOffset += strlen( deltaSpace.c_str( ));
				}
			if ( numIndexed == IndexerConstants::saveEveryXEntries )
			    {
				SeekEntry entry = SeekEntry( );
				entry.offset = seekOffset;
				entry.realLocation = location;
				seekDictionary[ word.first ].push_back( entry );
				numIndexed = 0;
			    }
				lastOne = location;
			}
		chunkDictionary[ word.first ].lastLocation = lastOne;
		write( file, "\n", 1 );
		seekOffset += 1;
		}

	string docEndingHeader = "===Document Endings===\n";
	write( file, docEndingHeader.c_str( ), strlen( docEndingHeader.c_str( )));
	seekOffset += strlen( docEndingHeader.c_str( ));
	seeker.insert( "=docEnding", to_string( seekOffset ));
	int docEndSeekCounter = 0;
	for ( auto ending : docEndings )
		{
		string title = "";
		for(char letter : ending.title) {
			if(letter != ',' && letter != ']' && letter != '[' && letter != '\n' 
				&& letter != '\"' && letter != '\\' && letter != '&' 
				&& letter != ':') {
				title.push_back(letter);
			}
		}
		string toDiskTitle = title;
		string toDiskUrl = ending.url;

		toDiskUrl.erase(std::remove_if(toDiskUrl.begin(),
									   toDiskUrl.end(),
									   [](unsigned char x){return std::isspace(x);}),
							 		   toDiskUrl.end());
		toDiskUrl = util::removeAllStr(toDiskUrl, "\\");
		toDiskTitle = util::removeAllStr(toDiskTitle, "\\");
		toDiskTitle = util::removeAllStr(toDiskTitle, "\\n");
		toDiskTitle = util::removeAllStr(toDiskTitle, "\\t");
		toDiskTitle = util::removeAllStr(toDiskTitle, "\\v");
		toDiskTitle = util::removeAllStr(toDiskTitle, "\\r");
		toDiskTitle = util::removeAllStr(toDiskTitle, "\\f");

		string docEndString = "[" + toDiskUrl + ", " + 
								toDiskTitle + ", " +
                                to_string( ending.docEndPosition ) + ", " +
                                to_string( ending.docNumWords ) + "]\n";
		write( file, docEndString.c_str( ), strlen( docEndString.c_str( )));
		docEndSeekCounter++;
		if ( docEndSeekCounter == IndexerConstants::saveEveryXEntries )
			{
			docEndSeekCounter = 0;
			seekDictionary["=docEnding"].push_back( SeekEntry(ending.docEndPosition, seekOffset ));
			}
		seekOffset += strlen( docEndString.c_str( ));
		}
	chunkEndLocation.push_back(chunkEnd);
	close( file );
	}

void Indexer::saveChunkDictionary()
	{
	MMDiskHashTable dhtChunk = MMDiskHashTable( util::GetCurrentWorkingDir( ) +
												IndexerConstants::pathToIndex +
												"master.txt", IndexerConstants::masterKeySize,
												IndexerConstants::masterValueSize );
	for ( auto word : chunkDictionary )
		{
		string key = word.first;
		if ( key.size( ) > IndexerConstants::maxWordSize )
			key.resize( IndexerConstants::maxWordSize );

		string value = "";
		for ( auto chunk : word.second.chunks )
			value += to_string( chunk ) + " ";

		value += "\t" + to_string( word.second.frequency );
		value += "\t" + to_string( word.second.lastLocation);
		value += "\t" + to_string( word.second.docFrequency);
		dhtChunk.insert( key, value );
		}
    dhtChunk.insert("=numberChunks", to_string(currentFile));
	dhtChunk.insert("=numberUniqueWords", to_string(chunkDictionary.size()));
	dhtChunk.insert("=totalNumberIndexed", to_string(currentlyIndexed));
	dhtChunk.insert("=totalDocsIndexed", to_string(numberDocsIndexed));
	int currentChunk = 0;
	for(auto location : chunkEndLocation)
		{
		string key = "=chunk" + to_string(currentChunk);
		dhtChunk.insert(key, to_string(location));
		currentChunk++;
		}
	}

void Indexer::saveWordSeek()
	{
	MMDiskHashTable wordSeek = MMDiskHashTable(util::GetCurrentWorkingDir( ) +
											   IndexerConstants::pathToIndex +
											   to_string( currentFile ) + "-wordseek.txt",
											   IndexerConstants::chunkWordSeekKeySize,
											   IndexerConstants::chunkWordSeekValueSize );
	for ( auto word : seekDictionary )
		{
		string key = word.first;
		int currentPartition = 0;

		if ( key.size( ) > IndexerConstants::maxWordSize )
			key.resize( IndexerConstants::maxWordSize );

		string value = "";
		for ( auto entry : word.second ) {
			string prospectiveSeek = "<" + to_string(entry.offset) +
					  ", " + to_string(entry.realLocation) + "> ";
			if(value.size() + prospectiveSeek.size() <= IndexerConstants::chunkWordSeekValueSize) {
				value += prospectiveSeek;
			} else {
				wordSeek.insert(key + to_string(currentPartition), value);
				currentPartition++;
				value = prospectiveSeek;
			}
		}

		wordSeek.insert( key + to_string(currentPartition), value );
		}
		currentFile++;
	}

void Indexer::reset()
	{
	masterDictionary.clear( );
	docEndings.clear( );
	seekDictionary.clear();
	currentBlockNumberWords = 0;
	currentBlockNumberDocs = 0;
	}


void Indexer::Kill()
	{
	*(this->alive) = false;
	//currentFile++;
	}
