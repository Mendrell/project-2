#include "utilityFunctions.h"

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

