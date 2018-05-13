#include <iostream>
#include <queue>
//#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>

using namespace std;

const char EMPTYCHARSYMBOL = '_';
const char WALLCHARSYMBOL = '#';
const char ENEMYCHARSYMBOL = 'e';
const char PLAYERCHARSYMBOL = 'p';
const char CHESTCHARSYMBOL = 'c';
const char AMMOCHARSYMBOL = 'a';

const int EMPTYINTSYMBOL = 0;
const int WALLINTSYMBOL = 1;
const int ENEMYINTSYMBOL = 2;
const int PLAYERINTSYMBOL = 3;
const int CHESTINTSYMBOL = 4;
const int AMMOINTSYMBOL = 5;

const string EMPTYSTRSYMBOL = "empty";
const string WALLSTRSYMBOL = "wall";
const string ENEMYSTRSYMBOL = "enemy";
const string PLAYERSTRSYMBOL = "player";
const string CHESTSTRSYMBOL = "chest";
const string AMMOSTRSYMBOL = "arrow";

template<class T>
int searchVector(std::vector <T> vecToSearch, T varToFind)
{
	bool done;
	int count00;
	int retIndex;
	
	retIndex = -1;
	
	done = false;
	count00 = 0;
	
	while (!done && count00 < vecToSearch.size())
	{
		if (vecToSearch.at(count00) == varToFind)
		{
			done = true;
			retIndex = count00;
		}
		count00++;
	}
	
	return retIndex;
}

template <class T>
void display1DVec(vector <T> inpVector, string inpDelim = "")
{
	for (int i = 0; i < inpVector.size(); i++)
	{
		cout << inpVector.at(i) << inpDelim;
	}
	cout << endl;
}

template <class T>
void display2DVec(vector < vector <T> > inpVector, string inpDelim = "")
{
	for (int i = 0; i < inpVector.size(); i++)
	{
		display1DVec(inpVector.at(i), inpDelim);
	}
}

template <class T>
T getMapElement(vector < vector <T> > inpVector, int inpX, int inpY)
{
	T retElement;
	if (inpY < inpVector.size() && inpY >= 0)
	{
		if (inpX < inpVector.at(inpY).size() && inpX >= 0)
		{
			retElement = inpVector.at(inpY).at(inpX);
		}
		else
			cout << "getMapElement error" << endl;
	}
	else
			cout << "getMapElement error" << endl;
	return retElement;
}


void fileToGraph(ifstream &inpFile, vector < vector < int > > &retMap);
void intGraphToStrFileList(vector < vector < int > > inpMap, string inpOutFileName);
int characterParser(char inpChar);
void fileToFileList(ifstream &inpFile, string outFileName);
char intParser(int inpInt);
string intToStrParser(int inpInt);

//So this is by each object type
//I.E. for enemies, player, wall
void realCoordToGraph();

int nodesExpanded;

//This reads a graph file and stores it in a 2d vector
//Then calculates the shortest path from start and end locations
	//start and end is x y x y format
int main(int argc, char *argv[])
{
	ifstream mainReadFile;
	vector < vector < int > > mainGraph;
	string fileName;
	string outFileName;
	
	if (argc > 1)
		fileName = argv[1];
	else
		fileName = "map01.txt";
	
	if (argc > 2)
		outFileName = argv[2];
	else
		outFileName = "testOutMap01.txt";
	
	//cout << fileName << endl;
	
	mainReadFile.open(fileName.c_str());
	//cout << fileName << endl;
	fileToGraph(mainReadFile, mainGraph);
	//cout << fileName << endl;
	mainReadFile.close();
	
	display2DVec(mainGraph);
	
	mainReadFile.open(fileName.c_str());
	fileToFileList(mainReadFile, outFileName);
	mainReadFile.close();
	
	return 0;
}

//Y is first .at() X is second .at()
//takes file of characters and converts it to 2d vec of ints
void fileToGraph(ifstream &inpFile, vector < vector < int > > &retMap)
{
	string graphLine;
	vector < vector < int > > tempMap;
	
	//cout << "here00" << endl;
	
	int count00 = 0;
	while (!inpFile.eof())
	{
		getline(inpFile, graphLine);

		//handle carriage returns
		if(graphLine.at(graphLine.length() - 1) == '\r' )
			graphLine = graphLine.substr(0, graphLine.length() - 1);
		
		//push an empty vector in
		tempMap.push_back(vector <int> ());
		
		for (int i = 0; i < graphLine.length(); i++)
		{
			//parse and push characters
			tempMap.back().push_back(characterParser(graphLine.at(i)));
		}
		
		count00++;
	}
	
	//cout << "here01" << endl;
	retMap = tempMap;
}

void intGraphToStrFileList(vector < vector < int > > inpMap, string inpOutFileName)
{
	string graphLine;
	vector < vector < int > > tempMap;
	tempMap = inpMap;
	int lengthY;
	int lengthX;
	
	//get grid lengths
	lengthX = 0;
	lengthY = tempMap.size();
	for (int i = 0; i < tempMap.size(); i++)
	{
		if (lengthX < tempMap.at(i).size())
		{
			lengthX = tempMap.at(i).size();
		}
	}
	
	if (lengthX < lengthY)
		lengthX = lengthY;
	
	//parse graph into file
	ofstream outFile;
	outFile.open(inpOutFileName.c_str());
	
	outFile << "grid" << " ";
	outFile << lengthX << " ";
	outFile << lengthY;
	
	for (int i = 0; i < tempMap.size(); i++)
	{
		for (int j = 0; j < tempMap.at(i).size(); j++)
		{
			string tempStr = intToStrParser(tempMap.at(i).at(j));
			if (tempStr != EMPTYSTRSYMBOL)
			{			
				outFile << "\n";
				outFile << intToStrParser(tempMap.at(i).at(j)) << " ";
				outFile << j << " ";
				outFile << i;
			}
		}
	}
	outFile.close();
}

void fileToFileList(ifstream &inpFile, string inpOutFileName)
{
	string graphLine;
	vector < vector < int > > tempMap;
	int lengthY;
	int lengthX;
	
	int count00 = 0;
	fileToGraph(inpFile, tempMap);
	intGraphToStrFileList(tempMap, inpOutFileName);
}

//parses a char to an int
int characterParser(char inpValue)
{
	int retValue;
	retValue = 0;
	switch(inpValue)
	{
		case EMPTYCHARSYMBOL:
			retValue = EMPTYINTSYMBOL;
			break;
		case WALLCHARSYMBOL:
			retValue = WALLINTSYMBOL;
			break;
		case PLAYERCHARSYMBOL:
			retValue = PLAYERINTSYMBOL;
			break;
		case ENEMYCHARSYMBOL:
			retValue = ENEMYINTSYMBOL;
			break;
		case CHESTCHARSYMBOL:
			retValue = CHESTINTSYMBOL;
			break;
		case AMMOCHARSYMBOL:
			retValue = AMMOINTSYMBOL;
			break;
		default:
			cout << "error parsing" << endl;
			break;
	}
	
	return retValue;

}

char intParser(int inpInt)
{	
	char retValue;
	retValue = 0;
	switch(inpInt)
	{
		case EMPTYINTSYMBOL:
			retValue = EMPTYCHARSYMBOL;
			break;
		case WALLINTSYMBOL:
			retValue = WALLCHARSYMBOL;
			break;
		case PLAYERINTSYMBOL:
			retValue = PLAYERCHARSYMBOL;
			break;
		case ENEMYINTSYMBOL:
			retValue = ENEMYCHARSYMBOL;
			break;
		case CHESTINTSYMBOL:
			retValue = CHESTCHARSYMBOL;
			break;
		case AMMOINTSYMBOL:
			retValue = AMMOCHARSYMBOL;
			break;
		default:
			cout << "error parsing" << endl;
			break;
	}
	
	return retValue;
}

string intToStrParser(int inpInt)
{
	string retValue;
	retValue = "";
	switch(inpInt)
	{
		case EMPTYINTSYMBOL:
			retValue = EMPTYSTRSYMBOL;
			break;
		case WALLINTSYMBOL:
			retValue = WALLSTRSYMBOL;
			break;
		case PLAYERINTSYMBOL:
			retValue = PLAYERSTRSYMBOL;
			break;
		case ENEMYINTSYMBOL:
			retValue = ENEMYSTRSYMBOL;
			break;
		case CHESTINTSYMBOL:
			retValue = CHESTSTRSYMBOL;
			break;
		case AMMOINTSYMBOL:
			retValue = AMMOSTRSYMBOL;
			break;
		default:
			cout << "error parsing" << endl;
			break;
	}
	
	return retValue;
}