//
// Created by Zane Dunnings on 4/14/18.
//

#ifndef EECS398_SEARCH_SVM_H
#define EECS398_SEARCH_SVM_H

#include <vector>
#include <string>
#include "../util/util.h"

using namespace std;

struct doc
	{
	vector< double > featureVec;
	string url;
	int id;
	};

class SVM
	{
public:

	SVM();

	~SVM ( );

	/***
	 * Trains the classifier on some training file
	 */
	void Train( string trainingFile );

	/***
	 * Generate Ranking matrix given a training file, assign to member RankingMatrix
	 */
	void generateRankingMatrix( int trainingFile );

	/***
	 * Gets the kendall Tau score for some grouping of ranked documents, essentially scores how good some ranking is based
	 * on the Ranking Matrix
	 * @return double
	 */
	double getKendallTauScore(  vector< vector < bool > > &);
	/***
	 * Ranking matrix, value of 1 means i is ranked above j given some ranking method R;
	 * This is the reference method for this class, that all other matrices will compare to
	 */
	vector< vector <  bool > > RankingMatrix;

private:


	string getRankedSitesFileName( int number );

	string getUnrankedSitesFileName( int number );


	const int NUMBER_OF_FEATURES = 3;

	const int NUMBER_OF_DOCS = 10;

	vector < doc *> corpus;
	};


#endif //EECS398_SEARCH_SVM_H
