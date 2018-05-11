/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <Enemies.h>
#include <iostream>
#include <Timer.h>
#include <enemyai.h>

using namespace std;



//Timer *T1 = new Timer();                             // Set Timer for animation
Enemies::Enemies()
{
    //ctor
    enmLoc.x=0;
    enmLoc.y=0;

    xmax =1;
    ymax =0.25;
    xmin =0;
    ymin =0;
    up= down = left=right=false;
    live = true;

    objectTimer = new Timer();
    objectDirectionFaced = 6;
    canObjectAct = false;
    isObjectActing = false;

    objectGenericCounter = 0;
    needDirectionChange = false;

}

Enemies::~Enemies()
{
    //dtor
    delete objectTimer;
}

void Enemies::initEnm(int grid,int numFrames, char * FileName)
{
    gridSize = grid;
    frames = numFrames;
    xmax =1/(float)frames;
    objectTimer->Start();
    t = (float)(2.0/grid)/frames;
    unitWidth = (float)2.0/gridSize;
    enmTex = TextureLoader(FileName);
}


void Enemies::drawEnemy()
{
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,enmTex);


    glPushMatrix();
    if(!needDirectionChange)
        animate();
    else
    {

    }
    glTranslatef(enmLoc.x,enmLoc.y,0.0);

    glScaled(1.0/(float)gridSize,1.0/(float)gridSize,1);

    glBegin(GL_POLYGON);
        glTexCoord2f(xmin,ymin);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(xmax,ymin);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(xmax,ymax);
        glVertex3f(-1,-1,0.0f);

        glTexCoord2f(xmin,ymax);
        glVertex3f(1,-1,0.0f);
     glEnd();
     glPopMatrix();
}

void Enemies::placeEnemy(int x, int y)
{
    unitWidth = 2.0/gridSize;
    x+=1;
    y+=1;
    enmLoc.x =  -1-unitWidth/2+(unitWidth)*x;
    enmLoc.y =  -1-unitWidth/2+(unitWidth)*y;

    setObjCurrGridLoc({x, y});
    setObjCurrRealLoc(enmLoc);
}

void Enemies::moveEnemy(string dir)
{
  if(moveDis<=0){
   if(dir=="up"){up=true; down=left=right=false;}
   else if(dir=="down"){down=true; up=left=right=false;}
   else if(dir=="left"){left=true; down=up=right=false;}
   else if(dir=="right"){right=true; down=left=up=false;}
   else{up=left=right=false;}
    }
}

void Enemies::animate()
{

if(moveDis < unitWidth)
{

if(objectTimer->GetTicks()<1000)
   {

if(up)
   {
       if(enmLoc.y< 1-unitWidth/2)
        {
            enmLoc.y += t;
         }   moveDis +=t;

        xmin +=1/(float)frames;
        xmax +=1/(float)frames;
        ymin =0.0;
        ymax =0.25;
        if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
            }
    }

  else if(down)
   {
         if(enmLoc.y > -1+unitWidth/2)
           {
              enmLoc.y -= t;
           }  moveDis +=t;

            xmin +=1/(float)frames;
            xmax +=1/(float)frames;
            ymin =0.25;
            ymax =0.5;

            if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
            }

   }
   else if(left)
   {
       if(enmLoc.x>-1+unitWidth/2)
        {
            enmLoc.x -= t;
         }   moveDis +=t;

        xmin +=1/(float)frames;
        xmax +=1/(float)frames;
        ymin =0.75;
        ymax =1.0;

        if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
            }
   }

   else if(right)
   {
       if(enmLoc.x<1-unitWidth/2)
          {
              enmLoc.x += t;
           }   moveDis +=t;

            xmin +=1/(float)frames;
            xmax +=1/(float)frames;
            ymin =0.5;
            ymax =0.75;

            if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
              }
     }

  }else objectTimer->Reset();
}
 else {moveDis =0;down=up=left=right=false; }
}


GridLoc Enemies::getEnemyLoc()
{
   GridLoc val;
   val.x = (int)(ceil((enmLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((enmLoc.y +(1-unitWidth))/unitWidth));

    return val;
}

bool Enemies::getIsObjectActing()
{
    return isObjectActing;
}

void Enemies::updateEnemyVecPos(vectorstuff foo, int a, int b){
    /*if((enemyloctrackx[0] != enemyloctrackx[1]) || (enemyloctracky[0] != enemyloctracky[1])){

    }*/
    enemyloctrackx[1] = a;
    enemyloctracky[1] = b;
    if (enemyloctrackx[0] != enemyloctrackx[1]){
            swap(enemyloctrackx[0], enemyloctrackx[1]);
         }
    if (enemyloctracky[0] != enemyloctracky[1]){
            swap(enemyloctracky[0], enemyloctracky[1]);
         }
    //cout << a << " " << b << endl;
    //cout << enemyloctrackx[0] << " " << enemyloctrackx[1] << " " << enemyloctracky[0] << " " << enemyloctracky[1] << endl;


}

void Enemies::enemyupdatepos(int x, int y){//AS this will update position 0 to the current position of the player
         enemyloctrackx[0] = getEnemyLoc().x;
         enemyloctrackx[1] = getEnemyLoc().x;
         enemyloctracky[0] = getEnemyLoc().y;
         enemyloctracky[1] = getEnemyLoc().y;
}

void Enemies::objectAction(vectorstuff bash, units curenemypos, vector<units> playerpos)
{
    if (canObjectAct)
    {
        setObjOldGridLoc(getEnemyLoc()); //store old location
        setObjOldRealLoc(enmLoc); //in case it needs to be reverted to

        //canObjectAct = false;
        enemyai moveai;
        /*
        units themove = moveai.returnSolution(bash.mastervec, curenemypos, playerpos);
        cout << "Enemy current location: x."<< getEnemyLoc().x << "   y." <<getEnemyLoc().y << endl;
        cout << "The AI move: x."<< themove.x << "   y." << themove.y << endl << endl;
        cout << "front of solution que: "<< moveai.solutionQueue.front().x << "   " << moveai.solutionQueue.front().y;
        */

        units themove;
        //themove.set_unit(0, 0 '0');
        themove.set_unit(0, 0, '0');

        if(getEnemyLoc().x == themove.x){
            objectGenericCounter = 2;
            /*
            if(getEnemyLoc().y == themove.y + 1){
                cout << "Enemy moved up." << endl;
                objectGenericCounter = 1;
            }
            else if(getEnemyLoc().y == themove.y - 1){
                cout << "Enemy moved down." << endl;
                objectGenericCounter = 3;
            }
        }

        else if(getEnemyLoc().y == themove.y){
            if(getEnemyLoc().x == themove.x + 1){
                cout << "Enemy moved right." << endl;
                objectGenericCounter = 0;
            }
            else if(getEnemyLoc().x == themove.x - 1){
                cout << "Enemy moved left." << endl;
                objectGenericCounter = 2;
            }
            */
        }
        else
            //cout << "something is not working right";
            objectGenericCounter = 2;

        switch (objectGenericCounter)
        {
            case 0:
                //if (objectDirectionFaced != 3)  //to change direction facing without moving
                moveEnemy("right");
                objectGenericCounter++;
                break;
            case 1:
                moveEnemy("up");
                objectGenericCounter++;
                break;
            case 2:
                moveEnemy("left");
                objectGenericCounter++;
                break;
            case 3:
                moveEnemy("down");
                objectGenericCounter++;
                break;
        }
        //objectGenericCounter++;

        //store the current locations
        setObjCurrRealLoc(enmLoc);
        setObjCurrGridLoc(getEnemyLoc());
    }


}

void Enemies::objectLogicAction(bool isBlockCollision)
{
    if (canObjectAct)
    {
        if (!isBlockCollision)
        {

        }
        else
        {
            //setObjCurrRealLoc(getObjOldRealLoc());
        }

        canObjectAct = false;
        isObjectActing = false;
        //classPlayerActions = {false, false, false, false, false};
    }
}


void Enemies::setActionStatus(bool inpCanAct)
{
    canObjectAct = inpCanAct;
}

void Enemies::changeDirection()
{

}

GridLoc Enemies::getObjCurrGridLoc()
{
    //return objCurrGridLoc;
    return getEnemyLoc();
}

GridLoc Enemies::getObjNewGridLoc()
{
    return objOldGridLoc;
}

GridLoc Enemies::getObjOldGridLoc()
{
    return objNewGridLoc;
}

void Enemies::setObjCurrGridLoc(GridLoc inpGridLoc)
{
    objCurrGridLoc = inpGridLoc;
}

void Enemies::setObjNewGridLoc(GridLoc inpGridLoc)
{
    objNewGridLoc = inpGridLoc;
}

void Enemies::setObjOldGridLoc(GridLoc inpGridLoc)
{
    objOldGridLoc = inpGridLoc;
}

loc Enemies::getObjCurrRealLoc()
{
    return objCurrRealLoc;
}

loc Enemies::getObjNewRealLoc()
{
    return objNewRealLoc;
}

loc Enemies::getObjOldRealLoc()
{
    return objOldRealLoc;
}

void Enemies::setObjCurrRealLoc(loc inpRealLoc)
{
    objCurrRealLoc = inpRealLoc;
    enmLoc = inpRealLoc;
}

void Enemies::setObjNewRealLoc(loc inpRealLoc)
{
    objNewRealLoc = inpRealLoc;
}

void Enemies::setObjOldRealLoc(loc inpRealLoc)
{
    objOldRealLoc = inpRealLoc;
}
