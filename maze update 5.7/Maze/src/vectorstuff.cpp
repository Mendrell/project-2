#include "vectorstuff.h"
#include <templateFunctions.h>
#include <templateFunctions.cpp>

const int GSPACE = 0;
const int GWALL = 1;

vectorstuff::vectorstuff()
{
    //ctor
}

vectorstuff::~vectorstuff()
{
    //dtor
}

void vectorstuff::basicDijkstra(vector < vector < int > > inpGraph, graphCoord startPos, vector <graphCoord> endPos, queue < graphCoord > &retSolution)
{
    templateFunctions tFuncs;

	priority_queue < priorityCoordObject > frontier;
	queue <graphCoord> explored;
	vector <graphCoord> tempExpansion;
	priorityCoordObject tempPriorObj;
	priorityCoordObject topPriorObj;
	bool found;
	found = false;

	topPriorObj.path.push(startPos);
	//topPriorObj.priority = -minTaxiDistGC(startPos, endPos);
	topPriorObj.priority = 0;
	frontier.push(topPriorObj);

	while (!frontier.empty() && !found)
	{
		if (tFuncs.searchVector(endPos, frontier.top().path.back()) != -1)
		{
			found = true;
			retSolution = frontier.top().path;
			frontier.pop();
		}
		else
		{
			//Side Note: take average of x and y for basic a star of 8 direction
				//if they do and don't reach a wall add that node to main
					//add all other nodes to unexplored queue
						//the unexplored queue needs to be sorted by closet to start position
			topPriorObj = frontier.top();
			frontier.pop();
			explored.push(topPriorObj.path.back());
			//just checks if in bounds
			expandGraphLoc(inpGraph, topPriorObj.path.back(), tempExpansion);
			for (int i = 0; i < tempExpansion.size(); i++)
			{
				//check if not wall
				if (tFuncs.getMapElement(inpGraph, tempExpansion.at(i).x, tempExpansion.at(i).y) != GWALL)
				{
					tempPriorObj = topPriorObj;
					tempPriorObj.path.push(tempExpansion.at(i));
					//check if in frontier or explored
					if (!tFuncs.isInQueue(explored, tempExpansion.at(i)) && !tFuncs.isInPriorityQueue(frontier, tempPriorObj))
					{
						//tempPriorObj.priority = -minTaxiDistGC(tempExpansion.at(i), endPos);
						tempPriorObj.priority--;
						frontier.push(tempPriorObj);

					}
				}
			}
		}
	}
}

int vectorstuff::taxiDistanceGraphCoord(graphCoord inpStartPos, graphCoord inpEndPos)
{
	return (abs(inpEndPos.x - inpStartPos.x) + abs(inpEndPos.y - inpStartPos.y));
}

int vectorstuff::minTaxiDistGC(graphCoord inpStartPos, vector < graphCoord > inpEndPos)
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

bool vectorstuff::isInPQGC(priority_queue <priorityCoordObject> inpQueue, graphCoord inpElement)
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

//only checks if the positions are in the graph borders
//checks the surrounding locations of grid point and sends them back in vector
void vectorstuff::expandGraphLoc(vector < vector < int > > inpGraph, graphCoord inpCoord, vector < graphCoord > &retExpansion)
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

//parses a char to an int
int vectorstuff::characterParser(char inpChar)
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
		case 'p':
			retInt = 2;
			break;
		case 'e':
			retInt = 3;
			break;
		case 'c':
			retInt = 4;
			break;
		case 'a':
			retInt = 5;
			break;
		default:
			cout << "error parsing" << endl;
			break;
	}

	return retInt;
}

char vectorstuff::intParser(int inpInt)
{
	char retChar;
	retChar = 0;
	switch(inpInt)
	{
		case 0:
			retChar = '.';
			break;
		case 1:
			retChar = '#';
			break;
		case 2:
			retChar = 'p';
			break;
		case 3:
			retChar = 'e';
			break;
		case 4:
			retChar = 'c';
			break;
		case 5:
			retChar = 'a';
			break;
		default:
			cout << "error parsing" << endl;
			break;
	}

	return retChar;
}

