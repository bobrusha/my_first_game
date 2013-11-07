#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "screen.h"

class brick
{
public:
	int l, r, b, t;

	brick (int _l,int _r, int _b, int _t, screen& scrn): l(_l), r(_r), b(_b), t(_t)
	{
		scrn.arr[calculateIndex (l)][calculateIndex(b)] = 2;
	}
	void Draw()
	{
		glLineWidth ( 2.0 );		
		glColor3f( 0.0, 1.0 , 0.0 );

		glBegin (GL_LINE_STRIP);
			glVertex2i( l , b);
			glVertex2i( l , t);
			glVertex2i( r , t);
			glVertex2i( r , b);
			glVertex2i( l , b);
		glEnd();
		glBegin (GL_LINE_STRIP);
		glVertex2i( l , b);
		glVertex2i( r , t);
		glVertex2i( l , t);
		glVertex2i( r , b);
		glEnd();
		glFlush();
	}
	
};

#endif