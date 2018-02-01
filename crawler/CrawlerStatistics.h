//
// Created by Ben Bergkamp on 2/1/18.
//

#ifndef EECS398_SEARCH_CRAWLERSTATISTICS_H
#define EECS398_SEARCH_CRAWLERSTATISTICS_H

#include "../ThreadClass.h"

class CrawlerStatistics : public ThreadClass {

public:
    CrawlerStatistics() { };
    virtual void FuncToRun();

private:
    //members

};


#endif //EECS398_SEARCH_CRAWLERSTATISTICS_H
