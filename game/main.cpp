#include <iostream>
#include <list>
#include "bomb.h"
#include "block.h"

using namespace std;

//global variables
int wW = 420, wH = 420;
int border = 20;
int maxsteps = ((wW - border)/ step);
unsigned int textures[10];
unsigned int NUM_LVL = 1;

//--------------------
//game's objects

screen scrn (wW, border, step);

list <enemy> enemies;
list <brick> bricks;
list <bomb> bombs;

hero Main (scrn);
portal lvlup ( 0, 0, 0, 0);

list <enemy>::iterator pos;

void createLevel ()
{
        scrn.clearScreen();
        enemies.clear();
        bricks.clear();
        bombs.clear();

        enemies.push_back(enemy(50, 90, 130, 170));
        enemies.push_back(enemy(50, 90, 50, 90));

		bombs.push_back(bomb(-100,-60, -100, -60));
		bricks.push_back(brick (90, 130, 10, 50, scrn));
		lvlup = portal(370,410, 370, 410);
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
	createLevel();
}

void boom (int);
void enemyMotion(int);

int calculateCoordinates (int x)
{
		x *= step;
        x += 10;
        return x;
}
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
	
        for (list<brick>::iterator i = bricks.begin(); i!= bricks.end(); ++i){
                i->Draw(textures[3]);
        }
        for (list<enemy>::iterator i = enemies.begin(); i!= enemies.end(); ++i){
                i->drawHero();
        }
        Main.drawHero(textures[1]);
        if (! bombs.empty())
		{
			bombs.begin()->drawBomb(textures[2]);
		}
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
        
        if (scrn.arr[calculateIndex(l)+1][calculateIndex(b)] != 4)
        { 
                for (int i=0; i <= dst; ++i)
                {
                        if (scrn.arr[calculateIndex(l)+i][calculateIndex(b)] == 2)
                        {
                                bricks.remove(brick(l+i*step, r+(i*step), b, t, scrn));
                                scrn.arr[calculateIndex(l)+i][calculateIndex(b)] = 0;
                                break;
                        }
                        if (scrn.arr[calculateIndex(l)+i][calculateIndex(b)] == 3)
                        {
                                enemies.remove( enemy (l+i*step, r+i*step, b, t) );
                        }
                }
        }

        if (scrn.arr[calculateIndex(l)-1][calculateIndex(b)] != 4)
        { 
                for (int i=0; i <= dst; ++i)
                {
                        if (scrn.arr[calculateIndex(l)-i][calculateIndex(b)] == 2)
                        {
                                bricks.remove(brick(l-i*step, r-i*step, b, t, scrn));
                                scrn.arr[calculateIndex(l)-i][calculateIndex(b)] = 0;
                                break;
                        }
                        if (scrn.arr[calculateIndex(l)-i][calculateIndex(b)] == 3)
                        {
                                enemies.remove( enemy (l-i*step, r-i*step, b, t) );
                        }
                }
        }

        if (scrn.arr[calculateIndex(l)][calculateIndex(b)+1] != 4)
        { 
                for (int i=0; i <= dst; ++i)
                {
                        if (scrn.arr[calculateIndex(l)][calculateIndex(b)+i] == 2)
                        {
							bricks.remove(brick(l, r, b+i*step, t+i*step, scrn));
							scrn.arr[calculateIndex(l)][calculateIndex(b)+i] = 0;
							break;
						}
						if (scrn.arr[calculateIndex(l)][calculateIndex(b)+i] == 3)
						{
							enemies.remove( enemy (l, r, b+i*step, t+i*step) );
						}
				}
		}
		if (scrn.arr[calculateIndex(l)][calculateIndex(b)-1] != 4)
		{
			for (int i = 0; i <= dst; i++)
			{
				if (scrn.arr[calculateIndex(l)][calculateIndex(b)-i] == 2)
				{
					bricks.remove(brick(l, r, b-i*step, t-i*step, scrn));
					scrn.arr[calculateIndex(l)][calculateIndex(b)+i] = 0;
					break;
				}
				if (scrn.arr[calculateIndex(l)][calculateIndex(b)-i] == 3)
				{
					enemies.remove( enemy (l, r, b-i*step, t-i*step) );
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
                bombs.begin()-> damage();
                *(bombs.begin()) = bomb();
                redraw ();
                glFlush();
                return;
        }
}

void reshapeFunc(GLint newWidth, GLint newHeight)
{
        glViewport (0, 0, newWidth, newHeight);
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        gluOrtho2D (0.0, GLdouble(newWidth),0.0, GLdouble( newHeight));
        wW = newWidth;
        wH =  newHeight;

        glClear ( GL_COLOR_BUFFER_BIT);
}

void MyFunc ( GLint button, GLint action, GLint x, GLint y )
{
        if ( button == GLUT_LEFT_BUTTON && action == GLUT_DOWN )
        {
                *(bombs.begin()) = bomb (Main.l, Main.r, Main.b, Main.t);
                redraw ();
        }
        
        glFlush();
}


void MyKeyboard( int key, int x, int y)
{
        switch(key)
        {
        case 101:
                {
                        Main.MoveD(scrn, lvlup);
						
                        redraw();
                }
                break;
        case 102:
                {
                        Main.MoveR(scrn, lvlup);
                        redraw();
                }
                break;
        case 103:
                {
                        Main.MoveU(scrn, lvlup);
                        redraw();
                }
                break;
        case 100:
                {
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
	glutCreateWindow("smth strange");
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