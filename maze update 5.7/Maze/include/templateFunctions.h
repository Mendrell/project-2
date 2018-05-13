/*

A utility class where the objects may vary
to reduce redundant code

*/


#ifndef TEMPLATEFUNCTIONS_H
#define TEMPLATEFUNCTIONS_H

#include <queue>
#include <CommonThings.h>

extern "C" {
#include <stdint.h>
}

using namespace std;

//using namespace std;

class templateFunctions
{
    public:
        //templateFunctions();
        //~templateFunctions();

        template <class T, class U>
        bool collisionObjectToObject(T *inpObj1, U *inpObj2);

        template <class T, class U>
        bool collisionObjectBlockedByObject(T *inpObj1, U *inpObj2);

        template<class T>
        void unionVectors(std::vector <T> frontVec, std::vector <T> backVec, std::vector <T> &retVec);

        template<class T>
        int searchVector(std::vector <T> vecToSearch, T varToFind);

        template <class T>
        uintptr_t pointerToInt(T* inpPtr);

        template <class T>
        T* pointerToInt(uintptr_t inpInt);

        template <class T>
        void removeArrayElement(T inpArr[], int inpIndex, int inpLength);

        template <class T>
        bool isInQueue(queue <T> inpQueue, T inpElement);

        template <class T>
        bool isInPriorityQueue(priority_queue <T> inpQueue, T inpElement);

        template <class T>
        void display1DVec(vector <T> inpVector, string inpDelim = "");

        template <class T>
        void display2DVec(vector < vector <T> > inpVector, string inpDelim = "");

        //IMPORTANT: Y is the first dimension, X is the second
        //i.e. vec.at(y).at(x)
        //so if your vec is vec.at(x).at(y)
            //then you will need to flip the inputs
        template <class T>
        T getMapElement(vector < vector <T> > inpVector, int inpX, int inpY);

        template <class T>
        void display1DQueue(queue <T> inpQueue, string inpDelim = "");

        template <class T>
        void display1DPriorQueue(priority_queue <T> inpQueue, string inpDelim = "");

        template <class T>
        void removeVectorElement(vector <T> &retVec, int inpIndex);

        template <class T>
        void removeVectorPointerElement(vector <T> *retVec, int inpIndex);

        template <class T>
        void removeVectorPointerElementPointer(vector <T*> *retVec, int inpIndex);

        template <class T>
        void clearVectorPointerElementPointer(vector <T*> *retVec);

    protected:

    private:
};

//#include <templateFunctions.cpp>

#endif // TEMPLATEFUNCTIONS_H

//#include <templateFunctions.cpp>
