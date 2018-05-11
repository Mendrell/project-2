#ifndef VECTORSTUFF_H
#define VECTORSTUFF_H
#include <units.h>
#include <vector>
#include <string>
#include <iostream>
#include <Maze.h>


using namespace std;


class vectorstuff
{
    public:
        vectorstuff()
        {

        }

        vector<vector <units> > mastervec;
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



    protected:

    private:
        //vector<vector <units> > mastervec;
};


#endif // VECTORSTUFF_H
