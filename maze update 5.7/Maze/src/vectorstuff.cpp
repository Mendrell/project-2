#include "vectorstuff.h"
#include <templateFunctions.h>
#include <templateFunctions.cpp>

const int GSPACE = 0;
const int GWALL = 1;
const int GPLAYER = 2;
const int GENEMY = 3;
const int GCHEST = 4;
const int GAMMO = 5;

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
			retInt = GSPACE;
			break;
		case '#':
			retInt = GWALL;
			break;
		case 'P':
			retInt = GPLAYER;
			break;
		case 'E':
			retInt = GENEMY;
			break;
		case 'C':
			retInt = GCHEST;
			break;
		case 'A':
			retInt = GAMMO;
			break;
		default:
			//cout << "error parsing" << endl;
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
		case GSPACE:
			retChar = '_';
			break;
		case GWALL:
			retChar = '#';
			break;
		case GPLAYER:
			retChar = 'P';
			break;
		case GENEMY:
			retChar = 'E';
			break;
		case GCHEST:
			retChar = 'C';
			break;
		case GAMMO:
			retChar = 'A';
			break;
		default:
			//cout << "error parsing" << endl;
			break;
	}

	return retChar;
}

void vectorstuff::pathFinding(GridLoc startPos, GridLoc endPos, queue<GridLoc>& retSolution)
{
    vector < vector < int > > mainIntMap;
    graphCoord tempStartPos;
    graphCoord tempEndPos;
    vector < graphCoord > tempEndPoss;
    queue < graphCoord > tempRetSolution;
    queue < GridLoc > tempSolution;

    tempStartPos = convertGLtoGC(startPos);
    tempEndPos = convertGLtoGC(endPos);
    tempEndPoss.push_back(tempEndPos);

    convertUnitMapToIntMap(mastervec, mainIntMap);

    //void basicDijkstra(vector < vector < int > > inpGraph, graphCoord startPos, vector <graphCoord> endPos, queue < graphCoord > &retSolution);

    basicDijkstra(mainIntMap, tempStartPos, tempEndPoss, tempRetSolution);

    convertQueueGCtoGL(tempRetSolution, tempSolution);
    retSolution = tempSolution;

}

void vectorstuff::convertUnitMapToIntMap(vector< vector < units > > inpUnitMap, vector < vector < int > > &retIntMap)
{
    vector < vector < int > > tempIntMap;

    int dimX;
    int dimY;

    dimX = inpUnitMap.size();

    dimY = 0;
    for (int i = 0; i < inpUnitMap.size(); i++)
    {
        if (inpUnitMap.at(i).size() > dimY)
            dimY = inpUnitMap.at(i).size();
    }

    vector < int > tempIntVec;
    for (int i = 0; i < dimX; i++)
    {
        tempIntVec.push_back(GSPACE);
    }

    for (int i = 0; i < dimY; i++)
    {
        tempIntMap.push_back(tempIntVec);
    }

    char tempChar;
    for (int currX = 0; currX < inpUnitMap.size(); currX++)
    {
        for (int currY = 0; currY < inpUnitMap.at(currX).size(); currY++)
        {
            tempChar = inpUnitMap.at(currX).at(currY).print_unit();
            if (characterParser(tempChar) == GWALL)
            {
                tempIntMap.at(currY).at(currX) = GWALL;
            }
        }

    }

    retIntMap = tempIntMap;
}

GridLoc vectorstuff::convertGCtoGL(graphCoord inpCoord)
{
    GridLoc retCoord;

    retCoord.x = inpCoord.x;
    retCoord.y = inpCoord.y;

    return retCoord;
}

graphCoord vectorstuff::convertGLtoGC(GridLoc inpCoord)
{
    graphCoord retCoord;

    retCoord.x = inpCoord.x;
    retCoord.y = inpCoord.y;

    return retCoord;
}

void vectorstuff::convertQueueGCtoGL(queue<graphCoord>inpQueue, queue<GridLoc>& retQueue)
{
    queue < GridLoc > tempQueue;

    while (!inpQueue.empty())
    {
        tempQueue.push(convertGCtoGL(inpQueue.front()));
        inpQueue.pop();
    }

    retQueue = tempQueue;
}

void vectorstuff::convertQueueGLtoGC(queue<GridLoc>inpQueue, queue<graphCoord>& retQueue)
{
    queue < graphCoord > tempQueue;

    while (!inpQueue.empty())
    {
        tempQueue.push(convertGLtoGC(inpQueue.front()));
        inpQueue.pop();
    }

    retQueue = tempQueue;
}


