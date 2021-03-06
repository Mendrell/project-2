/*

These are just functions that are useful
but don't really in a specific class

*/

#include "utilityFunctions.h"
#include <math.h>       /* ceil */

utilityFunctions::utilityFunctions()
{
    //ctor
}

utilityFunctions::~utilityFunctions()
{
    //dtor
}

bool utilityFunctions::boxCollision (loc objectLoc0, cartRealDim2d objectDim0, loc objectLoc1, cartRealDim2d objectDim1)
{
	//do box collision calculations
	bool retIsCollision;

	loc obj0MinBounds = objectLoc0;
	loc obj0MaxBounds = {objectLoc0.x+objectDim0.width, objectLoc0.y+objectDim0.height};
	loc obj1MinBounds = objectLoc1;
	loc obj1MaxBounds = {objectLoc1.x+objectDim1.width, objectLoc1.y+objectDim1.height};

	retIsCollision = true;
	if (obj0MaxBounds.x < obj1MinBounds.x || obj0MinBounds.x > obj1MaxBounds.x)
		retIsCollision = false;
	if (obj0MaxBounds.y < obj1MinBounds.y || obj0MinBounds.y > obj1MaxBounds.y)
		retIsCollision = false;

	return retIsCollision;
}

bool utilityFunctions::gridCollision(GridLoc objLoc0, GridLoc objLoc1)
{
    return (objLoc0.x == objLoc1.x && objLoc0.y == objLoc1.y);
}

bool utilityFunctions::isSameGridLoc(GridLoc objLoc0, GridLoc objLoc1)
{
    return (objLoc0.x == objLoc1.x && objLoc0.y == objLoc1.y);
}

bool utilityFunctions::isInGridBounds(gridSize inpGridSize, GridLoc inpGridLoc)
{
    return (inpGridLoc.x < inpGridSize.width && inpGridLoc.x >= 0 && inpGridLoc.y < inpGridSize.height && inpGridLoc.y >= 0);
}

void utilityFunctions::displayGLQueue(queue<GridLoc>inpQueue)
{
    while (!inpQueue.empty())
    {
        cout << inpQueue.front().x << ":" << inpQueue.front().y << " ";
        inpQueue.pop();
    }
    cout << endl;
}

void utilityFunctions::displayStrQueue(queue<string>inpQueue)
{
    while (!inpQueue.empty())
    {
        cout << inpQueue.front() << " ";
        inpQueue.pop();
    }
    cout << endl;
}

GridLoc utilityFunctions::realToGrid(loc inpRealLoc, int inpGridSize)
{
    GridLoc val;
    double inpUnitWidth = calcUnitWidth(inpGridSize);
   val.x = (int)(ceil((inpRealLoc.x +(1-inpUnitWidth))/inpUnitWidth));
   val.y = (int)(ceil((inpRealLoc.y +(1-inpUnitWidth))/inpUnitWidth));

    return val;
}

double utilityFunctions::calcUnitWidth(int inpGridSize)
{
    double unitWidth;
    unitWidth = (double)2.0/inpGridSize;
    return unitWidth;
}
