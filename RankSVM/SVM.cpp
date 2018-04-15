//
// Created by Zane Dunnings on 4/14/18.
//

#include "SVM.h"
#include <cassert>
#include "../util/util.h"

using namespace std;
/***
	 * Generate Ranking matrix given a training file, assign to member RankingMatrix
	 */
void SVM::generateRankingMatrix( int trainingFile )
	{
	//TODO: change to memory mapped

	string unrankedFileName = getUnrankedSitesFileName( trainingFile );

	FILE * filePtr = fopen( unrankedFileName.c_str(), "r");
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

double SVM::getKendallTauScore(  vector< vector < bool > > & newRankVector)
	{
	//concordant pairs
	int P = 0;
	//inversion pairs
	int Q = 0;
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

	return 1 - ( 2 * Q ) / ( P + Q );
	}
