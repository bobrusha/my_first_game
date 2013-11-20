#include <iostream>
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

int lvl1[10][13] =
{
	{ 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0},
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0},
	{ 0, 2, 2, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0},
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 2, 0, 0, 2, 0, 2, 0, 2, 2, 0, 0, 2, 0},
	{ 2, 0, 0, 0, 2, 0, 0, 2, 2, 0, 0, 2, 0},
	{ 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0},

};
void createLevel ()
{
        scrn.clearScreen();
		switch (NUM_LVL)
		{
		case  0:
			{
				enemies.push_back(enemy (calculateCoordinates(12),calculateCoordinates(13), calculateCoordinates(5), calculateCoordinates(6), scrn));
				enemies.push_back(enemy (calculateCoordinates(5),calculateCoordinates(6), calculateCoordinates(0), calculateCoordinates(1), scrn));
				enemies.push_back(enemy (calculateCoordinates(6),calculateCoordinates(7), calculateCoordinates(7), calculateCoordinates(8), scrn));

				bricks.push_back(brick (calculateCoordinates(6), calculateCoordinates(7), calculateCoordinates(8), calculateCoordinates(9), scrn));
				bricks.push_back(brick (calculateCoordinates(11), calculateCoordinates(12), calculateCoordinates(8), calculateCoordinates(9), scrn));
				bricks.push_back(brick (calculateCoordinates(6), calculateCoordinates(7), calculateCoordinates(9), calculateCoordinates(10), scrn));
				bricks.push_back(brick (calculateCoordinates(6), calculateCoordinates(7), calculateCoordinates(10), calculateCoordinates(11), scrn));
				bricks.push_back(brick (calculateCoordinates(7), calculateCoordinates(8), calculateCoordinates(8), calculateCoordinates(9), scrn));

			
			}
			break;
		default:
			{
			std::cout<<"LOL"<<std::cout;
			}
		}

		lvlup = portal (10, 50, 10, 50, scrn);

		for (int i=0; i<13; i++)
		{
			for ( int j = 0; j<15; j++)
				std::cout<< scrn.arr[i][j]<<" ";
			std::cout<<std::endl;
		}
}

bool levelIsCompleted ()
{
	if ((enemies.empty() == true) && (bricks.empty() == true))
	{
		lvlup.up = true;
		return true;
	}
	else
		return false;
}

void levelUp()
{
	++NUM_LVL;
}

void boom (int);
void enemyMotion(int);

//-----------------------------------

void init (void)
{
        LoadTextures(textures);
		
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glutInitDisplayMode(GLUT_INDEX);
        gluOrtho2D (0.0, 420.0, 0.0, 420.0);

        scrn.Draw(wW, wH, textures[0]);
}


void redraw (void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	scrn.Draw(wW, wH, textures[0]);
	
	for (list<brick>::iterator i = bricks.begin(); i != bricks.end(); ++i)
	{
		i->Draw(textures[3]);
	}
	for (list<enemy>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		i->drawHero();
	}
	for (list<bomb>::iterator i = bombs.begin(); i != bombs.end(); ++i)
	{
		i->drawBomb(textures[2]);
	}
	Main.drawHero(textures[1]);

	lvlup.Draw(textures[4]);

	if (levelIsCompleted() == true && Main.b == lvlup.b && Main.r ==lvlup.r)
	{
		levelUp();
	}

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
                                enemies.remove( enemy (l+i*step, r+i*step, b, t, scrn) );
                        }
                }
        }

        if (scrn.arr[calculateIndex(b)][calculateIndex(l)-1] != 4)
        { 
                for (int i=0; i <= dst; ++i)
                {
                        if (scrn.arr[calculateIndex(b)][calculateIndex(l)-i] == 2)
                        {
                                bricks.remove(brick(l-i*step, r-i*step, b, t, scrn));
                                scrn.arr[calculateIndex(b)][calculateIndex(l)-i] = 0;
                                break;
                        }
                        if (scrn.arr[calculateIndex(b)][calculateIndex(l)-i] == 3)
                        {
                                enemies.remove( enemy (l-i*step, r-i*step, b, t, scrn) );
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
					scrn.arr[calculateIndex(b)+i][calculateIndex(l)] = 0;
					break;
				}
				if (scrn.arr[calculateIndex(b)-i][calculateIndex(l)] == 3)
				{
					enemies.remove( enemy (l, r, b-i*step, t-i*step, scrn) );
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
	createLevel();

	glutDisplayFunc ( redraw );
	glutTimerFunc(100, enemyMotion, 0);
	glutReshapeFunc ( reshapeFunc);
	glutSpecialFunc ( MyKeyboard );
	glutMouseFunc  ( MyFunc);
	glFlush();
	
	glutMainLoop();

}