cmake_minimum_required(VERSION 3.9)
project(eecs398_search)

set(CMAKE_CXX_STANDARD 11)

add_executable(crawler-parser-test
        main.cpp
        shared/ProducerConsumerQueue.h
        shared/ThreadClass.h
        shared/url.h
        crawler/crawler.cpp
        crawler/SocketReader.cpp
        crawler/StreamReader.h
        crawler/spider.cpp
        util/util.cpp
        crawler/LocalReader.h
        shared/Document.cpp
        parser/Parser.cpp
        util/stringProcessing.cpp)


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

add_executable(ParserTestE2E
        parser/Parser.cpp
        shared/Document.cpp
        shared/url.h
        util/util.cpp
        util/Tokenizer.cpp
        shared/ProducerConsumerQueue.h
        util/stringProcessing.cpp
        util/Stemmer.cpp
        parser/tests/parserTest.cpp)


add_executable(URLTEST shared/url.h shared/urlTest.cpp)

add_executable(search-engine search.cpp query/Query.cpp)

find_package(OpenSSL REQUIRED)

target_link_libraries(crawler-parser-test OpenSSL::SSL pthread)
