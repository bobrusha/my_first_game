#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"glaux.lib")
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <GL/glut.h>
//#include <tchar.h>

namespace myglaux 
{
#include <GL/GLAux.h>
}
//----------------------------------------------------

void LoadTextures( unsigned int* textures)
{
	memset(textures, 0, sizeof(textures));
	for (int i = 0; i<10; i++)
	{
			std::cout<<textures[i];
	}
	myglaux::AUX_RGBImageRec *texture1= myglaux::auxDIBImageLoadA("grass.bmp");
    glGenTextures(1, &textures[0]);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	std::cout<<" "<<std::endl;
    for (int i = 0; i<10; i++)
	{
			std::cout<<textures[i]<<" ";
	}

	myglaux::AUX_RGBImageRec *texture2= myglaux::auxDIBImageLoadA("hero.bmp");
    glGenTextures(2, &textures[1]);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2->sizeX, texture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2->data);

	std::cout<<" "<<std::endl;
	for (int i = 0; i<10; i++)
	{
			std::cout<<textures[i]<<" ";
	}

	myglaux::AUX_RGBImageRec *texture3= myglaux::auxDIBImageLoadA("bomb.bmp");
    glGenTextures(3, &textures[2]);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture3->sizeX, texture3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture3->data);

	std::cout<<" "<<std::endl;
	for (int i = 0; i<10; i++)
	{
			std::cout<<textures[i]<<" ";
	}

	myglaux::AUX_RGBImageRec *texture4= myglaux::auxDIBImageLoadA("brick.bmp");
    glGenTextures(4, &textures[3]);
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture4->sizeX, texture4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture4->data);
	
	std::cout<<" "<<std::endl;
	for (int i = 0; i<10; i++)
	{
			std::cout<<textures[i]<<" ";
	}
	myglaux::AUX_RGBImageRec *texture5= myglaux::auxDIBImageLoadA("exit.bmp");
    glGenTextures(5, &textures[4]);
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture5->sizeX, texture5->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture5->data);
	
	myglaux::AUX_RGBImageRec *texture6= myglaux::auxDIBImageLoadA("beaton.bmp");
    glGenTextures(6, &textures[5]);
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture6->sizeX, texture6->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture6->data);
	
	std::cout<<" "<<std::endl;
	for (int i = 0; i<10; i++)
	{
			std::cout<<i<<" ";
	}
	std::cout<<" "<<std::endl;

	for (int i = 0; i<10; i++)
	{
			std::cout<<textures[i]<<" ";
	}
}

#endif