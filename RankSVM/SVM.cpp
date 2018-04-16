//
// Created by Zane Dunnings on 4/14/18.
//

#include "SVM.h"
#include <cassert>
#include "../util/util.h"
#include <queue>
#include "../ranker/Site.h"

using namespace std;




/***
	 * Generate Ranking matrix given a training file, assign to member RankingMatrix
	 */
void SVM::generateRankingMatrix( int trainingFile )
	{
	//TODO: change to memory mapped

	string unrankedFileName = getUnrankedSitesFileName( trainingFile );

	FILE * filePtr = fopen( unrankedFileName.c_str(), "r");

	if( filePtr != nullptr )
		{

		for( int i = 0; i < NUMBER_OF_DOCS; ++i )
			{
			vector< double> featureVec;

			int id;
			fscanf ( filePtr, "%d", &id );

			for ( int  j = 0; j < NUMBER_OF_FEATURES; ++j )
				{
				int readFeature = 0;
				fscanf (filePtr, "%d", &readFeature);
				featureVec.push_back((double)readFeature/1000.0);

				}

			char url[150];
			string urlString(url);

			doc * currentDoc = new doc();
			currentDoc->url = urlString;
			currentDoc->featureVec = featureVec;
			currentDoc->id = id;
			fscanf (filePtr, "%s", url);

			corpus.push_back(currentDoc);

			urlToIDMap[urlString] = i;

			}
		}

//	if(filePtr != nullptr)
//		{
//		vector< double> featureVec;
//		int id;
//		fscanf (filePtr, "%d" , &id );
//
//		for( int i = 0; i < SVM::NUMBER_OF_FEATURES + 2; ++ i)
//			{
//			int readFeature = 0;
//			fscanf ( filePtr, "%d", &readFeature );
//			featureVec.push_back((double)readFeature/1000.0);
//			}
//
//		char url[ 80 ];
//		fscanf (filePtr, "%s", url );
//
//		string urlString(url);
//
//
//		doc *currentDoc = new doc();
//		currentDoc->url = urlString;
//		currentDoc->featureVec = featureVec;
//		currentDoc->id = id;
//
//		corpus.push_back( currentDoc );

	//	}

	fclose ( filePtr );

	string rankedFileName = getRankedSitesFileName( trainingFile );

	filePtr = fopen( rankedFileName.c_str( ) , "r");
	//Vector contains the sorted IDs


	vector< int > sortedID;

	if(filePtr != nullptr)
		{
		for( int i = 0; i < 10; ++i )
			{
			int id;
			fscanf ( filePtr, "%d", &id );
			sortedID.push_back ( id );
			}
		}

	//number of documents that have been hand sorted
	assert( sortedID.size( ) == 10);

	for( int i = 0 ; i < 10 ; ++i )
		{

		int currentID = sortedID[ i ];
		for( int j = 0; j < 10 ; ++ j)
			{
			int testID = sortedID[ j ];
			if( j >= i)
				{
				RankingMatrix[ testID ][ currentID ] = false;
				}
			else
				{
				RankingMatrix[ testID ][ currentID ] = true;
				}
			}
		}

	fclose(filePtr);
	}

string SVM::getUnrankedSitesFileName( int number )
	{
	string path = util::GetCurrentWorkingDir( );

	return path + "/RankSVM/train/unrankedSites" + to_string( number ) + ".txt";
	}

string SVM::getRankedSitesFileName( int number )
	{
	string path = util::GetCurrentWorkingDir( );

	return path + "/RankSVM/train/rankedSites" + to_string ( number ) + ".txt";
	}

SVM::SVM()
	{

	RankingMatrix.resize( 10 );
	for(int i = 0; i < 10; ++i )
		{
		RankingMatrix[ i ].resize( 10 );
		}
	}

SVM::~SVM()
	{
//	for( auto i = 0; i < corpus.size(); ++i)
//		{
//		delete corpus[ i ];
//		}
	}

double SVM::getKendallTauScore(  vector< vector < bool > >  newRankVector)
	{
	//concordant pairs
	double P = 0.0;
	//inversion pairs
	double Q = 0.0;
	for( int i = 0; i < NUMBER_OF_DOCS; ++i )
		{
		for( int j = 0; j  <NUMBER_OF_DOCS; ++j)
			{
			bool truth = RankingMatrix[j][i];
			bool test = newRankVector[j][i];
			if( truth == test)
				++P;
			else
				++Q;
			}
		}

	return - ( 2 * Q ) / ( P + Q );
	}

/***
 * Generates a binary ranking matrix based on an orderd priority queue
 */
vector< vector < bool > > SVM::generateRankingFromList(  priority_queue< doc, vector<doc>, Comp > SortedList )
	{

	vector < int > sortedVec;

	vector< vector < bool > > newRankMatrix;

	newRankMatrix.resize( NUMBER_OF_DOCS );
	for( int i = 0 ; i < NUMBER_OF_DOCS ; ++i )
		{
		newRankMatrix[ i ].resize( NUMBER_OF_DOCS );
		}

	while( SortedList.empty() == false )
		{
		sortedVec.push_back( urlToIDMap[ SortedList.top().url ] );
		SortedList.pop();
		}

	for( int i = 0 ; i < 10 ; ++i )
		{

		int currentID = sortedVec[ i ];
		for( int j = 0; j < 10 ; ++ j)
			{
			int testID = sortedVec[ j ];
			if( j >= i)
				{
				newRankMatrix[ testID ][ currentID ] = false;
				}
			else
				{
				newRankMatrix[ testID ][ currentID ] = true;
				}
			}
		}

	return newRankMatrix;
	}

/***
	 * Trains the classifier on some training file
	 */
void SVM::Train()
	{
	double convergenceVal = 0.1;

	vector< double > weights = {0.0, 0.0, 0.0};

	//get a list of ranked docs
	scoreDocs (weights );
	priority_queue< doc, vector< doc >, Comp > rankedDocs;
	for( int i = 0; i < NUMBER_OF_DOCS; ++i)
		{
		rankedDocs.push( *corpus[i]);
		}

	vector< vector < bool > > testingMatrix = generateRankingFromList ( rankedDocs );
	double prev_score = getKendallTauScore ( testingMatrix );
	cout << "Kendall Tau: " << prev_score;

	//TODO increase
	double alpha = 1;
	for( int i = 0; i < 20; ++ i)
		{

		double min_error = 0;
		int min_error_feature = 0;
		vector<double> testWeights = weights;
		double bestScore = 0;

		for( int j = 0; j < NUMBER_OF_FEATURES; ++j)
			{
			testWeights = weights;
			testWeights[j]+= alpha;
			scoreDocs (testWeights);
			for( int i = 0; i < NUMBER_OF_DOCS; ++i)
				{
				rankedDocs.push( *corpus[i]);
				}
			testingMatrix = generateRankingFromList ( rankedDocs );
			double testScore = getKendallTauScore (testingMatrix);
			double delta = testScore - prev_score;
			cout << "\ndelta: "<<delta<<endl;
			if (delta > min_error && delta > -0.99999)
				{
				min_error = delta;
				min_error_feature = j;
				bestScore = testScore;
				}
			}
		prev_score = bestScore;

		weights[min_error_feature] +=alpha;
		scoreDocs (weights);
		for( int i = 0; i < NUMBER_OF_DOCS; ++i)
			{
			rankedDocs.pop();
			}
		}

	printWeights(weights);

	}


/***
 * Rescores all of the documents given a vector of weights
 * @param weights
 */
void SVM::scoreDocs( vector< double > weights )
	{
	for( int i = 0; i < NUMBER_OF_DOCS; ++i )
		{
		double score = 0.0;
		for( int j = 0; j < NUMBER_OF_FEATURES; ++ j)
			{
			score += weights[j] * corpus[i]->featureVec[j];
			}
		corpus[i]->score = score;
		}
	}

void SVM::printWeights( vector< double> weights )
	{
	for( int i=0; i < NUMBER_OF_FEATURES; ++i)
		{
		cout << "feature"<<i<<": "<<weights[i]<<"\n";
		}
	}