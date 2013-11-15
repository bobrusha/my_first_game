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
//-----------------------------------

void boom (int);
void enemyMotion(int);

int calculateCoordinates (int x)
{
	x *= step;
	x += 10;
	return x;
}
//-----------------------------------


screen scrn (wW, border, step);
list <enemy> enemies;
list <brick> bricks;
list <bomb> bombs;

enemy first;
hero Main (scrn);
//brick BX (10, 50, 10, 50, scrn);
bomb B;

list <enemy>::iterator pos;

void createLevel ()
{
	scrn.clearScreen();
	enemies.clear();
	bricks.clear();
	bombs.clear();

	enemies.push_back(first);
	enemies.push_back(enemy(50, 90, 50, 90));

	//bricks.push_back(BX);
	bricks.push_back(brick (90, 130, 10, 50, scrn));
}

bool levelIsCompleted ()
{
	return ((enemies.empty() == true) && (bricks.empty() == true));
	
}
void init (void)
{
	LoadTextures(textures);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutInitDisplayMode(GLUT_INDEX);
	gluOrtho2D (0.0, 420.0, 0.0, 420.0);

	scrn.Draw(wW, wH, textures[0]);

	//createLevel();
	pos = enemies.begin();
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
	
	B.drawBomb(textures[2]);
	
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
	/*
	проверяем в каждом направлении
	сначала на бетонную стену
	потом на кирппичную, если поп-ся кирпичная уничтожаем её и выходим из этого направления
	потом на врагов, если поп-ся уничтожаем их
	*/
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
				std::cout<<"I wanna damaged bricks! TOP"<<std::endl;
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
				std::cout<<b<<" "<<calculateIndex(b)<<" "<< b-i*step<<std::endl;
				std::cout<<i<<" "<<dst<<std::endl;
				std::cout<<calculateIndex(b)-i<<std::endl;
				std::cout<<"I wanna damaged bricks! DOWN"<<std::endl;

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

	if (levelIsCompleted() == true)
	{
		createLevel();
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
		B.damage();
		B = bomb();
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

	/*	glViewport ( 0, 0, newWidth, newHeight );
	glMatrixMode ( GL_PROJECTION );

	gluOrtho2D (0.0, 400.0, 0.0, 400.0);
	*/

	glClear ( GL_COLOR_BUFFER_BIT);
}

void MyFunc ( GLint button, GLint action, GLint x, GLint y )
{
	if ( button == GLUT_LEFT_BUTTON && action == GLUT_DOWN )
	{
		B = bomb (Main.l, Main.r, Main.b, Main.t);
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
			Main.MoveD(scrn);
			redraw();
		}
		break;
	case 102:
		{
			Main.MoveR(scrn);
			redraw();
		}
		break;
	case 103:
		{
			Main.MoveU(scrn);
			redraw();
		}
		break;
	case 100:
		{
			Main.MoveL(scrn);
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