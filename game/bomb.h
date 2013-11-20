#ifndef _BOMB_H_
#define _BOMB_H_

#include "hero.h"
#include "enemy.h"

int i;
void boom (int);

class bomb
{
public:
	int l, r, b, t, dst;
	bomb (): l(0), r(0), b(0), t(0), dst(0){}
	bomb ( int _l, int _r, int _b, int _t):	l(_l), r(_r), b(_b), t(_t), dst(3)
	{
		i = 0;
		glutTimerFunc(50, boom, 0);
	}

	void drawBomb (unsigned int texture)
	{	
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, texture);
		
		glColor3f( 1.0, 1.0 , 1.0);
		glLineWidth ( 2.0 );		
		glBegin (GL_QUADS);

			glTexCoord2f ( 0.0, 0.0);
			glVertex2i( l , b);
			glTexCoord2f ( 0.0, 1.0);
			glVertex2i( l , t);
			glTexCoord2f ( 1.0, 1.0);
			glVertex2i( r , t);

			glTexCoord2f ( 1.0, 0.0);
			glVertex2i( r , b);
			
		glEnd();

		glFlush();
	}
	void damage ();
	/*Переписать функцию так чтобы она была внутри класса*/
};

bool operator == (const bomb& x1, const bomb& x2)
{
	return (x1.l == x2.l && x1.b ==x2.b );
}

#endif