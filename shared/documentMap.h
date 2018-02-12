//
// Created by Jake Close on 2/8/18.
//

#pragma once

#include "url.h"
#include <string>
#include <vector>
using namespace std;
class Document
	{
	public:
		Url url;
		string domain;
		long docID;
		bool lastCrawlStatus;
		int lastCrawlDate;
		int lastCrawlPageCount;


		Document() {};


	};