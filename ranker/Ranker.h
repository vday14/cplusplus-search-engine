//
// Created by anvia on 3/29/2018.
//

#ifndef EECS398_SEARCH_RANKER_H
#define EECS398_SEARCH_RANKER_H

#include <queue>
#include "../constraintSolver/ISRWord.h"
#include "../parser/Parser.h"
#include "../util/Tokenizer.h"


class Ranker {
    //Send query to parser - have to create new functions in parser, and initialize query vector
    Ranker( std::vector< ISRWord > *ISRsIn, std::unordered_map< std::string, std::vector< unsigned long > > *query_in );
    //Get word from ISR 'get word?' method
    unsigned long docFrequency ( std::string word );
    //TODO figure out input, some way to access a 'stats' folder - ask Nick
    unsigned long getNumDocs ( );
    //TODO figure out input, some way to access a 'stats' folder - ask Nick
    unsigned long getDocFreq( );
    std::vector< unsigned long > tfIdfVec( );
    unsigned long cosineSim( std::vector< unsigned long > queryTfIdfs, std::vector < unsigned long > docTfIdfs );
    //TODO phrase matching: add 1 / log(distance) between words to points?



    //need distance


private:
    std::vector< ISRWord > *wordISRs;
    const std::unordered_map< std::string, std::vector< unsigned long > > *queryVector;
};


#endif //EECS398_SEARCH_RANKER_H
