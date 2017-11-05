#include "fileManager.h"



fileManager::fileManager()
{
	CLogger::GetLogger()->Log("file Manager Created");
}
/*The c'tor gets the  full path  to the file as a string  and have the ability 
to read the file ,split to anagram and create the matrixes*/
fileManager::fileManager(string fileNamePATH ,string stopWordFilePATH)
{
	
	CLogger::GetLogger()->Log("Open input file for reading");
	inputFile.open(fileNamePATH);
	if (! inputFile.is_open())
	{
		CLogger::GetLogger()->Log("Cannot open input file");
		exit(1);
	}

	/*read stopword list and save them in a List*/
	if (! stopWordFilePATH.empty())
	{
		stopWordFile.open(stopWordFilePATH);
		if (!stopWordFile.is_open())
		{
			CLogger::GetLogger()->Log("Error While trying ot read stopWords list");
			exit(1);
		}

		string temp;
		while (!stopWordFile.eof())
		{
			stopWordFile >> temp;
			stopWordList.push_back(temp);
		}

		CLogger::GetLogger()->Log("Stop words list were created succesfully");
	}

}


void fileManager::readFile(int segSize)
{
	string reader , block;
	int currentBlockSize = segSize;
	while (!inputFile.eof())
	{
		inputFile >> reader;
		int size = reader.size();
		if (currentBlockSize - size > 0)
		{
			block += reader;
			currentBlockSize -= size;
		}
		else {
			/*insert  according to free size left */
			block += reader.substr(0, size -currentBlockSize  );
			textBlocks.push_back(block);
			block.erase();
			block += reader.substr(size - currentBlockSize, size);
			currentBlockSize = segSize - block.size();
		}
	}
}


/*TODO Continue*/
void fileManager::createAnagramMatrix(int NgramSize)
{
	Ngrams.empty();
	int segSeize ,j,i = 0;
	string Curr_Block,tempNGram;
	while (!textBlocks[i].empty())
	{
		Curr_Block = textBlocks[i];
		segSeize=Curr_Block.size();
		j = 0;
		while (Curr_Block[j]  &&  Curr_Block[j+NgramSize])
		{

			tempNGram = Curr_Block.substr(j, j + NgramSize);
			Ngrams[i].push_back(tempNGram);
			j += NgramSize;
		}

	}
}

fileManager::~fileManager()
{
	CLogger::GetLogger()->Log("File Manager D'tor");
}
