//
// Created by Jake Close on 3/13/18.
//

#pragma once

#include <iostream>
#include <vector>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "WordSeek.h"
#include "../util/util.h"
#include "../indexer/DocumentEnding.h"

// Find occurrences of document ends.

class ISREndDoc
	{
public:
	ISREndDoc();
	DocumentEnding next();
	DocumentEnding getCurrentDoc();
	unsigned GetDocumentLength ( );
	unsigned GetTitleLength ( );
	string getURL ( );
private:
	DocumentEnding currentDoc;
	char* memMap;
	int currentChunk;
    int currentFile;
    vector<size_t> getSeekContents();

};


