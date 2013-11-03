#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"glaux.lib")

#include <time.h>
#include <stdio.h>
#include <GL/glut.h>
#include <tchar.h>

namespace myglaux 
{
#include <GL/GLAux.h>
}
//----------------------------------------------------

void LoadTextures( unsigned int* textures)
{
    myglaux::AUX_RGBImageRec *texture1= myglaux::auxDIBImageLoadA("1.bmp");
    glGenTextures(1, &textures[0]);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
}

#endif