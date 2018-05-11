/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef ENEMIES_H
#define ENEMIES_H

#include<CommonThings.h>
#include <Maze.h>
#include <time.h>
#include <thread>
#include <string>
#include <math.h>       /* ceil */
#include <vectorstuff.h>

class Enemies
{
    public:
        Enemies();                          // constructor
        virtual ~Enemies();                 // DeConstructor
        void initEnm(int, int, char *);     // Initialize Enemy

        void placeEnemy(int,int);           // place enemy
        void drawEnemy();                   // Draw Enemy with Animation
        void moveEnemy(string);             // move Enemy left,right,up,down
        void animate();                     // Animate sprite
        GridLoc getEnemyLoc();              // Return Enemy current grid location
        bool getIsObjectActing();
        void objectAction(vectorstuff, units, vector<units>);
        void setActionStatus(bool inpCanAct);
        void updateEnemyVecPos();
        int enemyloctrackx[2]{};
        int enemyloctracky[2]{};
        void enemyupdatepos(int, int);
        void updateEnemyVecPos(vectorstuff, int, int);


        int gridSize;                       // Grid size of the maze
        float unitWidth;                    // Unit width of the grid
        int stepsPerMove;                   // Step count for animation
        bool live;                          // Status of the Enemy
    protected:

    private:
        void changeDirection();

        int frames;                        // number of frames generally
        float t;                           // steps for animation count
        GLuint enmTex;                     // Image Texture

        float xmax, xmin,ymax,ymin;        // Animated Texture mapping
        bool up,down,left,right;           // move direction
        float moveDis=0;                   // Moving distance for animation
        loc enmLoc;                        // location of the enemy

        Timer *objectTimer;
        int objectDirectionFaced; //currently using clock directions 6 oclock behind 3 oclock to right
        bool isObjectActing;
        bool canObjectAct;
        bool needDirectionChange;
        int objectGenericCounter;
};

#endif // ENEMIES_H
