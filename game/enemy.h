#ifndef _ENEMY_H_
#define _ENEMY_H_


#include "hero.h"


class enemy
{
public: 
	int l, r, b, t, dir;
	enemy(): l (170), r(210), b(170), t(210), dir(0) {}
	enemy( int _l, int _r, int _b, int _t): l (_l), r(_r), b(_b), t(_t), dir(0) {}
	enemy( enemy* x): l (x->l), r(x->r), b(x->b), t(x->t), dir(x->dir) {}
	~enemy(){}

	void MoveL (screen& scrn, hero& mhero)
	{
		switch (scrn.arr [calculateIndex (l - step)][calculateIndex(b)])
		{
			case 0:
				scrn.arr [calculateIndex (l)][calculateIndex(b)] = 0;
				l -= step;
				r -= step;
				scrn.arr[calculateIndex (l)][calculateIndex(b)] = 3;
				std::cout<<"<<"<<std::endl;
				break;
			case 1:
				mhero.Damaged();
				break;
			default:
				dir = 1;
				break;
		}
	}
	void MoveR (screen& scrn, hero& mhero)
	{
		switch (scrn.arr [calculateIndex (l + step)][calculateIndex(b)])
		{
			case 0:
				scrn.arr [calculateIndex (l)][calculateIndex(b)] = 0;
				l += step;
				r += step;
				scrn.arr[calculateIndex (l)][calculateIndex(b)] = 3;
				break;
			case 1:
				mhero.Damaged();
				break;
			default:
				dir = 2;
				break;
		}
	}
	void MoveU (screen& scrn, hero& mhero)
	{
		switch (scrn.arr [calculateIndex (l)][calculateIndex(b+step)])
		{
		case 0:
				scrn.arr [calculateIndex (l)][calculateIndex(b)] = 0;
				b += step;
				t += step;
				scrn.arr[calculateIndex (l)][calculateIndex(b)] = 3;
				break;
		case 1:
			mhero.Damaged();
			break;
		default:
			dir = 3;
			break;
		}
	}
	void MoveD (screen& scrn, hero& mhero)
	{
		switch (scrn.arr [calculateIndex (l)][calculateIndex(b-step)])
		{
		case 0:
				scrn.arr [calculateIndex (l)][calculateIndex(b)] = 0;
				b -= step;
				t -= step;
				scrn.arr[calculateIndex (l)][calculateIndex(b)] = 3;
				break;
			case 1:
				mhero.Damaged();
				break;
			default:
				dir = 0;
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

#endif