cmake_minimum_required(VERSION 3.9)
project(eecs398_search)

set(CMAKE_CXX_STANDARD 11)

add_executable(QueueTest
        shared/ProducerConsumerQueue.h
        shared/ProducerConsumerQueue_test.cpp)

add_executable(crawler-parser-Test
        main.cpp
        shared/ProducerConsumerQueue.h
        shared/ThreadClass.h
        shared/url.h
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
        crawler/HouseKeeper.cpp
        indexer/Indexer.cpp)


add_executable(crawler-parser-indexer-Test
        main.cpp
        shared/ProducerConsumerQueue.h
        shared/ThreadClass.h
        shared/url.h
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
        shared/ThreadClass.h
        crawler/UrlFrontier.cpp
        shared/url.h
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
        shared/ThreadClass.h
        shared/url.h
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
        shared/url.h
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
        crawler/Readers/HttpsReader.cpp)

add_executable(SharedTableTest
        shared/SharedHashMapTest.cpp )

add_executable(URLTEST shared/url.h shared/urlTest.cpp)

add_executable(search-engine search.cpp query/Query.cpp)

add_executable(ISRWord-tests
        util/util.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/tests/ISRWordTests.cpp
        constraintSolver/ISREndDoc.cpp
        util/stringProcessing.cpp
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
        util/stringProcessing.cpp
        util/Stemmer.cpp )

add_executable(ISRAnd-tests
        constraintSolver/tests/ISRAndTests.cpp
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
        util/Stemmer.cpp )


add_executable(DataStructures-Vector-tests
        DataStructures/Vector/Vector.h
        DataStructures/Vector/VectorTests.cpp)

add_executable(DataStructures-HashTable-tests
        DataStructures/HashTable/HashTable.h
        DataStructures/HashTable/HashTableTests.cpp)

add_executable(DataStructures-DiskHashTable-tests
        DataStructures/DiskHashTable/DiskHashTable.h
        DataStructures/DiskHashTable/DiskHashTableTests.cpp)

add_executable(Indexer-twitter-tests
        DataStructures/DiskHashTable/MMDiskHashTable.h
        indexer/Indexer.cpp
        indexer/json.hpp
        util/stringProcessing.cpp
        util/Stemmer.cpp
        util/util.cpp
        indexer/IndexerTwitterTests.cpp)

add_executable(query-Ranker-tests
        query/Ranker/tests/RankerTest.cpp
        query/Ranker/Ranker.h
        query/Ranker/Scorer.h
        query/Ranker/Site.h
        query/Ranker/Ranker.cpp
        query/Ranker/Scorer.cpp
        query/Ranker/Site.cpp
        util/util.cpp
        constraintSolver/ISRWord.cpp
        constraintSolver/ISREndDoc.cpp
        util/stringProcessing.cpp
        util/Stemmer.cpp )

find_package(OpenSSL REQUIRED)

target_link_libraries(ParserTest OpenSSL::SSL)

target_link_libraries(isolated-integration OpenSSL::SSL pthread)
target_link_libraries(url-frontier-test OpenSSL::SSL pthread)

target_link_libraries(crawler-parser-Test OpenSSL::SSL pthread)
target_link_libraries(crawler-parser-indexer-Test OpenSSL::SSL pthread)

target_link_libraries(QueueTest pthread)

