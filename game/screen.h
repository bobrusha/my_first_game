#ifndef _SCREEN_H_
#define _SCREEN_H_
#include <list>
#include "bomb.h"
#include "texture.h"

using namespace std;

int step = 40;
int calculateIndex (int x)
{
	x += (step - 10);
	x /= step;
	return x;
}

class screen
{
public:
	
	int arr [13][15];

	//int w, h;
	// 0 - free
	// 1 - hero
	// 2 - obj
	// 3 - enemy
	// 4 - beaton
	// 5 - bonus
	// 6 - exit


	void clearScreen()
	{
		for (int i = 2; i < 12; i++)
			for ( int j=0; j<14; j++)
				arr[i][j] = 0;
	}
	screen ()
	{
		clearScreen();
	}

	/*
	screen(screen& tmp)
	{
		for (int i = 0; i < 13; i++)
			for ( int j=0; j<15; j++)
				arr[i][j] = tmp.arr[i][j];
	}
	*/
	void Draw(int w, int h, unsigned int texture)
	{
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, texture);

		glColor3f( 1.0, 1.0, 1.0);
		glLineWidth ( 2.0 );		
		glBegin (GL_QUADS);
			glTexCoord2f ( 0.0, 0.0);
			glVertex2i( 0 , 0);
			
			glTexCoord2f ( 0.0, 1.0);
			glVertex2i( 0 , h);

			glTexCoord2f ( 1.0, 1.0);
			glVertex2i( w , h);

			glTexCoord2f ( 1.0, 0.0);
			glVertex2i( w , 0);
			
		glEnd();

		glFlush();
	}
};
#endif