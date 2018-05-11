#include <iostream>
#include <queue>
//#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

struct graphCoord
{
	int x;
	int y;
	
	bool operator == (const graphCoord a) const
	{
		return (a.y == y && a.x == x);
	}
	
	graphCoord operator + (const graphCoord a) const
	{
		graphCoord retCoord;
		retCoord = {x + a.x, y + a.y};
		return retCoord;
	}
	
	graphCoord operator - (const graphCoord a) const
	{
		graphCoord retCoord;
		retCoord = {x - a.x, y - a.y};
		return retCoord;
	}
	
	friend ostream& operator<<(ostream &out, graphCoord gC)
	{	
		out << gC.x;
		out << ':';
		out << gC.y;

		return out; //return a reference to the output stream
	}
};



struct priorityCoordObject
{
	queue < graphCoord > path;
	int priority;
	
	bool operator < (const priorityCoordObject &a) const
	{
		return (priority < a.priority);
	}	
	bool operator == (const priorityCoordObject &a) const
	{
		return (path.back() == a.path.back());
	}
	friend ostream& operator<<(ostream &out, const priorityCoordObject &a)
	{	
		out << a.priority;
		//out << ':';
		//out << gC.y;

		return out; //return a reference to the output stream
	}
};


struct graphDimensions
{
	int width;
	int height;
};
struct cartCoord
{
	double x;
	double y;
};
struct boxDimensions
{
	double width;
	double height;
};

const int GSPACE = 0;
const int GWALL = 1;

template <class T>
bool isInQueue(queue <T> inpQueue, T inpElement)
{
	bool found;
	
	found = false;
	while (!inpQueue.empty() && !found)
	{
		if (inpQueue.front() == inpElement)
		{
			found = true;
		}
		inpQueue.pop();
	}
	
	return found;
}

template <class T>
bool isInPriorityQueue(priority_queue <T> inpQueue, T inpElement)
{
	bool found;
	
	found = false;
	while (!inpQueue.empty() && !found)
	{
		if (inpQueue.top() == inpElement)
		{
			found = true;
		}
		inpQueue.pop();
	}
	
	return found;
}

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
		/*
		for (int j = 0; j < inpVector.at(i).size(); j++)
		{
			cout << inpVector.at(i).at(j) << " ";
		}
		cout << endl;
		*/
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

template <class T>
void display1DQueue(queue <T> inpQueue, string inpDelim = "")
{
	while (!inpQueue.empty())
	{	
		cout << inpQueue.front() << inpDelim;
		inpQueue.pop();
	}
	cout << endl;
}

template <class T>
void display1DPriorQueue(priority_queue <T> inpQueue, string inpDelim = "")
{
	while (!inpQueue.empty())
	{	
		cout << inpQueue.top() << inpDelim;
		inpQueue.pop();
	}
	cout << endl;
}

void expandGraphLoc(vector < vector < int > > inpGraph, graphCoord inpCoord, vector < graphCoord > &retExpansion);
void breadthFirstSearch(vector < vector < int > > inpGraph, graphCoord startPos, vector <graphCoord> endPos, queue < graphCoord > &retSolution); //djkstra algorithm
void fileToGraph(ifstream &inpFile, vector < vector < int > > &retMap);
int characterParser(char inpChar);
void beeLineSearch(vector < vector < int > > inpGraph, graphCoord startPos, vector <graphCoord> endPos, queue < graphCoord > &retSolution); //basic a star
int taxiDistanceGraphCoord(graphCoord inpStartPos, graphCoord inpEndPos);
int minTaxiDistGC(graphCoord inpStartPos, vector < graphCoord > inpEndPos);
bool isInPQGC(priority_queue <priorityCoordObject> inpQueue, graphCoord inpElement);
cartCoord graphToLowRealCoord(graphCoord inpGraphCoord, graphDimensions inpGraphDim, boxDimensions inpBoxDim);
cartCoord graphToHighRealCoord(graphCoord inpGraphCoord, graphDimensions inpGraphDim, boxDimensions inpBoxDim);

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
	graphCoord startPos, endPos;
	vector <graphCoord> endPositions;
	
	if (argc > 1)
		fileName = argv[1];
	else
		fileName = "map01.txt";
	
	if (argc > 3)
		startPos = {stoi(argv[2]), stoi(argv[3])};
	else
		startPos = {5, 1};
	
	if (argc > 5)
		endPos = {stoi(argv[4]), stoi(argv[5])};
	else
		endPos = {1, 6};
	
	mainReadFile.open(fileName.c_str());
	fileToGraph(mainReadFile, mainGraph);
	mainReadFile.close();
	
	display2DVec(mainGraph);
	
	endPositions.push_back(endPos);
	queue <graphCoord> solutionQueue;
	//breadthFirstSearch(mainGraph, startPos, endPos, solutionQueue);
	breadthFirstSearch(mainGraph, startPos, endPositions, solutionQueue);
	display1DQueue(solutionQueue, " ");
	cout << nodesExpanded << endl;
	
	beeLineSearch(mainGraph, startPos, endPositions, solutionQueue);
	display1DQueue(solutionQueue, " ");
	cout << nodesExpanded << endl;
	
	/*
	priorityCoordObject pCOTemp00;
	priority_queue < priorityCoordObject > pqPCOTemp00;
	priority_queue < int > pQTest00;
	
	pCOTemp00.priority = 0;
	pqPCOTemp00.push(pCOTemp00);
	
	pCOTemp00.priority = 9;
	pqPCOTemp00.push(pCOTemp00);
	
	pCOTemp00.priority = 7;
	pqPCOTemp00.push(pCOTemp00);
	
	pCOTemp00.priority = 3;
	pqPCOTemp00.push(pCOTemp00);
	
	pCOTemp00.priority = -6;
	pqPCOTemp00.push(pCOTemp00);
	
	display1DPriorQueue(pqPCOTemp00, " ");
	*/
	
	
	return 0;
}

//to determine if there is collision on the graph
bool graphCollision(graphCoord inpOrigin, graphCoord inpTarget)
{
	return (inpOrigin == inpTarget);
}

//note: Untested
//IMPORTANT: NOTE: pretty sure this is not needed
//pretty sure we don't need this
	//basically its uses would be taking the data in the double world
		//and placing it on the correct int world (the graph with breadth search)
			//if the double world overlaps with multiple int world spaces
				//then the double would go into each int world space
		//then do graph collision detection on the int world
			//if there is graph collision detected
				//go to the double world and then use this box collision
					//otherwise all objects in the double world would always have to detect for collision with each other
					//this limits it to each graph cell
						//NOTE: this is not implemented as it would require a 3d vector
							//the third dimension would contain what objects are on that graph space
bool boxCollision (cartCoord objectLoc0, boxDimensions objectDim0, cartCoord objectLoc1, boxDimensions objectDim1)
{
	//do box collision calculations
	bool retIsCollision;
	
	cartCoord obj0MinBounds = objectLoc0;
	cartCoord obj0MaxBounds = {objectLoc0.x+objectDim0.width, objectLoc0.y+objectDim0.height};
	cartCoord obj1MinBounds = objectLoc1;
	cartCoord obj1MaxBounds = {objectLoc1.x+objectDim1.width, objectLoc1.y+objectDim1.height};
	
	retIsCollision = true;
	if (obj0MaxBounds.x < obj1MinBounds.x || obj0MinBounds.x > obj1MaxBounds.x)
		retIsCollision = false;
	if (obj0MaxBounds.y < obj1MinBounds.y || obj0MinBounds.y > obj1MaxBounds.y)
		retIsCollision = false;
	
	return retIsCollision;
}

//this takes a graph a starting and ending position and returns the shortest path
//only cardinal directions north south west east
void breadthFirstSearch(vector < vector < int > > inpGraph, graphCoord startPos, vector <graphCoord> endPos, queue < graphCoord > &retSolution)
{
	nodesExpanded = 0;
	queue < queue <graphCoord> > potentialSolutions;
	queue <graphCoord> frontier;
	queue <graphCoord> explored;
	queue <graphCoord> tempSolution;
	vector <graphCoord> tempExpansion;
	bool found;
	found = false;
	
	frontier.push(startPos);
	potentialSolutions.push(frontier);
	
	while (!frontier.empty() && !found)
	{
		//if (frontier.front() == endPos)
		if (searchVector(endPos, frontier.front()) != -1)
		{
			found = true;
			retSolution = potentialSolutions.front();
		}
		else
		{
			//just checks if in bounds
			expandGraphLoc(inpGraph, frontier.front(), tempExpansion);
			nodesExpanded++;
			for (int i = 0; i < tempExpansion.size(); i++)
			{
				//check if not wall
				if (getMapElement(inpGraph, tempExpansion.at(i).x, tempExpansion.at(i).y) != GWALL)
				{
					//check if in frontier or explored
					if (!isInQueue(explored, tempExpansion.at(i)) && !isInQueue(frontier, tempExpansion.at(i)))
					{
						frontier.push(tempExpansion.at(i));
						tempSolution = potentialSolutions.front();
						//tempSolution.push(frontier.front());
						tempSolution.push(tempExpansion.at(i));
						potentialSolutions.push(tempSolution);
					}
				}
			}
			explored.push(frontier.front());
		}
		frontier.pop();
		potentialSolutions.pop();
	}
}


void beeLineSearch(vector < vector < int > > inpGraph, graphCoord startPos, vector <graphCoord> endPos, queue < graphCoord > &retSolution)
{	
	nodesExpanded = 0;
	priority_queue < priorityCoordObject > frontier;
	//queue <graphCoord> frontier;
	queue <graphCoord> explored;
	//queue <graphCoord> tempSolution;
	vector <graphCoord> tempExpansion;
	priorityCoordObject tempPriorObj;
	priorityCoordObject topPriorObj;
	bool found;
	found = false;
	
	
	//frontier.push(startPos);
	//potentialSolutions.push(frontier);
	topPriorObj.path.push(startPos);
	topPriorObj.priority = -minTaxiDistGC(startPos, endPos);
	frontier.push(topPriorObj);
	
	while (!frontier.empty() && !found)
	{	
		if (searchVector(endPos, frontier.top().path.back()) != -1)
		{
			found = true;
			retSolution = frontier.top().path;
			frontier.pop();
		}	
		else
		{
			
			//first go for the beeLine direction since up down left right check if either horizontal or vertical decreases
				//if they do and don't reach a wall add that node to main
					//add all other nodes to unexplored queue
						//the unexplored queue needs to be sorted by closet to end goal
			topPriorObj = frontier.top();
			frontier.pop();
			explored.push(topPriorObj.path.back());
			//just checks if in bounds
			expandGraphLoc(inpGraph, topPriorObj.path.back(), tempExpansion);
			nodesExpanded++;			
			for (int i = 0; i < tempExpansion.size(); i++)
			{
				//check if not wall
				if (getMapElement(inpGraph, tempExpansion.at(i).x, tempExpansion.at(i).y) != GWALL)
				{
					tempPriorObj = topPriorObj;
					tempPriorObj.path.push(tempExpansion.at(i));
					//check if in frontier or explored
					//if (!isInQueue(explored, tempExpansion.at(i)) && !isInPQGC(frontier, tempExpansion.at(i)))
					if (!isInQueue(explored, tempExpansion.at(i)) && !isInPriorityQueue(frontier, tempPriorObj))
					{
						
						//tempPriorObj = topPriorObj;
						//tempPriorObj.path.push(tempExpansion.at(i));
						tempPriorObj.priority = -minTaxiDistGC(tempExpansion.at(i), endPos);
						frontier.push(tempPriorObj);
						
					}
					
					
				}
			}
		}
	}
	
}

int taxiDistanceGraphCoord(graphCoord inpStartPos, graphCoord inpEndPos)
{
	return (abs(inpEndPos.x - inpStartPos.x) + abs(inpEndPos.y - inpStartPos.y));
}

int minTaxiDistGC(graphCoord inpStartPos, vector < graphCoord > inpEndPos)
{
	int minDist = -1;
	if (inpEndPos.size() > 0)
	{
		minDist = taxiDistanceGraphCoord(inpStartPos, inpEndPos.at(0));
		int tempDist;
		for (int i = 1; i < inpEndPos.size(); i++)
		{
			tempDist = taxiDistanceGraphCoord(inpStartPos, inpEndPos.at(i));
			if (tempDist < minDist)
				minDist = tempDist;
		}
	}
	
	return minDist;
}

bool isInPQGC(priority_queue <priorityCoordObject> inpQueue, graphCoord inpElement)
{
	bool found;
	
	found = false;
	while (!inpQueue.empty() && !found)
	{
		if (inpQueue.top().path.back() == inpElement)
		{
			found = true;
		}
		inpQueue.pop();
	}
	
	return found;
}

void mazeGeneration()
{

}

//only checks if the positions are in the graph borders
//checks the surrounding locations of grid point and sends them back in vector
void expandGraphLoc(vector < vector < int > > inpGraph, graphCoord inpCoord, vector < graphCoord > &retExpansion)
{
	vector < graphCoord > tempVec;
	for (int i = inpCoord.y - 1; i <= inpCoord.y + 1; i++)
	{
		for (int j = inpCoord.x - 1; j <= inpCoord.x + 1; j++)
		{
			if (!(i == inpCoord.y && j == inpCoord.x)) //this makes it so it doesn't include itself
			{
			if (i == inpCoord.y || j == inpCoord.x) //this makes it so that it only moves up and down - without out diagonal is valid
			{
				if (i >= 0 && i < inpGraph.size())
				{
					if (j >= 0 && j < inpGraph.at(i).size())
					{
						//cout << "push back" << endl;
						tempVec.push_back({j, i});
					}
				}
			}
			}
		}
	}
	retExpansion = tempVec;
}

//Y is first .at() X is second .at()
//takes file of characters and converts it to 2d vec of ints
void fileToGraph(ifstream &inpFile, vector < vector < int > > &retMap)
{
	string graphLine;
	vector < vector < int > > tempMap;
	
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
	retMap = tempMap;
}

//parses a char to an int
int characterParser(char inpChar)
{
	int retInt;
	retInt = 0;
	switch(inpChar)
	{
		case ' ':
			retInt = 0;
			break;
		case '#':
			retInt = 1;
			break;
		default:
			cout << "error parsing" << endl;
			break;
	}
	
	return retInt;
}

cartCoord graphToLowRealCoord(graphCoord inpGraphCoord, graphDimensions inpGraphDim, boxDimensions inpBoxDim)
{
	cartCoord retCartCoord;
	
	retCartCoord.x = inpBoxDim.width * inpGraphCoord.x / inpGraphDim.width;
	retCartCoord.y = inpBoxDim.height * inpGraphCoord.y / inpGraphDim.height;
	
	return retCartCoord;
}
cartCoord graphToHighRealCoord(graphCoord inpGraphCoord, graphDimensions inpGraphDim, boxDimensions inpBoxDim)
{
	cartCoord retCartCoord;
	
	retCartCoord.x = inpBoxDim.width * (inpGraphCoord.x + 1) / inpGraphDim.width;
	retCartCoord.y = inpBoxDim.height * (inpGraphCoord.y + 1) / inpGraphDim.height;
	
	return retCartCoord;
}

