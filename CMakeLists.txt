cmake_minimum_required(VERSION 3.9)
project(eecs398_search)

set(CMAKE_CXX_STANDARD 11)

add_executable(QueueTest
        shared/ProducerConsumerQueue.h
        shared/ProducerConsumerQueue_test.cpp)

add_executable(crawler-parser-test
        main.cpp
        shared/ProducerConsumerQueue.h
        shared/ThreadClass.h
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

add_executable(crawler-parser-indexer-test
        main.cpp
        shared/ProducerConsumerQueue.h
        shared/ThreadClass.h
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
        parser/tests/parserTest.cpp)

add_executable(SharedTableTest shared/SharedHashMapTest.cpp )

add_executable(URLTEST shared/url.h shared/urlTest.cpp)

add_executable(search-engine search.cpp query/Query.cpp)

add_executable(ISRWord-tests util/util.cpp constraintSolver/ISRWord.cpp constraintSolver/tests/ISRWordTests.cpp )

find_package(OpenSSL REQUIRED)

target_link_libraries(crawler-parser-test OpenSSL::SSL pthread)
target_link_libraries(crawler-parser-indexer-test OpenSSL::SSL pthread)

target_link_libraries(QueueTest pthread)
