#ifndef LIFE_H
#define LIFE_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_game
{
	int width;
	int height;
	int iterations;
	char **board;
	int i;
	int j;
	int draw;

	char alive;
	char dead;
}	t_game;

#endif