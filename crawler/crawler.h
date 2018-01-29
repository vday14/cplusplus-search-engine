

/*
 *
 * Must provide
 Robustness:
The Web contains servers that create spider traps, which are generators of web pages that mislead crawlers into getting stuck fetching an infinite number of pages in a particular domain. Crawlers must be designed to be resilient to such traps. Not all such traps are malicious; some are the inadvertent side-effect of faulty website development.
Politeness:
Web servers have both implicit and explicit policies regulating the rate at which a crawler can visit them. These politeness policies must be respected.

 */


class Crawler {

    //robots.txt cache




public:










};


//spiders : threads doing work of fetching urls
//houseKeeper : This thread is generally quiescent except that it wakes up once every few seconds to log crawl progress statistics
// (URLs crawled, frontier size, etc.), decide whether to terminate the crawl, or (once every few hours of crawling) checkpoint the crawl. In checkpointing, a snapshot of the crawler's state (say, the URL frontier) is committed to disk. In the event of a catastrophic crawler failure, the crawl is restarted from the most recent checkpoint.