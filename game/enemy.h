#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "hero.h"


class enemy
{
public: 
	int l, r, b, t, dir;
	enemy(): l (170), r(210), b(170), t(210), dir(0) {}
	enemy( int _l, int _r, int _b, int _t, screen& scrn): l (_l), r(_r), b(_b), t(_t), dir(0) 
	{
		scrn.arr[calculateIndex(b)][calculateIndex (l)] = 3;
	}
	enemy( enemy* x): l (x->l), r(x->r), b(x->b), t(x->t), dir(x->dir) {}
	
	void MoveL (screen& scrn, hero& mhero)
	{
		switch (scrn.arr[calculateIndex(b)][calculateIndex (l - step)])
		{
			case 0:
				{
					scrn.arr[calculateIndex(b)][calculateIndex (l)] = 0;
					l -= step;
					r -= step;
					scrn.arr[calculateIndex(b)][calculateIndex (l)] = 3;
				}
				break;
			case 1:
				{
					mhero.Damaged();
				}
				break;
			case 2:
			case 3:
			case 4:
			case 6:
				{
					dir = 1;
				}
			break;
		}
	}
	void MoveR (screen& scrn, hero& mhero)
	{
		switch (scrn.arr [calculateIndex(b)][calculateIndex (l + step)])
		{
			case 0:
				{
					scrn.arr[calculateIndex(b)][calculateIndex (l)] = 0;
					l += step;
					r += step;
					scrn.arr[calculateIndex(b)][calculateIndex (l)] = 3;
				}
				break;
			case 1:
				{
					mhero.Damaged();
				}
				break;
			case 2:
			case 3:
			case 4:
			case 6:
				{
					dir = 2;
				}
			break;
		}
	}
	void MoveU (screen& scrn, hero& mhero)
	{
		switch (scrn.arr[calculateIndex(b+step)][calculateIndex (l)])
		{
		case 0:
			{
				scrn.arr[calculateIndex(b)][calculateIndex (l)] = 0;
				b += step;
				t += step;
				scrn.arr[calculateIndex(b)][calculateIndex (l)] = 3;
			}
				break;
		case 1:
			{
				mhero.Damaged();
				break;
			}
		case 2:
		case 3:
		case 4:
		case 6:
			{
				dir = 3;
			}
			break;
		}
	}
	void MoveD (screen& scrn, hero& mhero)
	{
		switch (scrn.arr[calculateIndex(b-step)][calculateIndex (l)])
		{
		case 0:
			{
				scrn.arr[calculateIndex(b)][calculateIndex (l)] = 0;
				b -= step;
				t -= step;
				scrn.arr[calculateIndex(b)][calculateIndex (l)] = 3;
			}
			break;
		case 1:
			{
					mhero.Damaged();
			}
			break;
		case 2:
		case 3:
		case 4:
		case 6:
			{
				dir = 0;
			}
			break;
		}
	}
	
	void motion( screen& scrn, hero& mhero)
	{ 
		if (dir == 0)
			MoveL (scrn, mhero);
		if (dir == 1)
			MoveR (scrn, mhero);
		if (dir == 2)
			MoveU (scrn, mhero);
		if (dir == 3)
			MoveD (scrn, mhero);
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
};

bool operator == (const enemy& b1, const enemy& b2)
{
	if ( b1.b == b2.b && b1.l == b2.l && b1.t == b2.t && b1.r == b2.r)
		return true;
	else 
		return false;
}

#endif