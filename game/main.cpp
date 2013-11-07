#include "bomb.h"
#include "block.h"

//global variables
int wW = 420, wH = 420;
int border = 20;
int maxsteps = ((wW - border)/ step);
void boom (int);
void enemyMotion(int);

unsigned int textures[1];

//-----------------------------------

screen scrn (wW, border, step);

int calculateCoordinates (int x)
{
	x *= step;
	x += 10;
	return x;
}

enemy first;
hero Main (scrn);
brick BX (10, 50, 10, 50, scrn);
bomb B;

void init (void)
{
	LoadTextures(textures);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glutInitDisplayMode(GLUT_INDEX);
	gluOrtho2D (0.0, 420.0, 0.0, 420.0);

}


void redraw (void)
{
	glClear (GL_COLOR_BUFFER_BIT);

	Main.drawHero(textures[0]);
	first.drawHero();
	B.drawBomb();
	BX.Draw();

	glFlush();
}

void enemyMotion ( int = 0)
{
	first.motion (scrn);
	redraw();
	glutTimerFunc(300, enemyMotion, 0);
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
		B.damage(Main, first);
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

	glutDisplayFunc ( redraw );
	glutTimerFunc(100, enemyMotion, 0);
	glutReshapeFunc ( reshapeFunc);
	glutSpecialFunc ( MyKeyboard );
	glutMouseFunc  ( MyFunc);

	glFlush();

	glutMainLoop();

}