#ifndef _HERO_H
#define _HERO_H
#include "block.h"

class hero
{
public:
	int l, r, b, t, lives;
	bool inportal;

	hero (screen &scrn): l (10), r(50), b(370), t(410), lives (2), inportal(false) 
	{	
		scrn.arr[calculateIndex(b)][calculateIndex (l)] = 1;
	}

	void drawHero(unsigned int texture)
	{
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, texture);

		glEnable (GL_TEXTURE_2D);

		glLineWidth ( 2.0 );		
		glColor3f( 1.0, 1.0 , 1.0 );

		glBegin (GL_QUADS);

			glTexCoord2f ( 0.0, 0.0);
			glVertex2i( l , b);

			glTexCoord2i ( 0.0, 1.0);
			glVertex2i( l , t);

			glTexCoord2i ( 1.0, 1.0);
			glVertex2i( r , t);
			
			glTexCoord2i (1.0, 0.0);
			glVertex2i( r , b);

			glEnd();
		glFlush();

		if ( lives == 2)
		{
			glLineWidth ( 2.0 );		
			glColor3i( 0, 255 , 0 );
			glBegin (GL_LINE_STRIP);
			glVertex2i( 380, 10);
			glVertex2i( 380, 20);
			glVertex2i( 390, 20);
			glVertex2i( 390, 10);
			glVertex2i( 380, 10 );
			glEnd();
		}
		if (lives >= 1)
		{
			glLineWidth ( 2.0 );		
			glColor3i( 0, 255 , 0 );
			glBegin (GL_LINE_STRIP);
			glVertex2i( 360, 10);
			glVertex2i( 360, 20);
			glVertex2i( 370, 20);
			glVertex2i( 370, 10);
			glVertex2i( 360, 10 );
			glEnd();
		}
		glFlush();
	
	}

	// движение героя 
	//проверяем свободна ли клетка и если да пермещаем в неё героя
	//освобождаем предыдущую клетку
	void Damaged()
	{
		lives --;
	}
	void MoveL (screen &scrn, portal& quit)
	{
		
		if ( scrn.arr[calculateIndex(b)][calculateIndex (l - step)] == 3 )
		{
			Damaged();
		}
		else
			if ( scrn.arr[calculateIndex(b)][calculateIndex (l - step)] == 0 )
			{
				scrn.arr[calculateIndex(b)][calculateIndex (l)] = 0;
				l -= step;
				r -= step;
				scrn.arr[calculateIndex(b)][calculateIndex (l)] = 1; 
			}
			else 
				if (scrn.arr[calculateIndex(b)][calculateIndex (l - step)] == 6 && quit.up == true)
				{
					inportal = true;
				}
	}
	void MoveR (screen &scrn, portal& quit)
	{
		if ( scrn.arr[calculateIndex(b)][calculateIndex (l + step)] == 3 )
		{
			Damaged();
		}
		else
		{
			if (scrn.arr[calculateIndex(b)][calculateIndex (l + step)] == 0)
			{
				scrn.arr[calculateIndex(b)][calculateIndex (l)] = 0;
				l += step;
				r += step;
				scrn.arr[calculateIndex(b)][calculateIndex (l)] = 1; 
			}
			else 
				if (scrn.arr[calculateIndex(b)][calculateIndex (l + step)] == 6 && quit.up==true)
				{
					inportal = true;
				}
		}
	}
	void MoveD (screen &scrn, portal& quit)
	{
		if ( scrn.arr[calculateIndex(b - step)][calculateIndex (l)] == 3 )
		{
			Damaged();
		}
		else
		{
			if (scrn.arr[calculateIndex(b - step)][calculateIndex (l)] == 0 )
			{
				scrn.arr[calculateIndex(b)][calculateIndex (l)] = 0;
				b -= step;
				t -= step;
				scrn.arr[calculateIndex(b)][calculateIndex (l)] = 1; 
			}
			else 
				if (scrn.arr[calculateIndex(b -step)][calculateIndex (l)] == 6 && quit.up==true)
				{
					inportal = true;
				}
		}
	}
	void MoveU (screen &scrn, portal& quit)
	{
		if ( scrn.arr[calculateIndex(b + step)][calculateIndex (l)] == 3 )
		{
			Damaged();
		}
		else
		{
			if (scrn.arr[calculateIndex(b + step)][calculateIndex (l)] == 0)
			{
				scrn.arr[calculateIndex(b)][calculateIndex (l)] = 0;
				b += step;
				t += step;
				scrn.arr[calculateIndex(b)][calculateIndex (l)] = 1; 
			}
			else 
				if (scrn.arr[calculateIndex(b + step)][calculateIndex (l)] == 6 && quit.up==true)
				{
					inportal = true;
				}
		}
	}

};

#endif