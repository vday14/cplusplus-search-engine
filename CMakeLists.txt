cmake_minimum_required(VERSION 3.9)
project(eecs398_search)

#set(dir ${CMAKE_CURRENT_SOURCE_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")

set(CMAKE_CXX_STANDARD 11)

add_executable(QueueTest
        shared/ProducerConsumerQueue.h
        shared/ProducerConsumerQueue_test.cpp)

add_executable(TryPopTest
        shared/TryPopTest.cpp
        shared/ProducerConsumerQueue.h
        shared/ThreadClass.cpp
        shared/ParsedUrl.cpp
        crawler/crawler.cpp
        crawler/UrlFrontier.cpp
        crawler/Readers/StreamReader.h
        crawler/Readers/HttpReader.cpp
        crawler/Readers/HttpsReader.cpp
        crawler/Readers/LocalReader.cpp
        crawler/spider.cpp
        util/util.cpp
        shared/Document.cpp
        parser/Parser.cpp
        util/Stemmer.cpp
        util/Tokenizer.cpp
        util/stringProcessing.cpp
        indexer/Indexer.cpp
        )

add_executable(crawler-parser-Test
        main.cpp
        shared/ProducerConsumerQueue.cpp
        shared/ThreadClass.cpp
        shared/ParsedUrl.cpp
        crawler/crawler.cpp
        crawler/UrlFrontier.cpp
        crawler/Readers/StreamReader.h
        crawler/Readers/HttpReader.cpp
        crawler/Readers/HttpsReader.cpp
        crawler/Readers/LocalReader.cpp
        crawler/spider.cpp
        util/util.cpp
        shared/Document.cpp
        parser/Parser.cpp
        util/Stemmer.cpp
        util/Tokenizer.cpp
        util/stringProcessing.cpp
        indexer/Indexer.cpp)


add_executable(crawler-parser-indexer-Test
        main.cpp
        shared/ProducerConsumerQueue.h
        shared/ThreadClass.cpp
        shared/ParsedUrl.cpp
        crawler/crawler.cpp
        crawler/UrlFrontier.cpp
        crawler/Readers/StreamReader.h
        crawler/Readers/HttpReader.cpp
        crawler/Readers/HttpsReader.cpp
        crawler/Readers/LocalReader.cpp
        crawler/spider.cpp
        util/util.cpp
        shared/Document.cpp
        parser/Parser.cpp
        util/Stemmer.cpp
        util/Tokenizer.cpp
        util/stringProcessing.cpp
        indexer/Indexer.cpp)



add_executable(isolated-integration
        crawler/tests/crawlerTest.cpp
        shared/ProducerConsumerQueue.h
        shared/ThreadClass.cpp
        crawler/UrlFrontier.cpp
        shared/ParsedUrl.cpp
        crawler/crawler.cpp
        crawler/Readers/StreamReader.h
        crawler/Readers/HttpReader.cpp
        crawler/Readers/HttpsReader.cpp
        crawler/Readers/LocalReader.cpp
        crawler/spider.cpp
        util/util.cpp
        shared/Document.cpp
        parser/Parser.cpp
        util/Stemmer.cpp
        util/Tokenizer.cpp
        util/stringProcessing.cpp
        indexer/Indexer.cpp)




add_executable(url-frontier-test
        crawler/tests/urlFrontierTest.cpp
        shared/ProducerConsumerQueue.h
        shared/ThreadClass.cpp
        shared/ParsedUrl.cpp
        crawler/crawler.cpp
        crawler/UrlFrontier.cpp
        crawler/Readers/StreamReader.h
        crawler/Readers/HttpReader.cpp
        crawler/Readers/HttpsReader.cpp
        crawler/Readers/LocalReader.cpp
        crawler/spider.cpp
        util/util.cpp
        shared/Document.cpp
        parser/Parser.cpp
        util/Stemmer.cpp
        util/Tokenizer.cpp
        util/stringProcessing.cpp
        indexer/Indexer.cpp)

add_executable(StringProcessingTest
        util/stringProcessing.cpp
        util/Stemmer.cpp
        util/tests/stringProcessingTest.cpp)

add_executable(TokenizerTest
        util/Tokenizer.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp
        util/tests/tokenizerTest.cpp)

add_executable(StemmerTest
        util/stringProcessing.cpp
        util/Stemmer.cpp
        util/tests/stemmerTest.cpp)

add_executable(ParserTest
        parser/Parser.cpp
        shared/Document.cpp
        shared/ParsedUrl.cpp
        util/util.cpp
        util/Tokenizer.cpp
        shared/ProducerConsumerQueue.h
        util/stringProcessing.cpp
        util/Stemmer.cpp
        crawler/UrlFrontier.cpp
        parser/tests/parserTest.cpp
        crawler/Readers/StreamReader.h
        crawler/Readers/LocalReader.cpp
        crawler/Readers/HttpReader.cpp
        crawler/Readers/HttpsReader.cpp
        ranker/Ranker.cpp
        indexer/Corpus.cpp
        indexer/Chunk.cpp
        ranker/Site.cpp
        ranker/Scorer.cpp
        query/queryLanguage/QueryParser.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISREndDoc.cpp
        query/Query.cpp
        parser/queryTokenizer.cpp
        )


add_executable(URLTEST
        shared/ParsedUrl.cpp
        shared/urlTest.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp

        )

add_executable(search-engine
        search.cpp
        query/Searcher.cpp
        util/DataStructureLib/tuple.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp
        util/util.cpp
        constraintSolver/ISRContainer.cpp
        constraintSolver/ISR.h
        ranker/Ranker.cpp
        indexer/Corpus.cpp
        indexer/Chunk.cpp
        ranker/Site.cpp
        ranker/Scorer.cpp
        query/queryLanguage/QueryParser.cpp
        constraintSolver/ISREndDoc.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISRAnd.cpp
        constraintSolver/ISROr.cpp
        query/Query.cpp
        parser/queryTokenizer.cpp
        shared/ThreadClass.cpp)


add_executable(querySpeedTest
        query/querySpeedTest.cpp
        query/Searcher.cpp
        util/DataStructureLib/tuple.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp
        util/util.cpp
        constraintSolver/ISRContainer.cpp
        constraintSolver/ISR.h
        ranker/Ranker.cpp
        indexer/Corpus.cpp
        indexer/Chunk.cpp
        ranker/Site.cpp
        ranker/Scorer.cpp
        query/queryLanguage/QueryParser.cpp
        constraintSolver/ISREndDoc.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISRAnd.cpp
        constraintSolver/ISROr.cpp
        query/Query.cpp
        parser/queryTokenizer.cpp
        shared/ThreadClass.cpp
        )

add_executable(ISRWord-tests
        util/util.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/tests/ISRWordTests.cpp
        constraintSolver/ISREndDoc.cpp
        util/stringProcessing.cpp
        indexer/Chunk.cpp
        indexer/Corpus.cpp
        util/Stemmer.cpp )

add_executable(ISREndDoc-tests
        util/util.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp
        constraintSolver/ISREndDoc.cpp
        constraintSolver/tests/ISREndDocTests.cpp)

add_executable(ISROR-tests
        util/util.cpp
        constraintSolver/ISR.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISROr.cpp
        constraintSolver/tests/ISROrTests.cpp
        constraintSolver/ISREndDoc.cpp
        indexer/Corpus.cpp
        indexer/Chunk.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp )

add_executable(ISRAnd-tests
        constraintSolver/tests/ISRAndTests.cpp
        indexer/Corpus.cpp
        indexer/Chunk.cpp
        util/util.cpp
        constraintSolver/ISR.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISRAnd.cpp
        constraintSolver/ISREndDoc.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp )

add_executable(ISRWord-Multi-Test
        constraintSolver/tests/ISRWordMultiTest.cpp
        util/util.cpp
        constraintSolver/ISR.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISRAnd.cpp
        constraintSolver/ISREndDoc.cpp
        util/stringProcessing.cpp
        indexer/Corpus.cpp
        indexer/Chunk.cpp
        util/Stemmer.cpp )

add_executable(ISRMultiWordORTest
        constraintSolver/tests/ISRMultiWordORTest.cpp
        util/util.cpp
        constraintSolver/ISR.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISRAnd.cpp
        constraintSolver/ISREndDoc.cpp
        util/DataStructureLib/tuple.cpp
        indexer/Corpus.cpp
        indexer/Chunk.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp

        )
add_executable(NestedAnd
        constraintSolver/tests/nestedAnd.cpp
        util/util.cpp
        constraintSolver/ISR.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISRContainer.cpp
        constraintSolver/ISRAnd.cpp
        constraintSolver/ISROr.cpp

        constraintSolver/ISREndDoc.cpp
        util/DataStructureLib/tuple.cpp
        indexer/Corpus.cpp
        indexer/Chunk.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp
        query/queryLanguage/QueryParser.cpp
        ranker/Ranker.cpp
        ranker/Scorer.cpp
        ranker/Site.cpp
        )

add_executable(Scorer-tests
        ranker/tests/ScorerTest.cpp
        ranker/Scorer.cpp
        ranker/Site.cpp
        ranker/Ranker.cpp
        util/util.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISREndDoc.cpp
        util/stringProcessing.cpp
        indexer/Corpus.cpp
        util/Stemmer.cpp
        indexer/Chunk.cpp
        parser/queryTokenizer.cpp
        util/Tokenizer.cpp
        query/Query.cpp)

add_executable(DataStructures-Vector-tests
        DataStructures/Vector/Vector.h
        DataStructures/Vector/VectorTests.cpp)

add_executable(DataStructures-HashTable-tests
        DataStructures/HashTable/HashTable.h
        DataStructures/HashTable/HashTableTests.cpp)

add_executable(DataStructures-q-DiskHashTable-tests
        DataStructures/DiskHashTable/DiskHashTable.h
        DataStructures/DiskHashTable/DiskHashTableTests.cpp)

add_executable(Indexer-twitter-tests
        DataStructures/DiskHashTable/MMDiskHashTable.h
        indexer/Indexer.cpp
        indexer/json.hpp
        util/stringProcessing.cpp
        util/Stemmer.cpp
        util/util.cpp
        shared/ThreadClass.cpp
        indexer/IndexerTwitterTests.cpp indexer/WordInfo.h)

add_executable(MasterReader-tests
        DataStructures/DiskHashTable/MMDiskHashTable.h
        util/stringProcessing.cpp
        util/Stemmer.cpp
        util/util.cpp
        indexer/MasterReader.cpp
        )


add_executable(Corpus-tests
        indexer/tests/CorpusTests.cpp
        indexer/Corpus.cpp
        indexer/Chunk.cpp
        DataStructures/DiskHashTable/MMDiskHashTable.h
        util/stringProcessing.cpp
        util/Stemmer.cpp
        util/util.cpp
        )


add_executable(rankerTests
        ranker/tests/RankerTest.cpp
        ranker/Ranker.cpp
        ranker/Scorer.cpp
        ranker/Site.cpp
        util/util.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISREndDoc.cpp
        util/stringProcessing.cpp
        indexer/Corpus.cpp
        util/Stemmer.cpp
        indexer/Chunk.cpp
        parser/queryTokenizer.cpp
        util/Tokenizer.cpp
        query/Query.cpp

        )

add_executable(testISRQueryTuple
        query/queryLanguage/tests/queryIsrTest.cpp
        query/queryLanguage/QueryParser.cpp
        util/DataStructureLib/tuple.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp
        util/util.cpp
        constraintSolver/ISRContainer.cpp
        constraintSolver/ISR.h
        ranker/Ranker.cpp
        ranker/Site.cpp
        ranker/Scorer.cpp
        constraintSolver/ISREndDoc.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISRAnd.cpp
        constraintSolver/ISROr.cpp

        )

add_executable(server
        site/LinuxTinyServer.cpp
        query/Query.cpp
        parser/queryTokenizer.cpp
        query/Searcher.cpp
        util/DataStructureLib/tuple.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp
        util/util.cpp
        constraintSolver/ISRContainer.cpp
        constraintSolver/ISR.h
        ranker/Ranker.cpp
        indexer/Corpus.cpp
        indexer/Chunk.cpp
        ranker/Site.cpp
        ranker/Scorer.cpp
        query/queryLanguage/QueryParser.cpp
        constraintSolver/ISREndDoc.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISRAnd.cpp
        constraintSolver/ISROr.cpp
        shared/ThreadClass.cpp

        )

add_executable(testQueryParser
        query/queryLanguage/tests/testQueryParser.cpp
        query/queryLanguage/QueryParser.cpp
        util/Tokenizer.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp
        )


add_executable(testQueryLanguage
        query/queryLanguage/tests/testQueryParser.cpp
        query/queryLanguage/QueryParser.cpp
        util/DataStructureLib/tuple.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp
        )

add_executable(ISRAndTwitterIntegrityTest
        constraintSolver/ISR.h
        constraintSolver/ISRAnd.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISREndDoc.cpp
        indexer/json.hpp
        util/stringProcessing.cpp
        util/Stemmer.cpp
        util/util.cpp
        indexer/Corpus.cpp
        indexer/Chunk.cpp
        constraintSolver/tests/ISRAndTwitterIntegrityTest.cpp)

add_executable(devtool-SumSpaceNumbers
        devtools/SumSpaceNumbers.cpp)

add_executable(testSVM
        RankSVM/train/train.cpp
        RankSVM/SVM.cpp
        util/util.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp
        ranker/Site.cpp
        ranker/Scorer.cpp
        query/Query.cpp
        parser/queryTokenizer.cpp

        )

find_package(OpenSSL REQUIRED)

target_link_libraries(TryPopTest OpenSSL::SSL)

#target_link_libraries(query-Ranker-tests OpenSSL::SSL)

target_link_libraries(ParserTest OpenSSL::SSL)

target_link_libraries(isolated-integration OpenSSL::SSL pthread)
target_link_libraries(url-frontier-test OpenSSL::SSL pthread)

target_link_libraries(crawler-parser-Test OpenSSL::SSL pthread)
target_link_libraries(crawler-parser-indexer-Test OpenSSL::SSL pthread)

target_link_libraries(QueueTest pthread)
target_link_libraries(Scorer-tests OpenSSL::SSL pthread)
target_link_libraries(search-engine OpenSSL::SSL pthread)

target_link_libraries(server OpenSSL::SSL pthread)





