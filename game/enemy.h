#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "screen.h"

class enemy
{
public: 
	int l, r, b, t, dir;
	enemy(): l (170), r(210), b(170), t(210), dir(0) {}
	enemy( int _l, int _r, int _b, int _t): l (_l), r(_r), b(_b), t(_t), dir(0) {}
	enemy( enemy& x): l (x.l), r(x.r), b(x.b), t(x.t), dir(x.dir) {}
	~enemy(){}

	void MoveL (screen& scrn)
	{
		if (scrn.arr[calculateIndex (l - step)][calculateIndex(b)] == 0 )
		{
			scrn.arr[calculateIndex (l)][calculateIndex(b)] = 0;
			l -= step;
			r -= step;
			scrn.arr[calculateIndex (l)][calculateIndex(b)] = 3; 
		}
		else
			dir = 1;
	}
	void MoveR (screen& scrn)
	{
		if (scrn.arr [calculateIndex (l + step)][calculateIndex(b)] == 0)
		{
			scrn.arr [calculateIndex (l)][calculateIndex(b)] = 0;
			l += step;
			r += step;
			scrn.arr[calculateIndex (l)][calculateIndex(b)] = 3; 
		}
		else
			dir = 2;
	}
	void MoveU (screen& scrn)
	{
		if (scrn.arr[calculateIndex (l)][calculateIndex(b - step)] == 0)
		{
			scrn.arr[calculateIndex (l)][calculateIndex(b)] = 0;
			b -= step;
			t -= step;
			scrn.arr[calculateIndex (l)][calculateIndex(b)] = 3; 
		}
		else
			dir = 3;
	}
	void MoveD (screen& scrn)
	{
		if (scrn.arr[calculateIndex (l)][calculateIndex(b + step)] == 0 )
		{
			scrn.arr[calculateIndex (l)][calculateIndex(b)] = 0;
			b += step;
			t += step;
			scrn.arr[calculateIndex (l)][calculateIndex(b)] = 3; 
		}
		else
			dir = 0;
	}
	
	void motion( screen& scrn)
	{ 
		if (dir == 0)
			MoveL (scrn);
		if (dir == 1)
			MoveR (scrn);
		if (dir == 2)
			MoveU (scrn);
		if (dir == 3)
			MoveD (scrn);
	}
	
	void drawHero()
	{
		//motion();
		glLineWidth ( 2.0 );		
		glColor3f(1.0, 0 , 0 );
		glBegin (GL_QUADS);
			glVertex2i( l , b);
			glVertex2i( l , t);
			glVertex2i( r , t);
			glVertex2i( r , b);
			glVertex2i( l , b);
		glEnd();
		glFlush();
	}
	void Damaged()
	{

	}
};
#endif