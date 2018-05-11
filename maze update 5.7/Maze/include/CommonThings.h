/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#ifndef COMMONTHINGS_H
#define COMMONTHINGS_H

#include<GL/gl.h>
#include<SOIL.h>

#include<iostream>
//#include <Timer.h>

using namespace std;

class Timer;

typedef struct
{
  float x;
  float y;
}loc;

typedef struct
{
  float width;
  float height;
}cartRealDim2d;

typedef struct
{
  int x;
  int y;
}GridLoc;

typedef struct
{
  int width;
  int height;
}gridSize;

typedef struct
{
  float width;
  float height;
}worldSize;

typedef struct
{
    bool moveUp;
    bool moveDown;
    bool moveLeft;
    bool moveRight;
    bool shoot;
}playerActions;

static GLuint TextureLoader(char* FileName)
{
   GLuint tex;
   unsigned char* image;
   int width, height;

   glGenTextures(1, &tex);

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, tex);
    image = SOIL_load_image(FileName, &width, &height, 0, SOIL_LOAD_RGBA);

    if(!image) {cout<<" Cannot Find "<<FileName<<" image:<<endl";}
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    return tex;
}

template <class T>
void enemyclear(T* a, int n){
    /*
    for(int i=0;i<n;i++){
        a[i].live=0;
    }
    */
    a->clear();
}
template <class T>
void wallclear(T* a, int n){
    /*
    for(int i=0;i<n;i++){
        a[i].liveWall=0;
    }
    */
    a->clear();
}

#endif // COMMONTHINGS_H

