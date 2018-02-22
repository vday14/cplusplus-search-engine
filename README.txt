C++lue Search Engine ReadME:::



Milestone I Status::

---CRAWLER---
The index builder currently starts in the main.cpp file. It accepts a series of inputs variables via command line at the start to set certain configuration sets. We currently support the ability to run the crawler locally (opening text file) or over the web (HTTP/HTTPS requests) and with an input number of crawling spider threads. Main.cpp reads in list of seeds urls (depending on mode running) and adds them to the url frontier queue. Then it instantiates a crawler object(crawler.h) which has control of a crawlerstatistic object which keeps important logging information and a collection multiple threads each with running spider (spider.h) classes's. The spider is in constant loop to pull a url off of URL frontier, a shared memory queue (implemented in ProducerConsumerQueue.h) and perform the following operations. Takes the string url and creates a parsed url object (url.h) it checks to see if the url should be crawled based off of stored information in the documentMapTable (docmap.h) as well as looking at the robots.txt( This part is currently a work in progress). If the Url should be crawled, the spider creates a StreamReader object, which is the abstract class with child classes of a localReader and SocketReader and fills the readers buffer. The StreamReader object helps to abstract the way that the buffer is filled when passing to the Parser. For now, the spider fills the buffer with the entire file/web page and then writes it to disk (the file name is a hash of the  complete url). In the future, we plan to pass the buffer or the socket to the parser to improve efficiency.



---PARSER---



---INDEXER---


