#include "Indexer.h"

Indexer::Indexer( ProducerConsumerQueue < DocIndex * > *doc_index_queue_in,
						ProducerConsumerQueue < unordered_map < string, DocIndex * > > *anchor_in) :
		pointerToDictionaries( doc_index_queue_in ), AnchorQueue( anchor_in )
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
		if( pointerToDictionaries->Size( ) > 0)
			{

			DocIndex *dictionary = pointerToDictionaries->Pop( );
			numberDocsIndexed++;
			cout << "Number of documents indexed :: " << to_string(numberDocsIndexed) << endl;

			DocumentEnding docEnd = DocumentEnding( );
			size_t indexedCount = 0;
			currentBlockNumberDocs++;

			for ( auto word : *dictionary )
				{
				if ( word.first.at( 0 ) == '=' )
					{
					docEnd.url = word.first.substr( 1, word.first.length( ));
					continue;
					}
                chunkDictionary[word.first].docFrequency++;
                indexedCount += word.second.size( );
					currentBlockNumberWords += word.second.size( );

				for ( auto location : word.second )
					{
					masterDictionary[ word.first ].push_back( currentlyIndexed + location );
					}
				}

			currentlyIndexed += indexedCount;
			docEnd.docEndPosition = currentlyIndexed;
			docEnd.docNumWords = indexedCount;
			docEndings.push_back( docEnd );
			//add the url to the ->doc end map
			urlToDocEndings[ docEnd.url ] = docEnd.docEndPosition;


			if ( currentBlockNumberWords >= IndexerConstants::chunkSizeLimit )
				{
				cout << " --- Saving current chunk --- " << endl;
				save( );
				saveWordSeek( );
				reset( );
				}
			delete dictionary;
			}


		}
	cout << "Indexer is shutting down" << endl;
	save( );
	saveWordSeek( );
	reset( );
	saveChunkDictionary( );

	unordered_map < string, DocIndex * > anchorDict = AnchorQueue->Pop( );
	SaveAnchorText( &anchorDict );
	cout << " Indexer has finished running" << endl;
	return;
	}

void Indexer::save()
	{
	MMDiskHashTable seeker( util::GetCurrentWorkingDir( ) +
							IndexerConstants::pathToIndex +
							to_string( currentFile ) + "-seek.txt",
							IndexerConstants::chunkSeekKeySize, IndexerConstants::chunkSeekValueSize );
	string fileName = util::GetCurrentWorkingDir( ) +
                      IndexerConstants::pathToIndex +
                      to_string( currentFile ) + ".txt";
	int file = open( fileName.c_str( ), O_CREAT | O_WRONLY, S_IRWXU );

	seeker.insert("=numberUniqueWords", to_string(masterDictionary.size()));
	seeker.insert("=numberWords", to_string(currentBlockNumberWords));
	seeker.insert("=numberDocs", to_string(currentBlockNumberDocs));

	// TODO: these should really be c strings
	string statsHeader = "===STATS==="
                        "\nunique words: " + to_string( masterDictionary.size( )) +
                        "\nnumber words: " + to_string( currentBlockNumberWords ) +
                        "\nnumber docs: " + to_string( currentBlockNumberDocs ) +
                        "\n===========\n";
	write( file, statsHeader.c_str( ), strlen( statsHeader.c_str( )));

	// REALLY GROSS HACK
	size_t seekOffset = strlen( statsHeader.c_str( ));
	size_t chunkEnd = 0;

	for ( auto word : masterDictionary )
		{
		if ( word.first.size( ) > IndexerConstants::maxWordSize )
			{
			string resized = word.first;
			resized.resize( IndexerConstants::maxWordSize );
			seeker.insert( resized, to_string( seekOffset ));
			}
		else
			{
			seeker.insert( word.first, to_string( seekOffset ));
			}

		chunkDictionary[ word.first ].chunks.push_back( currentFile );

		bool firstPost = true;
		size_t lastOne = 0;
		int numIndexed = 0;
		for ( auto location : word.second )
			{
			if(chunkEnd < location) {
				chunkEnd = location;
			}
			chunkDictionary[ word.first ].frequency++;
			numIndexed++;
			if ( numIndexed == IndexerConstants::saveEveryXEntries )
				{
				SeekEntry entry = SeekEntry( );
				entry.offset = seekOffset;
				entry.realLocation = location;
                seekDictionary[ word.first ].push_back( entry );
				numIndexed = 0;
				}
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
	int docEndSeekCounter = 0; // save seek every 100 doc ends in the chunk
	for ( auto ending : docEndings )
		{
		string docEndString = "[" +
                                 ending.url + ", " +
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
        //seeker.CloseFile();
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

		if(key == "=docEnding")
			continue;

		if ( key.size( ) > IndexerConstants::maxWordSize )
			key.resize( IndexerConstants::maxWordSize );

		string value = "";
		for ( auto entry : word.second )
			value += ("<" + to_string( entry.offset ) +
					  ", " + to_string( entry.realLocation ) + "> ");

		wordSeek.insert( key, value );
		}
	string key = "=docEnding";
	string value = "";
	int currentEndingPartition = 0;
	for ( size_t i = 0; i < seekDictionary["=docEnding"].size( ); i++ )
		{
		string prospectiveDocEnding = "<" +
												to_string( seekDictionary["=docEnding"][ i ].offset ) +
												", " + to_string( seekDictionary["=docEnding"][ i ].realLocation ) + "> ";
		if ( value.size( ) + prospectiveDocEnding.size( ) <= IndexerConstants::chunkWordSeekValueSize )
			{
			value += prospectiveDocEnding;
			}
		else
			{
			wordSeek.insert( key + to_string( currentEndingPartition ), value );
			currentEndingPartition++;
			value = prospectiveDocEnding;
			}
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


void Indexer::SaveAnchorText( unordered_map < string, DocIndex * > *anchorDict )
	{

	//TODO create pointer to anchor


	//pointerToAnchor->Pop();
	//pass a dictionary of
	//map <url string> - >  vector<anchor word>
	//for each url in map
	//look up url string in  url -> docEnding map
	//for each anchor text in url map
	// create a  anchor text - > list of doc endings
	//write to disk

	cout << " -- SAVING ANCHOR TEXT --- " << endl;
	for ( auto const &ent1 : *anchorDict )
		{
		auto const &outer_key = ent1.first;
		//cout << "url: " << outer_key << endl;

		if ( urlToDocEndings.find( outer_key ) != urlToDocEndings.end( ))
			{
			size_t docEndForUrl = urlToDocEndings[ outer_key ];
			//cout << "Urls doc end : " << docEndForUrl << endl;

			}


		DocIndex *inner_map = ent1.second;

		for ( auto const &ent2 : *inner_map )
			{


			auto const &inner_key = ent2.first;
			auto const &inner_value = ent2.second;
			//cout << "url: " << outer_key << endl;
			//cout << "anchor text : " << inner_key << endl;
			//for(auto offset :inner_value)
			//	cout << "offset " << offset << endl;


			}

		}


	}


