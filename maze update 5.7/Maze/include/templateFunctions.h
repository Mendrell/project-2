#ifndef TEMPLATEFUNCTIONS_H
#define TEMPLATEFUNCTIONS_H

#include <queue>
#include <CommonThings.h>

extern "C" {
#include <stdint.h>
}

//using namespace std;

class templateFunctions
{
    public:
        templateFunctions();
        virtual ~templateFunctions();

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



    protected:

    private:
};

#endif // TEMPLATEFUNCTIONS_H
