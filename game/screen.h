#ifndef _SCREEN_H_
#define _SCREEN_H_
#include "texture.h"

 int step = 40;
int calculateIndex (int x)
{
	x += (step - 10);
	x /= step;
	return x;
}

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
	screen( int W, int brdr, int stp) 
	{
		const int k = (W - brdr)/stp ;

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
#endif