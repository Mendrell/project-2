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

    //objectTimer = new Timer();
    objectTimer = NULL;

    objectDirectionFaced = 6;
    canObjectAct = false;
    isObjectActing = false;

    objectGenericCounter = 0;
    needDirectionChange = false;

}

Enemies::~Enemies()
{
    //dtor
    if (objectTimer != NULL)
        delete objectTimer;
}

void Enemies::initEnm(int grid,int numFrames, char * FileName)
{
    objectTimer = new Timer();
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
    setObjOldGridLoc(getObjCurrGridLoc());
    setObjOldRealLoc(getObjCurrRealLoc());
    setObjNewGridLoc(getObjCurrGridLoc());
    setObjNewRealLoc(getObjCurrRealLoc());
}



void Enemies::updateEnemyVecPos(vectorstuff foo, int a, int b){
    /*if((enemyloctrackx[0] != enemyloctrackx[1]) || (enemyloctracky[0] != enemyloctracky[1])){

    }*/
    enemyloctrackx[1] = a;
    enemyloctracky[1] = b;
    int temp1, temp2, temp3, temp4;

    if (enemyloctrackx[0] != enemyloctrackx[1]){

            swap(enemyloctrackx[0], enemyloctrackx[1]);
         }
    if (enemyloctracky[0] != enemyloctracky[1]){
            swap(enemyloctracky[0], enemyloctracky[1]);
         }
    if((enemyloctrackx[0] != enemyloctrackx[1]) || (enemyloctracky[0] != enemyloctracky[1])){
        updateenemyvecref(foo, enemyloctrackx[1], enemyloctracky[1], enemyloctrackx[0], enemyloctracky[0], 'E');
    }



}

void Enemies::enemyupdatepos(int x, int y){//AS this will update position 0 to the current position of the player
         enemyloctrackx[0] = getEnemyLoc().x;
         enemyloctrackx[1] = getEnemyLoc().x;
         enemyloctrackxbar[0]= getEnemyLoc().x;
         enemyloctracky[0] = getEnemyLoc().y;
         enemyloctracky[1] = getEnemyLoc().y;
         enemyloctrackybar[0]= getEnemyLoc().x;
}

void Enemies::updateenemyvecref(vectorstuff temp, int old_x, int old_y, int new_x, int new_y, char type){
    //temp.updateVecref(old_x, old_y, '_');
   // cout << "almost there \n";
    //system("pause");
    units temp1;
    temp1.set_unit(old_x,old_y,'_');
    units temp2;
    temp2.set_unit(new_x,new_y, type);
    temp.temp1 = temp1;
    temp.temp2 = temp2;


    //temp.mastervec[old_x][old_y] = temp1;
    //temp.mastervec[new_x][new_y] = temp2;


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
    /*
   GridLoc val;
   val.x = (int)(ceil((enmLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((enmLoc.y +(1-unitWidth))/unitWidth));

    return val;
    */

    return realToGrid(enmLoc);
}

bool Enemies::getIsObjectActing()
{
    return isObjectActing;
}



void Enemies::objectAction(vectorstuff bash, units curenemypos, vector<units> playerpos)
{
    //setObjOldGridLoc(getEnemyLoc()); //store old location
    //setObjOldRealLoc(enmLoc); //in case it needs to be reverted to
    setObjOldGridLoc(getObjNewGridLoc()); //store old location
    setObjOldRealLoc(getObjNewRealLoc()); //in case it needs to be reverted to
    if (canObjectAct)
    {
        string tempStrMove;
        queue < string > tempQueueMove;
        getObjTravelPath(tempQueueMove);
        if (!tempQueueMove.empty())
            tempStrMove = tempQueueMove.front();
        else
            tempStrMove = "stay";
        if (tempStrMove == "right")
        {
            objectGenericCounter = 0;
        }
        else if (tempStrMove == "up")
        {
            objectGenericCounter = 1;
        }
        else if (tempStrMove == "left")
        {
            objectGenericCounter = 2;
        }
        else if (tempStrMove == "down")
        {
            objectGenericCounter = 3;
        }
        else if (tempStrMove == "stay")
        {
            objectGenericCounter = 4;
        }

        loc tempLoc00;
        switch (objectGenericCounter)
        {
            case 0:
                //if (objectDirectionFaced != 3)  //to change direction facing without moving
                moveEnemy("right");
                tempLoc00 = getObjCurrRealLoc();
                tempLoc00.x += unitWidth;
                setObjNewRealLoc(tempLoc00);

                break;
            case 1:
                moveEnemy("up");
                tempLoc00 = getObjCurrRealLoc();
                tempLoc00.y += unitWidth;
                setObjNewRealLoc(tempLoc00);

                break;
            case 2:
                moveEnemy("left");
                tempLoc00 = getObjCurrRealLoc();
                tempLoc00.x -= unitWidth;
                setObjNewRealLoc(tempLoc00);

                break;
            case 3:
                moveEnemy("down");
                tempLoc00 = getObjCurrRealLoc();
                tempLoc00.y -= unitWidth;
                setObjNewRealLoc(tempLoc00);

                break;
            case 4:
                break;
            default:
                cout << "error in enemy action" << endl;
                break;
        }

    }
    //setObjCurrRealLoc(enmLoc);
    //setObjCurrGridLoc(getEnemyLoc());
    setObjCurrRealLoc(getObjNewRealLoc());
    setObjCurrGridLoc(getObjNewGridLoc());
}

void Enemies::objectLogicAction(bool isBlockCollision)
{
    if (canObjectAct)
    {
        if (!isBlockCollision)
        {
            queue < string > tempQueueMove;
            getObjTravelPath(tempQueueMove);
            if (!tempQueueMove.empty())
                tempQueueMove.pop();
            setObjTravelPath(tempQueueMove);
        }
        else
        {
            //setObjCurrRealLoc(getObjOldRealLoc());
            setObjNewRealLoc(getObjOldRealLoc());
            setObjNewGridLoc(getObjOldGridLoc());
            setObjCurrRealLoc(getObjOldRealLoc());
            setObjCurrGridLoc(getObjOldGridLoc());
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
    //return objNewGridLoc;
    return realToGrid(objNewRealLoc);
}

GridLoc Enemies::getObjOldGridLoc()
{
    return objOldGridLoc;
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

GridLoc Enemies::realToGrid(loc inpRealLoc)
{
    GridLoc val;
   val.x = (int)(ceil((inpRealLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((inpRealLoc.y +(1-unitWidth))/unitWidth));

    return val;
}

void Enemies::getObjTravelPath(queue<string>& retPath)
{
    retPath = objTravelPath;
}

void Enemies::setObjTravelPath(queue<string>inpPath)
{
    objTravelPath = inpPath;
}

