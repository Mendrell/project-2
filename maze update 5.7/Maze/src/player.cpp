/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018

 this is the player class
 This is what the player controls
 Movement is turn based
 Player can fire a projectile
 This class also handles the projectile

 */

#include <Player.h>
#include <Timer.h>
#include <vectorstuff.h>0

//Timer *T = new Timer();                             // Set the Timer for animation

Player::Player()
{
    //ctor
    playerDir = "down";
    arrowLoc.x = 0.2;
    arrowLoc.y =0.5;
    arrAngle =0;
    arrowStatus = false;
    livePlayer = true;

    //objectTimer = new Timer();
    objectTimer = NULL;
    objectDirectionFaced = 6;
    canObjectAct = false;
    isObjectActing = false;
    classPlayerActions = {false, false, false, false, false};
    hasAmmo = false;
}

Player::~Player()
{
    //dtor
    if (objectTimer != NULL)
        delete objectTimer;
}

void Player::drawArrow()
{

if(arrowStatus){//this is where i need to update the location of the arrow in the vector
   glColor3f(1.0,1.0,1.0);

     if(objectTimer->GetTicks()>10)
        {
            if(arrowLoc.x>=-1 && arrowLoc.x<=1)
                arrowLoc.x += t*arrXdir;
            else arrowStatus = false;
            if(arrowLoc.y>=-1 && arrowLoc.y<=1)
                arrowLoc.y += t*arrYdir;
            else arrowStatus = false;
           objectTimer->Reset();
        }
    glTranslatef(arrowLoc.x ,arrowLoc.y,0.0);
    glRotated(arrAngle,0,0,1);
    glBindTexture(GL_TEXTURE_2D,arrowTex);
    glScaled(1.0/(float)gridSize,1.0/(float)gridSize,1);

    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);

        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);
     glEnd();
  }
}

void Player::shootArrow()//this is where i need to intitiate the arrow in the vector
{   if(livePlayer){
    if(!arrowStatus)
    {
      arrowStatus=true;

      if(strcmp(playerDir, "left")==0)
      {
        arrAngle = -90;
        arrXdir=-1;
        arrYdir=0;
        arrowLoc.x = plyLoc.x-unitWidth/2;
        arrowLoc.y = plyLoc.y;
      }
      if(strcmp(playerDir, "right")==0)
      {
        arrAngle =90;
        arrXdir=1;
        arrYdir=0;
        arrowLoc.x = plyLoc.x+unitWidth/2;
        arrowLoc.y = plyLoc.y;
      }
      if(strcmp(playerDir, "up")==0)
      {
        arrXdir=0;
        arrYdir=1;
        arrAngle =180;

        arrowLoc.y = plyLoc.y+unitWidth/2;
        arrowLoc.x = plyLoc.x;
      }
      if(strcmp(playerDir, "down")==0)
      {
        arrXdir=0;
        arrYdir=-1;
        arrAngle= 0;

        arrowLoc.y = plyLoc.y-unitWidth/2;
        arrowLoc.x = plyLoc.x;
      }
     }
    }
}


void Player::loadArrowImage(char* fileName)
{
    arrowTex = TextureLoader(fileName);
}

GridLoc Player::getArrowLoc()
{
   GridLoc val;

    val.x = (int)(ceil((arrowLoc.x +(1-unitWidth))/unitWidth));
    val.y = (int)(ceil((arrowLoc.y +(1-unitWidth))/unitWidth));

   return val;
}


void Player::drawplayer()
{
    if(livePlayer)
    {

   glColor3f(1.0,1.0,1.0);

   glTranslatef(plyLoc.x ,plyLoc.y,0.0);

    glBindTexture(GL_TEXTURE_2D,plyTex);
    glScaled(1.0/(float)gridSize,1.0/(float)gridSize,1);


    glBegin(GL_QUADS);
        glTexCoord2f(xmin,ymin);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(xmax,ymin);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(xmax,ymax);
        glVertex3f(-1,-1,0.0f);

        glTexCoord2f(xmin,ymax);
        glVertex3f(1,-1,0.0f);
     glEnd();
    }
}


void Player::initPlayer(int gSize,int frams, char *FileName)
{

    objectTimer = new Timer();

    frames = frams;
    gridSize = gSize;

    xmax =1/(float)frames;
    ymax =0.25;
    xmin =0;
    ymin =0;

    unitWidth = (float)2/gridSize;
    stepsPerMove = frames;

    objectTimer->Start();
    plyLoc.x= -unitWidth;
    plyLoc.y= -unitWidth;

    t= unitWidth/stepsPerMove;

    plyTex = TextureLoader(FileName);
}


void Player::placePlayer(int x, int y)
{
    plyLoc.x =  converter(x,y).x;
    plyLoc.y =  converter(x,y).y;

    setObjCurrRealLoc(plyLoc);
    setObjCurrGridLoc({x, y});
    setObjOldRealLoc(getObjCurrRealLoc());
    setObjOldGridLoc(getObjCurrGridLoc());
}

void Player::movePlayer(char* dir)
{
      if(strcmp(dir, "left")==0)
   {     playerDir = "left";
        if(objectTimer->GetTicks()>10)
        {
            if(plyLoc.x>-1+unitWidth/2)
                plyLoc.x -= t;
            if(xmax>=1){
                xmax =1/(float)frames;
                xmin =0;
            }
            xmin += 1/(float)frames;
            xmax += 1/(float)frames;
            ymin =0.75;
            ymax =1.0;
            objectTimer->Reset();
        }
   }

   else if(strcmp(dir, "right")==0)
   {
        playerDir = "right";
        if(objectTimer->GetTicks()>1)
        {
            if(plyLoc.x<1-unitWidth/2)
            plyLoc.x += t;

            if(xmax>=1){
                xmax =1/(float)frames;
                xmin =0;
            }
            xmin +=1/(float)frames;
            xmax +=1/(float)frames;
            ymin =0.5;
            ymax =0.75;
            objectTimer->Reset();
        }
   }

   else if(strcmp(dir, "up")==0)
   {
        playerDir = "up";
        if(objectTimer->GetTicks()>1)
        { if(plyLoc.y< 1-unitWidth/2)
            plyLoc.y += t;
            if(xmax>=1){
                xmax =1/(float)frames;
                xmin =0;
            }
            xmin +=1/(float)frames;
            xmax +=1/(float)frames;

            ymin =0.25;
            ymax =0.50;

            objectTimer->Reset();
        }
   }

   else if(strcmp(dir, "down")==0)
   {
         playerDir = "down";
        if(objectTimer->GetTicks()>1)
        {
            if(plyLoc.y > -1+unitWidth/2)
                plyLoc.y -= t;
            if(xmax>=1){
                xmax =1/(float)frames;
                xmin =0;
            }
            xmin +=1/(float)frames;
            xmax +=1/(float)frames;
            ymin =0.0;
            ymax =0.25;
            objectTimer->Reset();
        }
   }
}

GridLoc Player::getPlayerLoc()
{
   GridLoc val;

   val.x = (int)(ceil((plyLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((plyLoc.y +(1-unitWidth))/unitWidth));

   return val;

}

loc Player::converter(int x, int y)
{
  loc val;
        x+=1;
        y+=1;

       val.x = -1-unitWidth/2+(unitWidth)*x;
       val.y = -1-unitWidth/2+(unitWidth)*y;
       return val;
}

bool Player::getIsObjectActing()
{
    return isObjectActing;
}

void Player::objectAction()
{
    if (canObjectAct)
    {
        //canObjectAct = false;
        isObjectActing = true;
        setObjOldRealLoc(getObjCurrRealLoc());
        setObjOldGridLoc(getObjCurrGridLoc());
        if (classPlayerActions.moveUp && !classPlayerActions.moveDown)
        {
			//setObjOldRealLoc(getObjCurrRealLoc());
			//setObjOldGridLoc(getObjCurrGridLoc());
            movePlayer("up");
        }
        else if (classPlayerActions.moveDown && !classPlayerActions.moveUp)
        {
            //setObjOldRealLoc(getObjCurrRealLoc());
            movePlayer("down");
        }
        else if (classPlayerActions.moveLeft && !classPlayerActions.moveRight)
        {
			//setObjOldRealLoc(getObjCurrRealLoc());
            movePlayer("left");
        }
        else if (classPlayerActions.moveRight && !classPlayerActions.moveLeft)
        {
            //setObjOldRealLoc(getObjCurrRealLoc());
            movePlayer("right");
        }
        else if (classPlayerActions.shoot)
        {
            //setObjOldRealLoc(getObjCurrRealLoc());
            if (getHasAmmo())
                shootArrow();
        }
        //isObjectActing = false;
        //classPlayerActions = {false, false, false, false, false};
        setObjCurrRealLoc(getObjCurrRealLoc());
        setObjCurrGridLoc(getObjCurrGridLoc());
    }
}

void Player::objectLogicAction(bool isBlockCollision)
{
    if (canObjectAct)
    {
        if (!isBlockCollision)
        {

        }
        else
        {
            setObjCurrRealLoc(getObjOldRealLoc());
            setObjCurrGridLoc(getObjOldGridLoc());
        }

        canObjectAct = false;
        isObjectActing = false;
        classPlayerActions = {false, false, false, false, false};
    }
}

void Player::setActionStatus(playerActions inpPlayAct, bool inpCanAct)
{
    classPlayerActions = inpPlayAct;
    canObjectAct = inpCanAct;
}

bool Player::playerCollision(int x, int y)
{
    float Xmin = converter(x,y).x-unitWidth/2;
    float Xmax = converter(x,y).x+unitWidth/2;
    float Ymin = converter(x,y).y-unitWidth/2;
    float Ymax = converter(x,y).y+unitWidth/2;

    if( playerDir == "up"){
       if(plyLoc.y> Ymin-unitWidth/2 && plyLoc.y < Ymax && plyLoc.x> Xmin-unitWidth/4 && plyLoc.x< Xmax+unitWidth/4 )
       {
          collision =true;
          return true;
       }
    }

     if(playerDir == "down"){
        if( plyLoc.y > Ymax && plyLoc.y< Ymax+unitWidth && plyLoc.x> Xmin-unitWidth/4 && plyLoc.x< Xmax+unitWidth/4)
        {   collision =true;
            return true;
        }
    }

    if(playerDir == "left"){
        if( plyLoc.x > Xmax && plyLoc.x < Xmax+unitWidth && plyLoc.y> Ymin-unitWidth/4 && plyLoc.y< Ymax+unitWidth/4)
        {   collision =true;
            return true;
        }
    }

    if(playerDir == "right"){
        if(plyLoc.x > Xmin-unitWidth/2 && plyLoc.x < Xmax && plyLoc.y> Ymin-unitWidth/4 && plyLoc.y< Ymax+unitWidth/4 )
       {   collision =true;
            return true;
      }
    }

 collision = false;
 return false;
}


GridLoc Player::getObjCurrGridLoc()
{
    //return objCurrGridLoc;
    return getPlayerLoc();
}

GridLoc Player::getObjNewGridLoc()
{
    return objNewGridLoc;
}

void Player::setObjCurrGridLoc(GridLoc inpGridLoc)
{
    objCurrGridLoc = inpGridLoc;
}

void Player::setObjNewGridLoc(GridLoc inpGridLoc)
{
    objNewGridLoc = inpGridLoc;
}

GridLoc Player::getObjOldGridLoc()
{
    return objOldGridLoc;
}

void Player::setObjOldGridLoc(GridLoc inpGridLoc)
{
    objOldGridLoc = inpGridLoc;
}


loc Player::getObjCurrRealLoc()
{
    return plyLoc;
}

loc Player::getObjNewRealLoc()
{
    return objNewRealLoc;
}

loc Player::getObjOldRealLoc()
{
    return objOldRealLoc;
}

void Player::setObjCurrRealLoc(loc inpRealLoc)
{
    objCurrRealLoc = inpRealLoc;
    plyLoc = inpRealLoc;
}

void Player::setObjNewRealLoc(loc inpRealLoc)
{
    objNewRealLoc = inpRealLoc;
}

void Player::setObjOldRealLoc(loc inpRealLoc)
{
    objOldRealLoc = inpRealLoc;
}

bool Player::getIsObjDead()
{
    return !livePlayer;
}

void Player::setIsObjDead(bool inpBool)
{
    livePlayer = !inpBool;
}

bool Player::getIsProjDead()
{
    return !arrowStatus;
}

void Player::setIsProjDead(bool inpBool)
{
    arrowStatus = !inpBool;
}

bool Player::getHasAmmo()
{
    return hasAmmo;
}

bool Player::setHasAmmo(bool inpBool)
{
    hasAmmo = inpBool;
}

void Player::timer()
{

}
