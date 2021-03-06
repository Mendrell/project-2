#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <queue>
#include <CommonThings.h>


class utilityFunctions
{
    public:
        utilityFunctions();
        virtual ~utilityFunctions();

        bool boxCollision (loc objectLoc0, cartRealDim2d objectDim0, loc objectLoc1, cartRealDim2d objectDim1);
        bool gridCollision (GridLoc objLoc0, GridLoc objLoc1);
        bool isSameGridLoc(GridLoc objLoc0, GridLoc objLoc1);
        bool isInGridBounds(gridSize inpGridSize, GridLoc inpGridLoc);
        void displayGLQueue(queue < GridLoc > inpQueue);
        void displayStrQueue(queue < string > inpQueue);
        double calcUnitWidth(int inpGridSize);
        GridLoc realToGrid(loc inpRealLoc, int inpGridSize);

    protected:

    private:
};

#endif // UTILITYFUNCTIONS_H
