//
// Created by Zane Dunnings on 4/14/18.
//

#ifndef EECS398_SEARCH_SVM_H
#define EECS398_SEARCH_SVM_H

#include <vector>
#include <string>
#include "../util/util.h"
#include <queue>
#include "../ranker/Site.h"



struct doc
	{

	doc()
			:score(0.0), url(""), id(0){};
	vector< double > featureVec;
	double score;
	string url;
	int id;
	};



using namespace std;



class SVM
	{
public:
/***
 * Custom Comparator for the priority queue that keeps the websites in their correct order.
 */
	class Comp
		{

	public:

		bool operator()(doc L, doc R)
			{
			return L.score < R.score;
			}
		};
	SVM();

	~SVM ( );

	/***
	 * Trains the classifier on some training file
	 */
	void Train( );

	/***
	 * Generate Ranking matrix given a training file, assign to member RankingMatrix
	 */
	void generateRankingMatrix( int trainingFile );

	/***
	 * Gets the kendall Tau score for some grouping of ranked documents, essentially scores how good some ranking is based
	 * on the Ranking Matrix
	 * @return double
	 */
	double getKendallTauScore(  vector< vector < bool > > );
	/***
	 * Ranking matrix, value of 1 means i is ranked above j given some ranking method R;
	 * This is the reference method for this class, that all other matrices will compare to
	 */
	vector< vector <  bool > > RankingMatrix;

	void scoreDocs( vector < double > weights);


	void printWeights( vector< double> weights );
private:


	string getRankedSitesFileName( int number );

	string getUnrankedSitesFileName( int number );

	vector< vector < bool > > generateRankingFromList(  priority_queue< doc, vector<doc>, Comp > SortedList );

	const int NUMBER_OF_FEATURES = 3;

	const int NUMBER_OF_DOCS = 10;

	unordered_map < string , int > urlToIDMap;

	vector <  doc * > corpus;
	};


#endif //EECS398_SEARCH_SVM_H
