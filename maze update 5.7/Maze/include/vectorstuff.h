#ifndef VECTORSTUFF_H
#define VECTORSTUFF_H
#include <units.h>
//#include <vector>
#include <string>
#include <iostream>
#include <Maze.h>
#include <queue>


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


class vectorstuff
{
    public:
        vectorstuff();
        virtual ~vectorstuff();

        vector<vector <units> > mastervec;
        units temp1;//old
        units temp2;//new
        bool bs = false;
        int test;

        void pathFinding(GridLoc startPos, GridLoc endPos, queue < GridLoc > &retSolution);

         void crap(){
            mastervec[temp1.x][temp1.y] = temp1;
            mastervec[temp2.x][temp2.y] = temp2;
            bs = false;

        }


        void updateVecref(int x, int y, char c)//sets new values to the vector given coordinates and a character
            {
                units temp;
                temp.set_unit(x, y, c);
                mastervec[x][y] = temp;
            }

        void init2dvec(int x){
                mastervec.clear();
                for(int i=0; i<x;i++){//AS this initializes an empty 2d vector
                    vector<units> tempvec;
                    for (int j = 0; j<x;j++){
                        units temp;
                        temp.set_unit(i, j, '_');
                        tempvec.push_back(temp);
                    }
                    mastervec.push_back(tempvec);
                }
            }
        void display1DVec(vector <units> inpVector, string inpDelim = "")//units has to be its own class
            {
                for (int i = 0; i < inpVector.size(); i++)
                {
                    cout << inpVector[i].print_unit() << inpDelim;
                }
                cout << endl;
            }
        void display2DVec()//AS displays the 2d vector, it does it sidways i wonder if this can be fixed
            {
                string inpDelim = "";
                for (int i = 0; i < mastervec.size(); i++)
                {
                    display1DVec(mastervec.at(i), inpDelim);
                }
            }
        units getvecpos(int x, int y) {
            return mastervec[x][y];
        }

        bool vectorMapisWallCollision(int inpX, int inpY)
        {
            return (getvecpos(inpX, inpY).print_unit() == '#');
        }
        bool vectorMapisEnemyCollision(int inpX, int inpY)
        {
            return (getvecpos(inpX, inpY).print_unit() == 'E');
        }
        bool vectorMapisPlayerCollision(int inpX, int inpY)
        {
            return (getvecpos(inpX, inpY).print_unit() == 'P');
        }



    protected:

    private:

        void convertUnitMapToIntMap(vector < vector < units > > inpUnitMap, vector < vector < int > > &retIntMap);
        GridLoc convertGCtoGL(graphCoord inpCoord);
        graphCoord convertGLtoGC(GridLoc inpCoord);
        void convertQueueGCtoGL(queue < graphCoord > inpQueue, queue < GridLoc > &retQueue);
        void convertQueueGLtoGC(queue < GridLoc > inpQueue, queue < graphCoord > &retQueue);

        void basicDijkstra(vector < vector < int > > inpGraph, graphCoord startPos, vector <graphCoord> endPos, queue < graphCoord > &retSolution);

        void expandGraphLoc(vector < vector < int > > inpGraph, graphCoord inpCoord, vector < graphCoord > &retExpansion);
        int characterParser(char inpChar);

        int taxiDistanceGraphCoord(graphCoord inpStartPos, graphCoord inpEndPos);
        int minTaxiDistGC(graphCoord inpStartPos, vector < graphCoord > inpEndPos);

        bool isInPQGC(priority_queue <priorityCoordObject> inpQueue, graphCoord inpElement);
        char intParser(int inpInt);

        //vector<vector <units> > mastervec;
};


#endif // VECTORSTUFF_H
