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
	bomb ( int _l, int _r, int _b, int _t):	l(_l), r(_r), b(_b), t(_t), dst(3*step)
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
	/*
	void damage ( hero &hr, enemy & nmy)
	{
		if  ((hr.r - r >= 0 && (hr.r - r) <= dst && (hr.b == b)) ||  
			(l - hr.l >= 0 && (l - hr.l) <= dst && (hr.b == b)) ||  
			(hr.b - b >= 0 && (hr.b - b) <= dst && (hr.r == r)) || 
			(t - hr.t >= 0 && (t - hr.t) <= dst && (hr.r == r)))
		{
			hr.Damaged();
		}
		if((nmy.r - r >= 0 && (nmy.r - r) <= dst && (nmy.b == b)) ||  
			(l - nmy.l >= 0 && (l - nmy.l) <= dst && (nmy.b == b)) ||  
			(nmy.b - b >= 0 && (nmy.b - b) <= dst && (nmy.r == r)) || 
			(t - nmy.t >= 0 && (t - nmy.t) <= dst && (nmy.r == r)))
		{
			//kill enemy
			
		}
	}*/
};

#endif