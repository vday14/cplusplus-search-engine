#pragma once

#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <atomic>
#include <string.h>
#include <algorithm>
#include "../shared/ProducerConsumerQueue.h"
#include "../shared/ThreadClass.h"
#include "DocumentEnding.h"
#include "SeekEntry.h"
#include "../DataStructures/DiskHashTable/MMDiskHashTable.h"
#include "../util/util.h"
#include "WordInfo.h"
#include "IndexerConstants.h"

// Pulls dictionaries from the parser and merges them into the master index,
// which is saved on disk.

using DocIndex = const unordered_map< string, vector < unsigned long > >;

class Indexer : public ThreadClass
	{
public:
	Indexer ( ProducerConsumerQueue< DocIndex * > *doc_index_queue_in ,
			  ProducerConsumerQueue < unordered_map<string , DocIndex * > >  *anchor_in ,
	size_t doc_to_crawl_in);

	void run ( );
	void Kill ( );
	size_t numberDocsIndexed;

private:
	void save ( );
    void saveWordSeek();
    void saveChunkDictionary ( );
	void reset ( );

	ProducerConsumerQueue< DocIndex * > *pointerToDictionaries;

	// for master.txt file - includes chunks the words appear in, the last 
	// real location of the word, frequency, and doc frequency
	unordered_map< string, WordInfo > chunkDictionary;
	vector<size_t> chunkEndLocation;

	unordered_map< string, vector< size_t > > masterDictionary;
	unordered_map< string, vector< SeekEntry > > seekDictionary;
	vector< DocumentEnding > docEndings;

	size_t currentFile;
	size_t currentlyIndexed;
	size_t currentBlockNumberWords;
	size_t currentBlockNumberDocs;
	size_t docsToCrawl;
	atomic_bool* alive = new atomic_bool(true);

};
