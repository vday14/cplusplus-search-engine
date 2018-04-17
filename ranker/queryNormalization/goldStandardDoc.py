"""
Uses Google as gold standard to find the "perf" document
in order to normalize proximityMatching more accurately
"""

from __future__ import division
from bs4 import BeautifulSoup
from googlesearch import search
import urllib
from collections import defaultdict
import os
from nltk import ngrams

def crawl( queries ):

    urls = []
    query_dict = {}
    for query in queries:
        # Get the first 5 hits for "query" in Google
        for url in search(query, tld='com', lang='eng', stop=5):
            urls.append(url)
        query_dict[query] = urls
        urls = []
    return query_dict


def scrape( url ):
    html = urllib.urlopen(url).read()
    soup = BeautifulSoup(html, "html.parser")

    # kill all script and style elements
    for script in soup(["script", "style"]):
        script.extract()    # rip it out

    # get text
    text = soup.get_text()

    # break into lines and remove leading and trailing space on each
    lines = (line.strip() for line in text.splitlines())
    # break multi-headlines into a line each
    chunks = (phrase.strip() for line in lines for phrase in line.split("  "))
    # drop blank lines
    text = '\n'.join(chunk for chunk in chunks if chunk)

    # print(text)
    return text


def output_to_file(query_dict):

    for query in query_dict:
        for counter, url in enumerate(query_dict[query]):
            html = scrape(url)
            filename = ''.join(list(query)) + str(counter) + '.txt'
            file = open(filename, 'w')
            html = html.encode('utf8')
            html = html.lower()
            file.write(html)
            file.close()

def count_query_freq( ):
    counts = {}
    n = 0
    query = ""
    cwd = os.getcwd()
    directory = cwd + "/ranker/queryNormalization/html"

    for filename in os.listdir(directory):
        with open(directory + "/" + filename, 'r') as my_file:
            text = my_file.read()
            query = (filename[:-5]).lower()
            n = text.count( query )
            if query in counts:
                counts[query] += n
            else:
                counts[query] = n


    return counts

def num_n_grams():
    ngrams_dict = defaultdict(int)
    num_of_grams = 0
    query = ""
    cwd = os.getcwd()
    directory = cwd + "/ranker/queryNormalization/html"

    for filename in os.listdir(directory):
        with open(directory + "/" + filename, 'r') as my_file:
            text = my_file.read()
            query = (filename[:-5]).lower()
            grams = ngrams(text.split(), len(query.split()))
            for gram in grams:
                num_of_grams += 1
            ngrams_dict[query] += num_of_grams
    return ngrams_dict

# run if main file
if __name__ == "__main__":

    queries = ['Michigan Wolverines',
               'khloe kardashian',
               'president donald trump',
               'banana cream pie',
               'university of michigan',
               'machine learning',
               'black panther',
               'electric car',
               'myrtle beach'
               ]
    # query_dict = crawl(queries)
    # output_to_file(query_dict)
    counts = count_query_freq( )
    ngrams_dict = num_n_grams()

    print counts
    print ngrams_dict
    avrg = 0
    for q in counts:

        avrg += counts[q] / ngrams_dict[q]

    print "Average percentage of exact phrases: " + str ( avrg / len(queries) )






