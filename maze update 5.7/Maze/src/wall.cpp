/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <wall.h>
#include <iostream>

using namespace std;


wall::wall()
{
    //ctor
    liveWall = true;
    GetWallLoc.x = -1;
    GetWallLoc.y = -1;
    objCurrGridLoc = GetWallLoc;
}

wall::~wall()
{
    //dtor
}

void wall::wallInit(int grid,char* FileName)
{
    gridSize = grid;
    unitWidth = (float)2/grid;
    wallTex = TextureLoader(FileName);
}

void wall::drawWall()
{
    if(liveWall)
    {

    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,wallTex);

    glPushMatrix();
    glTranslatef(wallBrk.x,wallBrk.y,0.0);

    glScalef(1.0/(float)gridSize,1.0/(float)gridSize,1);


     glBegin(GL_POLYGON);
            glTexCoord2f(0,0);
            glVertex3f(1,1,0.0f);

            glTexCoord2f(1,0);
            glVertex3f(-1,1,0.0f);

            glTexCoord2f(1,1);
            glVertex3f(-1,-1,0.0f);

            glTexCoord2f(0,1);
            glVertex3f(1,-1,0.0f);
    glEnd();
    glPopMatrix();
    }
}

void wall::placeWall(int x, int y)
{
    GetWallLoc.x= x;
    GetWallLoc.y= y;

    x+=1;
    y+=1;

    wallBrk.x =  (unitWidth)*x-1-unitWidth/2;
    wallBrk.y =  (unitWidth)*y-1-unitWidth/2;
}

GridLoc wall::getObjCurrGridLoc()
{
    //return objCurrGridLoc;
    return GetWallLoc;
}

GridLoc wall::getObjNewGridLoc()
{
    return objNewGridLoc;
}

GridLoc wall::getObjOldGridLoc()
{
    return objOldGridLoc;
}

void wall::setObjCurrGridLoc(GridLoc inpGridLoc)
{
    GetWallLoc = inpGridLoc;
    objCurrGridLoc = inpGridLoc;
}

void wall::setObjNewGridLoc(GridLoc inpGridLoc)
{
    objCurrGridLoc = inpGridLoc;
}

void wall::setObjOldGridLoc(GridLoc inpGridLoc)
{
    objCurrGridLoc = inpGridLoc;
}

bool wall::getIsObjDead()
{
    return !liveWall;
}

void wall::setIsObjDead(bool inpBool)
{
    liveWall = !inpBool;
}
