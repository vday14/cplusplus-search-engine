all:
	g++ -std=c++11 main.cpp crawler/crawler.cpp crawler/spider.cpp -o crawler.exe -lpthread