cmake_minimum_required(VERSION 3.9)
project(eecs398_search)

set(CMAKE_CXX_STANDARD 11)

add_executable(search
        main.cpp
        shared/ProducerConsumerQueue.cpp
        shared/ProducerConsumerQueue.h
         parser/Parser.h
        util/Tokenizer.h
        util/stringProcessing.h
        util/Stemmer.h)



add_executable(crawl
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
        util/stringProcessing.h
        util/Stemmer.h
        util/tests/stringProcessingTest.cpp)

add_executable(TokenizerTest
        util/Tokenizer.h
        util/tests/tokenizerTest.cpp)

add_executable(StemmerTest
        util/Stemmer.h
        util/tests/stemmerTest.cpp)

add_executable(ParserEndToEndTest
        parser/Parser.h
        shared/Document.h
        shared/url.h
        parser/tests/parserTest.cpp)


add_executable(URLTEST shared/url.h shared/urlTest.cpp)


find_package(OpenSSL REQUIRED)

target_link_libraries(crawl OpenSSL::SSL pthread)

