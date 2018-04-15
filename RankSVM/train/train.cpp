//
// Created by Zane Dunnings on 4/15/18.
//

#include "../SVM.h"
#include <stdio.h>

int main()
	{
	SVM rankSVM;
	FILE * filptr = fopen("/Users/iphananatic/CLionProjects/EECS398/eecs398-search/RankSVM/train/unrankedSites0.txt", "r+");
	rankSVM.generateRankingMatrix ( 0 );
	cout << "Kendall Tau: " << rankSVM.getKendallTauScore( rankSVM.RankingMatrix );
	}
