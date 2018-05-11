#include "templateFunctions.h"

using namespace std;

templateFunctions::templateFunctions()
{
    //ctor
}

templateFunctions::~templateFunctions()
{
    //dtor
}

template<class T>
void templateFunctions::unionVectors(vector <T> frontVec, vector <T> backVec, vector <T> &retVec)
{
    for (int i = 0; i < backVec.size(); i++)
    {
        if (searchVector(frontVec, backVec.at(i)) == -1)
            frontVec.push_back(backVec.at(i));
    }

    retVec = frontVec;
}

template <class T>
uintptr_t templateFunctions::pointerToInt(T* inpPtr)
{
    //return uintptr_t(inpPtr);
    return reinterpret_cast<uintptr_t>(inpPtr);
}

template <class T>
T* templateFunctions::pointerToInt(uintptr_t inpInt)
{
    return (T*) inpInt;
}

template <class T>
int templateFunctions::searchVector(std::vector<T>vecToSearch, T varToFind)
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
void templateFunctions::removeArrayElement(T inpArr[], int inpIndex, int inpLength)
{
    for (int i = inpIndex + 1; i < inpLength; i++)
    {
        inpArr[i-1] = inpArr[i];
    }
}
