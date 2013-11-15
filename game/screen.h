#ifndef _SCREEN_H_
#define _SCREEN_H_
#include "texture.h"

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
	int arr [12][12];
	int k;
	// 0 - free
	// 1 - hero
	// 2 - obj
	// 3 - enemy
	// 4 - 
	//  - bonus
	//  - exit
	void clearScreen()
	{
		for (int i = 0; i < k+2; i++)
			for ( int j=0; j<k; j++)
				arr[i][j] = 0;
		for (int i = 2; i < k+2; i=i+2)
			for ( int j=2; j<k; j=j+2)
			{
				arr[i][j] = 4;
			}
		
		for (int i = 0; i < k+2; i++)
			arr[i][0] = 4;
		for (int i = 0; i < k+2; i++)
			arr[i][k+1] = 4;
		for (int j = 0; j < k+2; j++)
			arr[0][j] = 4;
		for (int j = 0; j < k+2; j++)
			arr[k+1][j] = 4;
	}
	
	screen( int W, int brdr, int stp): k((W - brdr)/stp)
	{
		clearScreen();
	}
	
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