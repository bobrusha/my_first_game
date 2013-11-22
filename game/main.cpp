﻿#include <iostream>
#include <vector>
#include <list>
#include "bomb.h"
#include "block.h"

using namespace std;

//global variables
int wW = 540, wH = 460;
int border = 20;
int maxsteps = ((wW - border)/ step);

unsigned int textures[10];
unsigned int NUM_LVL = 0;

//--------------------
//game's objects

screen scrn;

list <enemy> enemies;
list <brick> bricks;
list <bomb> bombs;
list <beaton> btn;

hero Main (scrn);
portal lvlup ( 0, 0, 0, 0, scrn);

list <enemy>::iterator pos;

//-----------------------
int calculateCoordinates (int x)
{
		x *= step;
        x += 10;
        return x;
}
//-----------------------

int lvls[2][13][15] =
{
	{
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 2, 0 },
		{ 4, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 4 },
		{ 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 2, 0, 2, 3, 2, 0, 2, 0, 0, 4 },
		{ 4, 0, 2, 2, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 4 },
		{ 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4 },
		{ 4, 2, 0, 0, 2, 0, 2, 0, 2, 2, 0, 0, 2, 2, 4 },
		{ 4, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 4 },
		{ 4, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 4 },
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }
	},
	{
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
		{ 4, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4 },
		{ 4, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 4 },
		{ 4, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 4 },
		{ 4, 0, 0, 2, 0, 0, 3, 2, 0, 0, 2, 2, 0, 0, 4 },
		{ 4, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 0, 0, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 3, 4 },
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }
	}
};

void createLevel ()
{
        scrn.clearScreen();
		bricks.clear();
		enemies.clear();
		btn.clear();

		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				switch ( lvls[NUM_LVL][i][j])
				{
					case 2:
					{
						bricks.push_back(brick (calculateCoordinates(j - 1), calculateCoordinates(j), calculateCoordinates(i-1), calculateCoordinates(i), scrn));
					}
					break;
					case 3:
					{
						enemies.push_back(enemy (calculateCoordinates(j - 1), calculateCoordinates(j), calculateCoordinates(i-1), calculateCoordinates(i), scrn));
					}
					break;
					case 4:
					{
						btn.push_back(beaton (calculateCoordinates(j - 1), calculateCoordinates(j), calculateCoordinates(i-1), calculateCoordinates(i), scrn));
					}
				}
			}
		}

		lvlup = portal (10, 50, 10, 50, scrn);
		Main = hero (scrn);
}

void levelUp()
{
	++NUM_LVL;
	createLevel();
}

void boom (int);
void enemyMotion(int);

//-----------------------------------

void init (void)
{
	memset(&textures, 0, sizeof(textures));
	LoadTextures(textures);
	
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutInitDisplayMode(GLUT_INDEX);
	gluOrtho2D (0.0, 420.0, 0.0, 420.0);
	
	scrn.Draw(wW, wH, textures[0]);
	NUM_LVL=0;
}

void youLose()
{
	glClear (GL_COLOR_BUFFER_BIT);
	glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, textures[5]);

		glEnable (GL_TEXTURE_2D);

		glLineWidth ( 2.0 );		
		glColor3f( 1.0, 1.0 , 1.0 );

		glBegin (GL_QUADS);

			glTexCoord2f ( 0.0, 0.0);
			glVertex2i( 200 , 200);

			glTexCoord2i ( 0.0, 1.0);
			glVertex2i( 200 , 350);

			glTexCoord2i ( 1.0, 1.0);
			glVertex2i( 400 , 350);
			
			glTexCoord2i (1.0, 0.0);
			glVertex2i( 400 , 200);

			glEnd();
		glFlush();
}

void redraw (void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	scrn.Draw(wW, wH, textures[0]);
	std::cout<<btn.size()<<std::endl;

	for (list<beaton>::iterator i = btn.begin(); i != btn.end(); ++i)
	{
		i->Draw(textures[6]);
	}

	if (! bricks.empty())
	{
		for (list<brick>::iterator i = bricks.begin(); i != bricks.end(); ++i)
		{
			i->Draw(textures[3]);
		}
	}
	if (! enemies.empty())
	{
		for (list<enemy>::iterator i = enemies.begin(); i != enemies.end(); ++i)
		{
			i->drawHero();
		}
	}
	
	if ( !bombs.empty())
	{
		for (list<bomb>::iterator i = bombs.begin(); i != bombs.end(); ++i)
		{
			i->drawBomb(textures[2]);
		}
	}
	Main.drawHero(textures[1]);

	lvlup.Draw(textures[4]);

	if ( enemies.empty() && Main.b == lvlup.b && Main.r ==lvlup.r)
	{
		levelUp();
	}
	//cout<<NUM_LVL<<endl;
	glFlush();
}

void enemyMotion ( int = 0)
{
        for (list<enemy>::iterator i = enemies.begin(); i!= enemies.end(); ++i)
        {
                i->motion(scrn, Main);
        }
        redraw();

        glutTimerFunc(300, enemyMotion, 0);
}

void bomb::damage()
{
	if (scrn.arr[calculateIndex(b)][calculateIndex(l)+1] != 4)
	{
		for (int i=0; i <= dst; ++i)
		{
			if (scrn.arr[calculateIndex(b)][calculateIndex(l)+i] == 2)
			{
				bricks.remove(brick(l+i*step, r+(i*step), b, t, scrn));
				scrn.arr[calculateIndex(b)][calculateIndex(l)+i] = 0;
				break;
			}
			if (scrn.arr[calculateIndex(b)][calculateIndex(l)+i] == 3)
			{
				enemies.remove( enemy ( l + i*step, r + i*step, b, t, scrn) );
				scrn.arr[calculateIndex(b)][calculateIndex(l)+i] = 0;
			}
		}
	}
	if (scrn.arr[calculateIndex(b)][calculateIndex(l)-1] != 4)
	{
		for (int i=0; i <= dst; ++i)
		{
			if (scrn.arr[calculateIndex(b)][calculateIndex(l) - i] == 2)
			{
				std::cout<<calculateIndex(l) - i<<" "<<r - i*step<<std::endl;

				bricks.remove(brick( l - i*step, r - i*step, b, t, scrn));
				scrn.arr[calculateIndex(b)][calculateIndex(l) - i] = 0;
				break;
			}
			if (scrn.arr[calculateIndex(b)][calculateIndex(l)-i - 1] == 3)
			{
				enemies.remove( enemy (l-i*step, r-i*step, b, t, scrn) );
				scrn.arr[calculateIndex(b)][calculateIndex(l)- i - 1] = 0;
			}
		}
	}
	if (scrn.arr[calculateIndex(b)+1][calculateIndex(l)] != 4)
	{
		for (int i=0; i <= dst; ++i)
		{
			if (scrn.arr[calculateIndex(b)+i][calculateIndex(l)] == 2)
			{
				bricks.remove(brick(l, r, b+i*step, t+i*step, scrn));
				scrn.arr[calculateIndex(b)+i][calculateIndex(l)] = 0;
				break;
			}
			if (scrn.arr[calculateIndex(b)+i][calculateIndex(l)] == 3)
			{
				enemies.remove( enemy (l, r, b+i*step, t+i*step, scrn) );
				scrn.arr[calculateIndex(b)+i][calculateIndex(l)] = 0;
			}
		}
	}
	if (scrn.arr[calculateIndex(b)-1][calculateIndex(l)] != 4)
	{
		for (int i = 0; i <= dst; i++)
		{
			if (scrn.arr[calculateIndex(b)-i][calculateIndex(l)] == 2)
			{
				bricks.remove(brick(l, r, b-i*step, t-i*step, scrn));
				scrn.arr[calculateIndex(b)-i][calculateIndex(l)] = 0;
				break;
			}
			if (scrn.arr[calculateIndex(b)-i][calculateIndex(l)] == 3)
			{
				enemies.remove( enemy (l, r, b-i*step, t-i*step, scrn) );
				scrn.arr[calculateIndex(b)-i][calculateIndex(l)] = 0;
			}
		}
	}
}

void boom (int = 0)
{
        i++;
        if( i < 20)
        {
                glutTimerFunc( 100, boom, 0);
        }
        if ( i == 20)
        {
			if(bombs.empty() == false)
			{
				std::cout<<"I'm there!"<<std::endl;
                bombs.begin()-> damage();

				bombs.remove(*(bombs.begin()));
				std::cout<<bombs.size()<<std::endl;
                redraw ();
                glFlush();
                return;
			}
        }
}

void reshapeFunc(GLint newWidth, GLint newHeight)
{
        glViewport (0, 0, newWidth, newHeight);
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        gluOrtho2D (0.0, GLdouble(newWidth),0.0, GLdouble( newHeight));
        wW = newWidth;
        wH = newHeight;

        glClear ( GL_COLOR_BUFFER_BIT);
}

void MyFunc ( GLint button, GLint action, GLint x, GLint y )
{
        if ( button == GLUT_LEFT_BUTTON && action == GLUT_DOWN )
        {
                bombs.push_back( bomb (Main.l, Main.r, Main.b, Main.t));
                redraw ();
        }
		 if ( button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN )
        {
			for (int i=0; i<13; i++)
			{
				for (int j=0; j<15; j++)
				{
					std::cout<<scrn.arr[i][j]<<" ";
				}
				std::cout<<std::endl;
			}
        }
        
        glFlush();
}


void MyKeyboard( int key, int x, int y)
{
	switch(key)
	{
	case 101:
		{
			std::cout<<"101"<< std::endl;
			Main.MoveU(scrn, lvlup);
			for (int i = 0; i < 13; i++)
			{
				for (int j = 0; j< 15;j++)
				std::cout<<scrn.arr[i][j]<<" ";
				std::cout<<std::endl;
			}
			std::cout<<std::endl;
			redraw();
		}
		break;
	case 102:
		{
			std::cout<<"102"<< std::endl;
			Main.MoveR(scrn, lvlup);
			redraw();
			for (int i = 0; i < 13; i++)
			{
				for (int j = 0; j< 15;j++)
				std::cout<<scrn.arr[i][j]<<" ";
				std::cout<<std::endl;
			}
			std::cout<<std::endl;
			

		}
		break;
	case 103:
		{
			std::cout<<"103"<< std::endl;
			Main.MoveD(scrn, lvlup);
			redraw();
		}
		break;
	case 100:
		{
			std::cout<<"100"<< std::endl;
			Main.MoveL(scrn, lvlup);
			redraw();
		}
		break;
	}
	glFlush();
}

int main ( int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 100);
	glutInitWindowSize( wW, wH);
	glutCreateWindow("Dyna blaster");

	init();
	std::cout<<btn.size()<<"main before createLevel()"<<std::endl;
	createLevel();
	std::cout<<btn.size()<<"main after createLevel()"<<std::endl;

	glutDisplayFunc ( redraw );
	glutTimerFunc(100, enemyMotion, 0);
	glutReshapeFunc ( reshapeFunc);
	glutSpecialFunc ( MyKeyboard );
	glutMouseFunc  ( MyFunc);
	glFlush();
	
	glutMainLoop();

}