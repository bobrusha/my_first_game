#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "screen.h"

class brick
{
public:
        int l, r, b, t;

        brick (int _l,int _r, int _b, int _t, screen& scrn): l(_l), r(_r), b(_b), t(_t)
        {
                scrn.arr[calculateIndex(b)][calculateIndex (l)] = 2;
        }
	void Draw (unsigned int texture)
    {
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, texture);
		
		glLineWidth ( 2.0 );
		glColor3f( 1.0, 1.0 , 1.0 );
		glBegin (GL_QUADS);
			glTexCoord2f (0.0, 0.0);
			glVertex2i( l , b);
			
			glTexCoord2f (0.0, 1.0);
			glVertex2i( l , t);
			
			glTexCoord2f (1.0, 1.0);
			glVertex2i( r , t);
			
			glTexCoord2f (1.0, 0.0);
			glVertex2i( r , b);
			
		glEnd();
		glFlush();
	}
};

bool operator == (const brick& b1, const brick& b2)
{
        if ( b1.b == b2.b && b1.l == b2.l && b1.t == b2.t && b1.r == b2.r)
                return true;
        else 
                return false;
}
class portal
{
public:
	int l, r, b, t;
	bool up;
	portal(): l(0), r(0), b(0), t(0), up(false){}
	portal (int _l, int _r, int _b, int _t, screen& scrn):l(_l), r(_r), b(_b), t(_t), up(false)
	{
		//scrn.arr[calculateIndex(b)][calculateIndex(l)] = 6;
	}
	
	void Draw (unsigned int texture)
	{
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, texture);
		glLineWidth ( 2.0 );
		glColor3f( 1.0, 1.0 , 1.0 );

		glBegin (GL_QUADS);

			glTexCoord2f (0.0, 0.0);
			glVertex2i( l , b);
			glTexCoord2f (0.0, 1.0);
			glVertex2i( l , t);
			glTexCoord2f (1.0, 1.0);
			glVertex2i( r , t);
			glTexCoord2f (1.0, 0.0);
			glVertex2i( r , b);
			glEnd();
		glFlush();
	}
};

class beaton
{
        int l, r, b, t;
public:
	beaton (int _l,int _r, int _b, int _t, screen& scrn): l(_l), r(_r), b(_b), t(_t)
	{
		scrn.arr[calculateIndex (l)][calculateIndex(b)] = 4;
	}
	void Draw (unsigned int texture)
    {
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, texture);
		
		glLineWidth ( 2.0 );
		glColor3f( 1.0, 1.0 , 1.0 );
		glBegin (GL_QUADS);
			glTexCoord2f (0.0, 0.0);
			glVertex2i( l , b);
			
			glTexCoord2f (0.0, 1.0);
			glVertex2i( l , t);
			
			glTexCoord2f (1.0, 1.0);
			glVertex2i( r , t);
			
			glTexCoord2f (1.0, 0.0);
			glVertex2i( r , b);
			
			glEnd();
			glFlush();
        }
};
#endif