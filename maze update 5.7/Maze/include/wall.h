/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018

 This is the wall object in game
 It is used to block movement and projectiles

 */
#ifndef WALL_H
#define WALL_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */


class wall
{
    public:
        wall();                            // constructor
        virtual ~wall();                   // De constructor
        wall(int);                         // overload constructor

            void drawWall();               // Draw the Maze wall
            void wallInit(int, char *);    // initialize the wall
            void placeWall(int, int);      // place the wall

			GridLoc getObjCurrGridLoc();
            GridLoc getObjNewGridLoc();
            GridLoc getObjOldGridLoc();

            void setObjCurrGridLoc(GridLoc inpGridLoc);
            void setObjNewGridLoc(GridLoc inpGridLoc);
            void setObjOldGridLoc(GridLoc inpGridLoc);

            bool getIsObjDead();
            void setIsObjDead(bool inpBool);

            float unitWidth;               // unit width of the grid cell
            int gridSize;                  // grid size

             GridLoc GetWallLoc;         // Grid Location of the wall
            bool liveWall;                 // wall status (broken or not)
    protected:

    private:
              loc wallBrk;                 // viewport location of the wall
              GLuint wallTex;              // wall texture handler

			GridLoc objCurrGridLoc;
            GridLoc objNewGridLoc;
            GridLoc objOldGridLoc;
};

#endif // WALL_H
