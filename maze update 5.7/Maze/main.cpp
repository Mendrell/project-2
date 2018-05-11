/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018

 NM: 051018: changed it so that keys do not directly call any function
    strong advice, have the keys only set flags
    have the flags determine where a function should be called in idle()

 */

#include <string.h>
#include <CommonThings.h>
#include <Maze.h>
#include <iostream>
#include <Timer.h>
#include <player.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <Enemies.h>

#include <wall.h>
#include <math.h>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <tuple>
#include <units.h>
#include <vectorstuff.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dos.h>
#include <windows.h>

#include <utilityFunctions.h>

#include <templateFunctions.h>
#include <templateFunctions.cpp>

/* GLUT callback Handlers */

using namespace std;

const int GENEMYLIMIT = 10;
const int GWALLLIMIT = 100;

//Maze *M = new Maze();                         // Set Maze grid size
void updatepos(int x, int y);//AS this will update position 0 to the current position of the player
void checkwallcollision();

void pathFindToPlayer(GridLoc startPos, queue <string> &retPath);

void clearPlayerList();
void clearEnemyList();
void clearWallList();
void clearProjectileList();

void cleanPlayerList();
void cleanEnemyList();
void cleanWallList();
void cleanProjectileList();

void resetPlayerList();
void resetEnemyList();
void resetWallList();

void clearMaze();
void resetMaze();
void resetPtrObjects();

Maze *M = new Maze();                         // Set Maze grid size
//Maze *M = new Maze(15);                         // Set Maze grid size
Player *P = new Player();                       // create player

//wall W[GWALLLIMIT];                                    // wall with number of bricks
//Enemies E[GENEMYLIMIT];                                  // create number of enemies
vector < wall > *W = new vector < wall >;
vector < Enemies > *E = new vector < Enemies >;
Timer *T0 = new Timer();                        // animation timer

float wWidth, wHeight;                          // display window width and Height
float xPos,yPos;                                // Viewpoar mapping

playerActions plyActs;
playerActions keysPressed;
bool canTakeAction;
bool actionInProgress;
bool menuisopen;
bool gamewin;
bool gamestart=0;
int chestlocationx;
int chestlocationy;
bool canshoot = false;
void display(void);                             // Main Display : this runs in a loop

int loctrackx[2] = {0,0};//AS tracks the past and current location of player x coordinate
int loctracky[2] = {0,0};//AS tracks the past and current location of player y coordinate
//should probably add this to the player class at some point

//---------------------------------------------------------------------------------------
//things needed for initializing
string comm;//AS value to recognize object wall player enemy chest etc.
int coor1;//AS sets the first coordinate
int coor2;//AS sets the second coordinate
int playercount = 0;//AS records the number of player cannot be greater than 1
int enemycount = 0;//AS tracks the number of enemies generated
int wallcount = 0;//AS tracks the number of walls generated
//---------------------------------------------------------------------------------------


void resize(int width, int height)              // resizing case on the window
{
    wWidth = width;
    wHeight = height;

    if(width<=height)
        glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
}

void checkBounds (int x, int y){
    if (x > M->getGridSize()-1 || y > M->getGridSize() - 1){//AS gidsize - 1 becaseu we start at coordinate 0 0
        cout << "Values entered are out of bounds!\n";
        system("pause");
        exit(EXIT_FAILURE);
    }
}

vectorstuff vecref;//AS declares the vector we keep track of everything in

void updateenemyvecmain(){//AS i dont know why but this function has to be passed in main or it wont work
    for(int i = 0; i < E->size(); i++){
            int curx = E->at(i).getEnemyLoc().x;
            int cury = E->at(i).getEnemyLoc().y;
            E->at(i).updateEnemyVecPos(vecref, curx, cury);
            vecref.updateVecref(E->at(i).enemyloctrackx[1], E->at(i).enemyloctracky[1], '_');
            vecref.updateVecref(E->at(i).enemyloctrackx[0], E->at(i).enemyloctracky[0], 'E');

/*void updateenemyvecmain(){//AS i dont know why but this function has to be passed in main or it wont work
    for(int i = 0; i < enemycount; i++){
            int curx = E[i].getEnemyLoc().x;
            int cury = E[i].getEnemyLoc().y;
            E[i].updateEnemyVecPos(vecref, curx, cury);
            vecref.updateVecref(E[i].enemyloctrackx[1], E[i].enemyloctracky[1], '_');
            vecref.updateVecref(E[i].enemyloctrackx[0], E[i].enemyloctracky[0], 'E');
*/
        }

}
vector<units> perimeter;
void checkperim(units bin){//Dhanyu may be giving us a better check condition for the player still may need to do this for the enemy
    perimeter.push_back(vecref.getvecpos(bin.x, bin.y));

}

vector<units> morty(1);//all this vector does is hold the player position


void init(int a)
{
    //resetPtrObjects();

    if(!gamestart){
    gamestart=1;

    //resetPtrObjects();

    glEnable(GL_COLOR_MATERIAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(0, wWidth, 0, wHeight);

    T0->Start();                                        // set timer to 0

    glEnable(GL_BLEND);                                 //display images with transparent
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    string level[4] = {"mapgen.txt","mapgen2.txt","mapgen3.txt","mapgen4.txt"};

    M->loadBackgroundImage("images/bak.jpg");           // Load maze background image
    ifstream bob;//AS initializes a file called bob
    bob.open("mapgen.txt");
    if(!bob.is_open()){//AS exits the program if the file does not exist
    cout << "file not found!\n";
    exit(EXIT_FAILURE);
    }



    enemycount = 0;
    int tempCount00 = 0;
    Enemies tempEnemy00;
    while(bob >> comm >> coor1 >> coor2){

        //cout << tempCount00 << endl;
        tempCount00++;
        //cout << tempCount00 << endl;
        //cout << comm << " " << coor1 << " " << coor2 << endl;
        if(comm == "grid"){

            M->setgrid(coor1);
            vecref.init2dvec(coor1);
        }

        else if (comm == "chest"){//needs to be lower case
            checkBounds(coor1,coor2);
            M->loadChestImage("images/chest.png");              // load chest image
            M->placeChest(coor1,coor2);// place chest in a grid
            chestlocationx = coor1;
            chestlocationy = coor2;

            vecref.updateVecref(coor1, coor2, 'C');//updates the vector units

            //cout << "chere00" << endl;

        }
        else if (comm == "player"){
            if(playercount <= 1){
            checkBounds(coor1,coor2);
            P->initPlayer(M->getGridSize(),6,"images/p.png");   // initialize player pass grid size,image and number of frames
            P->loadArrowImage("images/arr.png");                // Load arrow image
            P->placePlayer(coor1,coor2);//place player


            vecref.updateVecref(coor1, coor2, 'P');

//-----------------------------------------------------------------------------------
//this may need to get moved into the player class
            loctrackx[0] = coor1; loctrackx[1] = coor1;
            loctracky[0] = coor2; loctracky[1] = coor2;
//-----------------------------------------------------------------------------------            updateVecref(coor1, coor2, 'P');//updates the vector units
            playercount++;

            }
            else{
                cout << "can not have more than one player.\n";
                system("pause");
                exit(EXIT_FAILURE);
            }
        }
        else if (comm == "arrow"){
            checkBounds(coor1,coor2);
            M->loadSetOfArrowsImage("images/arrwset.png");// load set of arrows image
            M->placeStArrws(coor1,coor2);// place set of arrows

            vecref.updateVecref(coor1, coor2, 'A');//updates the vector units

        }

        else if (comm == "enemy"){
            checkBounds(coor1,coor2);
            if(enemycount < GENEMYLIMIT){
                /*
                E[enemycount].initEnm(M->getGridSize(),4,"images/e.png"); //Load enemy image
                E[enemycount].placeEnemy(coor1,coor2);
                int curx = E[enemycount].getEnemyLoc().x;
                int cury = E[enemycount].getEnemyLoc().y;
                E[enemycount].enemyupdatepos(curx, cury);
                */

                //Enemies tempEnemy00;
                //E->push_back(Enemies());
                E->push_back(tempEnemy00);
                E->back().initEnm(M->getGridSize(),4,"images/e.png"); //Load enemy image
                E->back().placeEnemy(coor1,coor2);
                int curx = E->back().getEnemyLoc().x;
                int cury = E->back().getEnemyLoc().y;
                //E->back().enemyupdatepos(curx, cury);

                vecref.updateVecref(coor1, coor2, 'E');//updates the vector units

                enemycount++;

                cout << E->back().getEnemyLoc().x << " " << E->back().getEnemyLoc().y << endl;
                cout << E->back().getObjCurrGridLoc().x << " " <<  E->back().getObjCurrGridLoc().y << endl;
                cout << E->back().getObjOldGridLoc().x << " " <<  E->back().getObjOldGridLoc().y << endl;
                cout << E->back().getObjCurrRealLoc().x << " " <<  E->back().getObjCurrRealLoc().y << endl;
                cout << E->back().getObjOldRealLoc().x << " " <<  E->back().getObjOldRealLoc().y << endl;
                //cout << "ehere01" << endl;
            }
            else{
                cout << "too many enemies!\n";
                system("pause");
                exit(EXIT_FAILURE);
            }
        }
        else if (comm == "resize"){
            new Maze(coor1);
        }

        else if (comm == "wall"){
            checkBounds(coor1,coor2);
            int maxwall = M->getGridSize();
            if(wallcount < GWALLLIMIT){
                /*
                W[wallcount].wallInit(M->getGridSize(),"images/wall.png");// Load walls
                W[wallcount].placeWall(coor1,coor2);// place each brick
                */

                W->push_back(wall());
                W->back().wallInit(M->getGridSize(),"images/wall.png");// Load walls
                W->back().placeWall(coor1,coor2);// place each brick

                vecref.updateVecref(coor1, coor2, '#');//updates the vector units

                wallcount++;
            }
            else{
                cout << "too many walls!";
                system("pause");
                exit(EXIT_FAILURE);
                       // place each brick
            }
        }
        else if(comm != "wall" || comm != "arrow" || comm != "enemy" || comm != "player" || comm != "chest"){
            cout << "Invalid command in text file!\n";
            system("pause");
            exit(EXIT_FAILURE);
        }

        //cout << "eowHere" << endl;

   } // need to add a | to the end of the text file to act as and end character\

    plyActs = {false, false, false, false, false};
    keysPressed = plyActs;
    canTakeAction = false;
    actionInProgress = false;

}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);        // clear display screen

        glPushMatrix();
         M->drawBackground();
        glPopMatrix();

        if(!menuisopen && !gamewin){
        for(int i=0; i<W->size();i++)
        {
           W->at(i).drawWall();
        }

        glPushMatrix();
            M->drawGrid();
        glPopMatrix();

        glPushMatrix();
            P->drawplayer();
        glPopMatrix();

        for(int i=0; i<E->size();i++)
        {
        E->at(i).drawEnemy();
        }

        glPushMatrix();
            P->drawArrow();
        glPopMatrix();

         glPushMatrix();
           M->drawChest();
        glPopMatrix();

    if(!canshoot){
        glPushMatrix();
           M->drawArrows();
        glPopMatrix();
    }
        }
    glutSwapBuffers();
}

void returntomenu();

void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':
            // if(!M->liveSetOfArrws)      // if setof arrows were picked by player
            //P->shootArrow();
            if (canshoot){
            keysPressed.shoot = true;
            plyActs.shoot = true;
            canTakeAction = true;
            }

        break;
        case 27 :                       // esc key to exit
        case 'q':
            exit(0);
            break;

        case 'm':
            if (menuisopen){

                menuisopen=0;
                //glClear (GL_COLOR_BUFFER_BIT);
            M->loadBackgroundImage("images/bak.jpg");
            //glPushMatrix();
            M->drawBackground();
            //glPopMatrix();
                break;
                }
            //glClear (GL_COLOR_BUFFER_BIT);
            M->loadBackgroundImage("images/menu.jpg");
            //glPushMatrix();
            M->drawBackground();
            //glPopMatrix();
            menuisopen=1;
            break;
        case '1':
            if (menuisopen){
                wallclear(W, wallcount);
                enemyclear(E, enemycount);
                init(0);
                menuisopen=0;
            } break;


        case '2':
            if (menuisopen){
                wallclear(W, wallcount);
                enemyclear(E, enemycount);
                init(1);
                menuisopen=0;
            }break;

        case '3':
            if (menuisopen){
                wallclear(W, wallcount);
                enemyclear(E, enemycount);
                init(2);
                menuisopen=0;
            } break;

        case '4':
            if (menuisopen){
                wallclear(W, wallcount);
                enemyclear(E, enemycount);
                init(3);
                menuisopen=0;
            } break;
    }

    glutPostRedisplay();
}

void returntomenu(){
    key('m', 0, 0);
}


 void GetOGLPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    xPos =posX ;
    yPos =posY ;
}


int Print(int Array[]){
    for (int i = 0; i < 2 ; i++){
        cout << Array[i] << " ";}
}

 void idle(void)
{

    utilityFunctions utilFunc;

     morty[0] = vecref.getvecpos(P->getPlayerLoc().x, P->getPlayerLoc().y);


    if (keysPressed.moveUp)
    {

        /*
         if((loctrackx[0] != loctrackx[1]) || (loctracky[0] != loctracky[1])){//makes it so that the enemy only moves when the player enter a new square
            vecref.updateVecref(loctrackx[1], loctracky[1], '_');//updates the vecref in real time
            vecref.updateVecref(loctrackx[0], loctracky[0], 'P');
        }
        //updateenemyvecmain();//there may be a better place to put this
        */
        keysPressed.moveUp = false;
    }
    if (keysPressed.moveDown)
    {
        /*
        //if(P->playerCollision(3,3))break;
         checkwallcollision();
         //updatepos(P->getPlayerLoc().x, P->getPlayerLoc().y);
         //displayloctrack();

         if((loctrackx[0] != loctrackx[1]) || (loctracky[0] != loctracky[1])){//makes it so that the enemy only moves when the player enter a new square
            vecref.updateVecref(loctrackx[1], loctracky[1], '_');
            vecref.updateVecref(loctrackx[0], loctracky[0], 'P');
        }
        //updateenemyvecmain();//there may be a better place to put this
        */
        keysPressed.moveDown = false;
    }
    if (keysPressed.moveLeft)
    {
        /*
        //if(P->playerCollision(3,3))break;
        checkwallcollision();
        //updatepos(P->getPlayerLoc().x, P->getPlayerLoc().y);
        //displayloctrack();

        if((loctrackx[0] != loctrackx[1]) || (loctracky[0] != loctracky[1])){//makes it so that the enemy only moves when the player enter a new square
        vecref.updateVecref(loctrackx[1], loctracky[1], '_');
        vecref.updateVecref(loctrackx[0], loctracky[0], 'P');
        }
       //updateenemyvecmain();//there may be a better place to put this
        */
        keysPressed.moveLeft = false;
    }
    if (keysPressed.moveRight)
    {
        /*
        //if(P->playerCollision(3,3))break;
         checkwallcollision();
         updatepos(P->getPlayerLoc().x, P->getPlayerLoc().y);
         //displayloctrack();

         if((loctrackx[0] != loctrackx[1]) || (loctracky[0] != loctracky[1])){//makes it so that the enemy only moves when the player enter a new square
            vecref.updateVecref(loctrackx[1], loctracky[1], '_');
            vecref.updateVecref(loctrackx[0], loctracky[0], 'P');
        }
        //updateenemyvecmain();//there may be a better place to put this
        */
        keysPressed.moveRight = false;
    }
    if (keysPressed.shoot)
    {
    }


    if (canTakeAction)
    {
        P->setActionStatus(plyActs, canTakeAction);

    }
    P->objectAction();
	bool isPlayerBlocked = false;

	/*
    for (int i = 0; i < W->size(); i++)
    {
        if (utilFunc.gridCollision(P->getObjCurrGridLoc(), W->at(i).getObjCurrGridLoc()))
            tempBool00 = true;
    }
    */
    //If it blocks you don't move
    //If it kills you don't move
    //If you kill it and you don't die, then move is okay
    if (vecref.vectorMapisWallCollision(P->getObjCurrGridLoc().x, P->getObjCurrGridLoc().y))
        isPlayerBlocked = true;
    if (vecref.vectorMapisEnemyCollision(P->getObjCurrGridLoc().x, P->getObjCurrGridLoc().y))
    {
        isPlayerBlocked = true;
        P->setIsObjDead(true);
    }

    if ((P->getPlayerLoc().x == M->GetStArrwsLoc().x) && (P->getPlayerLoc().y == M->GetStArrwsLoc().y)){
        canshoot = true;
    }

    P->objectLogicAction(isPlayerBlocked);

    if (!utilFunc.isSameGridLoc(P->getObjCurrGridLoc(), P->getObjOldGridLoc()))
     {
         vecref.updateVecref(P->getObjOldGridLoc().x, P->getObjOldGridLoc().y, '_');
         vecref.updateVecref(P->getObjCurrGridLoc().x, P->getObjCurrGridLoc().y, 'P');
     }

    if(!utilFunc.isSameGridLoc(P->getObjCurrGridLoc(), P->getObjOldGridLoc())){//makes it so that the enemy only moves when the player enter a new square
            for (int i = 0; i < E->size(); i++)
            {
                     E->at(i).setActionStatus(canTakeAction);
            }
    }

    for (int i = 0; i < E->size(); i++)
    {
        queue < string > tempEnemyPath;

        if (canTakeAction)
        {
            pathFindToPlayer(E->at(i).getObjNewGridLoc(), tempEnemyPath);
            E->at(i).setObjTravelPath(tempEnemyPath);
        }

        E->at(i).objectAction(vecref, vecref.getvecpos(E->at(i).getEnemyLoc().x, E->at(i).getEnemyLoc().y), morty);

        bool isBlockedMove;
        isBlockedMove = !utilFunc.isInGridBounds({M->getGridSize(), M->getGridSize()}, E->at(i).getObjNewGridLoc());
        //isBlockedMove = utilFunc.isInGridBounds({M->getGridSize(), M->getGridSize()}, E->at(i).getObjNewGridLoc());
        if (vecref.vectorMapisWallCollision(E->at(i).getObjNewGridLoc().x, E->at(i).getObjNewGridLoc().y))
            isBlockedMove = true;
        if (vecref.vectorMapisPlayerCollision(E->at(i).getObjNewGridLoc().x, E->at(i).getObjNewGridLoc().y))
        {
            isBlockedMove = true;
            P->setIsObjDead(true);
        }
        if (vecref.vectorMapisEnemyCollision(E->at(i).getObjNewGridLoc().x, E->at(i).getObjNewGridLoc().y))
            isBlockedMove = true;

         E->at(i).objectLogicAction(isBlockedMove);

         if (canTakeAction)
         {
             //cout << "here00" << endl;
             cout << E->at(i).getObjOldGridLoc().x << " " << E->at(i).getObjOldGridLoc().y << endl;
             cout << E->at(i).getObjCurrGridLoc().x << " " << E->at(i).getObjCurrGridLoc().y << endl;
             cout << E->at(i).getObjNewGridLoc().x << " " << E->at(i).getObjNewGridLoc().y << endl;
         }

         //if (!utilFunc.isSameGridLoc(E->at(i).getObjOldGridLoc(), E->at(i).getObjCurrGridLoc()))
         if (!utilFunc.isSameGridLoc(E->at(i).getObjOldGridLoc(), E->at(i).getObjNewGridLoc()))
         {
             vecref.updateVecref(E->at(i).getObjOldGridLoc().x, E->at(i).getObjOldGridLoc().y, '_');
             //vecref.updateVecref(E->at(i).getObjCurrGridLoc().x, E->at(i).getObjCurrGridLoc().y, 'E');
             vecref.updateVecref(E->at(i).getObjNewGridLoc().x, E->at(i).getObjNewGridLoc().y, 'E');
         }
    }

    if (!P->getIsProjDead())
    {
        if (vecref.getvecpos(P->getArrowLoc().x, P->getArrowLoc().y).print_unit() == '#')
            P->setIsProjDead(true);

        for (int i = 0; i < E->size(); i++)
        {
            if (utilFunc.isSameGridLoc(E->at(i).getObjNewGridLoc(), P->getArrowLoc()))
            {
                E->at(i).setIsObjDead(true);
                P->setIsProjDead(true);

                //vecref.updateVecref(P->getObjOldGridLoc().x, P->getObjOldGridLoc().y, '_');
                //vecref.updateVecref(E->at(i).getObjOldGridLoc().x, E->at(i).getObjOldGridLoc().y, '_');
            }
        }
    }

    if (canTakeAction)
    {
        //cout << "here01" << endl;
        cout << P->getObjCurrGridLoc().x << " " << P->getObjCurrGridLoc().y << endl;
        vecref.display2DVec();

    }
    //vecref.display2DVec();
    //system("cls");
    plyActs = {false, false, false, false, false};
    canTakeAction = false;
    actionInProgress = false;

    cleanEnemyList();
    cleanPlayerList();
    cleanProjectileList();


    glutPostRedisplay();
}


void mouse(int btn, int state, int x, int y){

    switch(btn){
        case GLUT_LEFT_BUTTON:

        if(state==GLUT_DOWN){

              GetOGLPos(x,y);
            }
            break;


      case GLUT_RIGHT_BUTTON:

        if(state==GLUT_DOWN){

              GetOGLPos(x,y);
            }
            break;
    }
     glutPostRedisplay();
};
//------------------------------------------------------------------------------------
//this may need to go into player class
void updatepos(int x, int y){//AS this will update position 0 to the current position of the player
         loctrackx[1] = P->getPlayerLoc().x;
         if (loctrackx[0] != loctrackx[1]){
            swap(loctrackx[0], loctrackx[1]);
         }
         loctracky[1] = P->getPlayerLoc().y;
         if (loctracky[0] != loctracky[1]){
            swap(loctracky[0], loctracky[1]);
         }
}
//------------------------------------------------------------------------------------

void displayloctrack(){ // prints to screen the coordinates of the player and the array tracking him
    //this will probably break later
         cout<< P->getPlayerLoc().x<< " "<<P->getPlayerLoc().y;
         cout << " | loctrackx: ";
         Print(loctrackx);
         cout << " | loctracky: ";
         Print(loctracky);
         cout << endl;
}

void checkwallcollision() {
    for (int i = 0; i < wallcount; i++){
        //if(P->playerCollision(W[wallcount].GetWallLoc.x,W[wallcount].GetWallLoc.y))break;
    }
}

//when the enemies move direction up in the vector they temporarly disapear unitl the player takes another action
//if they are right in front of each other this may cause issues later
bool annoying = false;
void Specialkeys(int key, int x, int y)
{

    // Your Code here
    switch(key)
    {
    case GLUT_KEY_UP:

         keysPressed.moveUp = true;
         plyActs.moveUp = true;
        canTakeAction = true;
        annoying = false;
    break;

    case GLUT_KEY_DOWN:

         keysPressed.moveDown = true;
         plyActs.moveDown = true;
        canTakeAction = true;
    break;

    case GLUT_KEY_LEFT:

         keysPressed.moveLeft = true;
         plyActs.moveLeft = true;
        canTakeAction = true;
    break;

    case GLUT_KEY_RIGHT:

         keysPressed.moveRight = true;
        plyActs.moveRight = true;
        canTakeAction = true;
    break;

   }
  glutPostRedisplay();
}


/* Program entry point */

int main(int argc, char *argv[])
{
    //cout << "here" << endl;

   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize (800, 800);                //window screen
   glutInitWindowPosition (100, 100);            //window position
   glutCreateWindow ("Maze");                    //program title
   init(1);


   queue < GridLoc > tempRetSolution;
   queue < string > tempStrSol;
   utilityFunctions uFunc;
   vecref.pathFinding({1, 12}, {10, 10}, tempRetSolution);
   uFunc.displayGLQueue(tempRetSolution);
   vecref.convertQueueGLtoString(tempRetSolution, tempStrSol);
   uFunc.displayStrQueue(tempStrSol);
   glutDisplayFunc(display);                     //callback function for display
   glutReshapeFunc(resize);                      //callback for reshape
   glutKeyboardFunc(key);                        //callback function for keyboard
   glutSpecialFunc(Specialkeys);
   glutMouseFunc(mouse);
   glutIdleFunc(idle);
   glutMainLoop();

   return EXIT_SUCCESS;
}

void pathFindToPlayer(GridLoc startPos, queue <string> &retPath)
{
    //utilityFunctions uFunc;
    queue <GridLoc> tempGLPath;
    queue <string> tempStrPath;

    vecref.pathFinding(startPos, P->getObjCurrGridLoc(), tempGLPath);
    vecref.convertQueueGLtoString(tempGLPath, tempStrPath);

    retPath = tempStrPath;
}

void clearPlayerList()
{
    if (P != NULL)
        delete P;
    P = NULL;
}

void clearEnemyList()
{
    if (E != NULL)
        delete E;
    E = NULL;
}

void clearWallList()
{
    if (W != NULL)
        delete W;
    W = NULL;
}

void clearProjectileList()
{
    if(!P->getIsProjDead())
        P->setIsProjDead(true);
}

void cleanPlayerList()
{
    if(P->getIsObjDead())
    {
        vecref.updateVecref(P->getObjCurrGridLoc().x, P->getObjCurrGridLoc().y, '_');
        clearProjectileList();
        clearPlayerList();
        cout << "Player dead exit game" << endl;
        //exit(0); //This is just a placeholder
    }
}

void cleanEnemyList()
{

    templateFunctions tFunc;
    for (int i = 0; i < E->size(); i++)
    {
        if (E->at(i).getIsObjDead())
        {
            vecref.updateVecref(E->at(i).getObjNewGridLoc().x, E->at(i).getObjNewGridLoc().y, '_');
            tFunc.removeVectorPointerElement(E, i);
            cout << E->size() << endl;
        }
    }
}

void cleanWallList()
{
    templateFunctions tFunc;
    for (int i = 0; i < W->size(); i++)
    {
        if (W->at(i).getIsObjDead())
        {
            vecref.updateVecref(W->at(i).getObjCurrGridLoc().x, W->at(i).getObjCurrGridLoc().y, '_');
            tFunc.removeVectorPointerElement(W, i);
        }
    }
}

void cleanProjectileList()
{
    if(P->getIsProjDead())
        P->setIsProjDead(true);
}

void resetPlayerList()
{
    clearPlayerList();
    P = new Player();
}

void resetEnemyList()
{
    clearEnemyList();
    E = new vector < Enemies >();
}

void resetWallList()
{
    clearEnemyList();
    W = new vector < wall >();
}

void clearMaze()
{
    if (M != NULL)
        delete W;
    M = NULL;
}

void resetMaze()
{
    clearMaze();
    M = new Maze();
}

void resetPtrObjects()
{
    resetPlayerList();
    resetEnemyList();
    resetWallList();
    resetMaze();
}
