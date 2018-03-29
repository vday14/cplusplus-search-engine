//
// Created by Jake Close on 2/1/18.
//
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "HouseKeeper.h"

void HouseKeeper::run(){
	//Sleep(3 minutes)
	//Gather data
	cout << "SAVING STATE OF URL FRONTIER " << endl;
	while(true)
		{
		std::this_thread::sleep_for (std::chrono::seconds(30));

		crawler->urlFrontier->writeDataToDisk();

		}


	}