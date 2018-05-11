#include "templateFunctions.h"

using namespace std;
/*
templateFunctions::templateFunctions()
{
    //ctor
}

templateFunctions::~templateFunctions()
{
    //dtor
}
*/
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

template <class T>
bool templateFunctions::isInQueue(queue <T> inpQueue, T inpElement)
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
bool templateFunctions::isInPriorityQueue(priority_queue <T> inpQueue, T inpElement)
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


template <class T>
void templateFunctions::display1DVec(vector <T> inpVector, string inpDelim)
{
	for (int i = 0; i < inpVector.size(); i++)
	{
		cout << inpVector.at(i) << inpDelim;
	}
	cout << endl;
}

template <class T>
void templateFunctions::display2DVec(vector < vector <T> > inpVector, string inpDelim)
{
	for (int i = 0; i < inpVector.size(); i++)
	{
		display1DVec(inpVector.at(i), inpDelim);
	}
}


template <class T>
T templateFunctions::getMapElement(vector < vector <T> > inpVector, int inpX, int inpY)
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
void templateFunctions::display1DQueue(queue <T> inpQueue, string inpDelim)
{
	while (!inpQueue.empty())
	{
		cout << inpQueue.front() << inpDelim;
		inpQueue.pop();
	}
	cout << endl;
}


template <class T>
void templateFunctions::display1DPriorQueue(priority_queue <T> inpQueue, string inpDelim)
{
	while (!inpQueue.empty())
	{
		cout << inpQueue.top() << inpDelim;
		inpQueue.pop();
	}
	cout << endl;
}


template <class T>
void templateFunctions::removeVectorElement(vector <T> &retVec, int inpIndex)
{
    vector <T> tempVec;
    tempVec = retVec;
    if (inpIndex < tempVec.size())
    {
        tempVec.erase(tempVec.begin() + inpIndex);
    }


    retVec = tempVec;
}
