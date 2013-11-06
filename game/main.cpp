#include "texture.h"

//global variables
int wW = 420, wH = 420;
int step = 40, border = 20;
int maxsteps = ((wW - border)/ step);
void boom (int);
void enemyMotion(int);

unsigned int textures[1];

//-----------------------------------
class screen
{
public:
	int arr [12][12];
	// 0 - free
	// 1 - hero
	// 2 - obj
	// 3 - enemy
	// 4 - bonus
	// 5 - exit
	screen() 
	{
		const int k = (wW - border)/step ;

		for (int i = 0; i < k+2; i++)
			for ( int j=0; j<k; j++)
				arr[i][j] = 0;

		for (int i = 0; i < k+2; i++)
			arr[i][0] = 2;
		for (int i = 0; i < k+2; i++)
			arr[i][k+1] = 2;
		for (int j = 0; j < k+2; j++)
			arr[0][j] = 2;
		for (int j = 0; j < k+2; j++)
			arr[k+1][j] = 2;
	}
	void clearScreen()
	{
		for (int i = 0; i<10; i++)
			for ( int j=0; j<10; j++)
				arr[i][j] = 0;
	}
};

screen scrn;

int calculateIndex (int x)
{
	x += (step - 10);
	x /= step;
	return x;
}

int calculateCoordinates (int x)
{
	x *= step;
	x += 10;
	return x;
}

class box
{
public:
	int l, r, b, t;
	box (int _l,int _r, int _b, int _t): l(_l), r(_r), b(_b), t(_t)
	{
		scrn.arr[calculateIndex (l)][calculateIndex(b)] = 2;
	}
	void Draw()
	{
		glLineWidth ( 2.0 );		
		glColor3f( 0.0, 1.0 , 0.0 );

		glBegin (GL_LINE_STRIP);
			glVertex2i( l , b);
			glVertex2i( l , t);
			glVertex2i( r , t);
			glVertex2i( r , b);
			glVertex2i( l , b);
		glEnd();
		glBegin (GL_LINE_STRIP);
		glVertex2i( l , b);
		glVertex2i( r , t);
		glVertex2i( l , t);
		glVertex2i( r , b);
		glEnd();
		glFlush();
	}
	
};



class enemy
{
public: 
	int l, r, b, t, dir;
	enemy(): l (170), r(210), b(170), t(210), dir(0) 
	{

	}
	
	void MoveL()
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
	void MoveR()
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
	void MoveU()
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
	void MoveD()
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
	
	void motion()
	{ 
		if (dir == 0)
			MoveL();
		if (dir == 1)
			MoveR();
		if (dir == 2)
			MoveU();
		if (dir == 3)
			MoveD();
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

enemy first;


class hero
{
public:
	int l, r, b, t, lives;

	hero(): l (90), r(130), b(10), t(50), lives (2) 
	{	
		scrn.arr[calculateIndex (l)][calculateIndex(b)] = 1;
	}

	void drawHero()
	{
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, textures[0]);

		glEnable (GL_TEXTURE_2D);

		glLineWidth ( 2.0 );		
		glColor3f( 1.0, 1.0 , 1.0 );

		glBegin (GL_QUADS);

			glTexCoord2f ( 0.0, 0.0);
			glVertex2i( l , b);

			glTexCoord2i ( 0.0, 1.0);
			glVertex2i( l , t);

			glTexCoord2i ( 1.0, 1.0);
			glVertex2i( r , t);
			
			glTexCoord2i (1.0, 0.0);
			glVertex2i( r , b);

			glEnd();
		glFlush();

		if ( lives == 2)
		{
			glLineWidth ( 2.0 );		
			glColor3i( 0, 255 , 0 );
			glBegin (GL_LINE_STRIP);
			glVertex2i( 380, 10);
			glVertex2i( 380, 20);
			glVertex2i( 390, 20);
			glVertex2i( 390, 10);
			glVertex2i( 380, 10 );
			glEnd();
		}
		if (lives >= 1)
		{
			glLineWidth ( 2.0 );		
			glColor3i( 0, 255 , 0 );
			glBegin (GL_LINE_STRIP);
			glVertex2i( 360, 10);
			glVertex2i( 360, 20);
			glVertex2i( 370, 20);
			glVertex2i( 370, 10);
			glVertex2i( 360, 10 );
			glEnd();
		}
		glFlush();
	
	}

	// движение героя 
	//проверяем свободна ли клетка и если да пермещаем в неё героя
	//освобождаем предыдущую клетку
	void Damaged()
	{
		lives --;
	}
	void MoveL()
	{
		if ( scrn.arr[calculateIndex (l - step)][calculateIndex(b)] == 3 )
		{
			Damaged();
		}
		else
			if ( scrn.arr[calculateIndex (l - step)][calculateIndex(b)] == 0 )
			{
				scrn.arr[calculateIndex (l)][calculateIndex(b)] = 0;
				l -= step;
				r -= step;
				scrn.arr[calculateIndex (l)][calculateIndex(b)] = 1; 
			}
	}
	void MoveR()
	{
		if ( scrn.arr[calculateIndex (l + step)][calculateIndex(b)] == 3 )
		{
			Damaged();
		}
		else
		{
			if (scrn.arr [calculateIndex (l + step)][calculateIndex(b)] == 0)
			{
				scrn.arr [calculateIndex (l)][calculateIndex(b)] = 0;
				l += step;
				r += step;
				scrn.arr[calculateIndex (l)][calculateIndex(b)] = 1; 
			}
		}
	}
	void MoveU()
	{
		if ( scrn.arr[calculateIndex (l)][calculateIndex(b - step)] == 3 )
		{
			Damaged();
		}
		else
		{
			if (scrn.arr[calculateIndex (l)][calculateIndex(b - step)] == 0 )
			{
				scrn.arr[calculateIndex (l)][calculateIndex(b)] = 0;
				b -= step;
				t -= step;
				scrn.arr[calculateIndex (l)][calculateIndex(b)] = 1; 
			}
		}
	}
	void MoveD()
	{
		if ( scrn.arr[calculateIndex (l)][calculateIndex(b + step)] == 3 )
		{
			Damaged();
		}
		else
		{
			if (scrn.arr[calculateIndex (l)][calculateIndex(b + step)] == 0)
			{
				scrn.arr [calculateIndex (l)][calculateIndex(b)] = 0;
				b += step;
				t += step;
				scrn.arr[calculateIndex (l)][calculateIndex(b)] = 1; 
			}
		}
	}

};

hero Main;
box BX (10, 50, 10, 50);
int i;

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

	void drawBomb()
	{	
		glColor3i( 0, 141 , 0);
		glLineWidth ( 2.0 );		
		glBegin (GL_LINE_STRIP);
			glVertex2i( l , b);
			glVertex2i( r , t);
			glVertex2i( r , b);
			glVertex2i( l , t);
			glVertex2i( l , b);
		glEnd();

		glFlush();
	}

	void damage ( )
	{
		if  ((Main.r - r >= 0 && (Main.r - r) <= dst && (Main.b == b)) ||  
			(l - Main.l >= 0 && (l - Main.l) <= dst && (Main.b == b)) ||  
			(Main.b - b >= 0 && (Main.b - b) <= dst && (Main.r == r)) || 
			(t - Main.t >= 0 && (t - Main.t) <= dst && (Main.r == r)))
		{
			Main.Damaged ();
		}
	}
};


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

	Main.drawHero();
	first.drawHero();
	B.drawBomb();
	BX.Draw();

	glFlush();
}

void enemyMotion ( int = 0)
{
	first.motion();
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
	if ( button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN )
	{
		B.damage();

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
			Main.MoveD();
			redraw();
		}
		break;
	case 102:
		{
			Main.MoveR();
			redraw();
		}
		break;
	case 103:
		{
			Main.MoveU();
			redraw();
		}
		break;
	case 100:
		{
			Main.MoveL();
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