/***
 * Class to represent each website in the ranking engine
 */
#ifndef EECS398_SEARCH_SITE_H
#define EECS398_SEARCH_SITE_H

#include <string>
#include <unordered_map>


struct data
	{
	unsigned long frequency;
	};

class Site
	{
public:

	double getScore();
	std::string url;
	double score;
	bool hasBeenScored;
	std::unordered_map< std::string, data> wordData;
	};
#endif //EECS398_SEARCH_SITE_H
