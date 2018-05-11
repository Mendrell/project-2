#ifndef ENEMYAI_H
#define ENEMYAI_H
#include <string.h>
#include <CommonThings.h>
#include <Maze.h>
#include <iostream>
#include <Timer.h>
#include <player.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <Enemies.h>

#include <wall.h>
#include <math.h>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <tuple>
#include <units.h>
#include <vectorstuff.h>
#include <queue>


using namespace std;

class enemyai
{
    public:
        enemyai();
        virtual ~enemyai();
        int nodesExpanded;
        queue <units> solutionQueue;
        vector <units> endPositions;

        void breadthFirstSearch(vector < vector < units > > inpGraph,  units startPos, vector <units> endPos, queue < units > &retSolution)
            {
                nodesExpanded = 0;
                queue < queue <units> > potentialSolutions;
                queue <units> frontier;
                queue <units> explored;
                queue <units> tempSolution;
                vector <units> tempExpansion;
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
                        expandGraphLoc(inpGraph, frontier.front(), tempExpansion);//<-----------------
                        nodesExpanded++;
                        for (int i = 0; i < tempExpansion.size(); i++)
                        {
                            //check if not wall
                            if (getMapElement(inpGraph, tempExpansion.at(i).x, tempExpansion.at(i).y).type != '#')
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
             int searchvectorcount = 0;
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
                    if (vecToSearch.at(count00).x == varToFind.x && vecToSearch.at(count00).y == varToFind.y)
                    {
                        done = true;
                        retIndex = count00;
                    }
                    //cout << "\n \ncount in searchvector   "<< count00 << endl << endl;
                    count00++;//this should not and never does iterate past 0
                }

                searchvectorcount++;
                //cout << searchvectorcount <<endl<<endl;
                return retIndex;
                //this function is returning when the enemy encounters the player corectly, things get a little wacky becasue
                //the walls are getting over written when a enemy or player passes through them
                //enemy should not be going through walls though checked in BFS
            }

            void expandGraphLoc(vector < vector < units > > inpGraph, units inpCoord, vector < units > &retExpansion)
            {
                vector < units > tempVec;
                char c = inpCoord.type;//this will be the enemies character type 'E'
                for (int i = inpCoord.x - 1; i <= inpCoord.x + 1; i++)
                {
                    for (int j = inpCoord.y - 1; j <= inpCoord.y + 1; j++)
                    {
                        if (!(i == inpCoord.x && j == inpCoord.y)) //this makes it so it doesn't include itself
                        {
                        if (i == inpCoord.x || j == inpCoord.y) //this makes it so that it only moves up and down - without out diagonal is valid
                        {
                            if (i >= 0 && i < inpGraph.size())
                            {
                                if (j >= 0 && j < inpGraph.at(i).size())
                                {
                                    units temp;
                                    temp.set_unit(i, j, c);
                                    //cout << "push back" << endl;
                                    tempVec.push_back(temp);
                                }
                            }
                        }
                        }
                    }
                }
                for (int z=0; z < tempVec.size() ; z++){
                    cout << tempVec[z].x << ", " << tempVec[z].y << "   ";
                }
                cout << endl;
                system("pause");
                retExpansion = tempVec;
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
            bool isInQueue(queue <T> inpQueue, T inpElement)
            {
                bool found;

                found = false;
                while (!inpQueue.empty() && !found)
                {
                    if (inpQueue.front().x == inpElement.x && inpQueue.front().y == inpElement.y)
                    {
                        found = true;
                    }
                    inpQueue.pop();
                }

                return found;
            }

            units returnSolution(vector< vector <units> > inpGraph,  units startPos, vector <units> endPos){
                breadthFirstSearch(inpGraph, startPos, endPos, solutionQueue);
                return solutionQueue.front();
                solutionQueue.pop();
            }
    protected:

    private:
};

#endif // ENEMYAI_H
