#pragma once
#include <iostream>
#include "string.h"
#include <fstream>
#include <vector>
#include "Logger.h"

using namespace std;

class fileManager
{
	
public:
	fileManager(string fileNameInput,string stopWordFilePATH);
	void readFile(int segSize);
	fileManager::fileManager();
	~fileManager();
	void fileManager::createAnagramMatrix(int NgramSize);
	

private:
	ifstream inputFile;
	ifstream stopWordFile;
	std::vector<string> stopWordList;
	std::vector <string> textBlocks;
	std::vector <vector<string>> Ngrams;
};

