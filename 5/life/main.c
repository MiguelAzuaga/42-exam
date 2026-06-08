// Assignment name : life
// Expected files : *.c *.h
// Allowed functions: atoi, read, putchar, malloc, calloc, realloc, free
// --------------------------------------------------------------------------------
// You must write a program that will simulate a game of life.
// The prototype of this program is the following:
// ./life width height iterations
// Width and height are the dimensions of the board and iterations is the number of
// iterations of the game of life.
// the initial configuration of the board will be drawn by a sequence of commands
// in the standard input.
// Imagine a pen starting in the top left corner of the board.
// Each command is one of these characters:

// w a s d -> move the pen up, left, bottom, and right.
// x -> lift or lower the pen in order to start or stop drawing.

// Once end of file is reached, your program must simulate a game of life on this
// board and print the result in stdout (each cell alive will be represented by
// the character 'O' and each dead cell will be represented by a space)
// each cell outside of the array will be considered dead
// Example:
// $> echo 'sdxddssaaww' | ./a.out 5 5 0 | cat -e
// $
// OOO $
// O O $
// OOO $
// $
// $> echo 'sdxssdswdxddddsxaadwxwdxwaa' | ./a.out 10 6 0 | cat -e
// $
// O OOO $
// O O $
// OOO O $
// O OOO $
// $
// $> echo 'dxss' | ./a.out 3 3 0 | cat -e
// O $
// O $
// O $
// $> echo 'dxss' | ./a.out 3 3 1 | cat -e
// $
// OOO$
// $
// $> echo 'dxss' | ./a.out 3 3 2 | cat -e
// O $
// O $
// O $

#include "life.h"

void free_array(char **board, int height)
{
	for (int i = 0; i < height; ++i)
	{
		if (board[i])
			free(board[i]);
	}
	free(board);

	return ;
}

void free_board(t_game *game, int height)
{
	if (game->board)
	{
		free_array(game->board, height);
		game->board = NULL;
	}
}

int init_game(t_game *game, char **argv)
{
	game->width = atoi(argv[1]);
	game->height = atoi(argv[2]);
	game->iterations = atoi(argv[3]);

	game->i = 0;
	game->j = 0;
	game->draw = 0;

	game->alive = 'O';
	game->dead = ' ';

	game->board = calloc(game->height, sizeof(char *));
	if (!(game->board))
		return (1);
	for (int i = 0; i < game->height; ++i)
	{
		game->board[i] = calloc(game->width, sizeof(char));
		if (!(game->board[i]))
		{
			free_board(game, i);
			return (1);
		}

		for (int j = 0; j < game->width; ++j)
			game->board[i][j] = game->dead;

	}

	return (0);
}

void fill_board(t_game *game)
{
	char buffer;

	while (read(0, &buffer, 1) == 1)
	{
		switch (buffer)
		{
			case 'w':
				if (game->i > 0)
					game->i--;
				break;
			case 's':
				if (game->i < (game->height - 1))
					game->i++;
				break;
			case 'a':
				if (game->j > 0)
					game->j--;
				break;
			case 'd':
				if (game->j < (game->width - 1))
					game->j++;
				break;
			case 'x':
				game->draw = !(game->draw);
				break;
			default:
				break;
		}

		if (flag == 0 && game->draw)
		{
			if ((game->i >= 0) && (game->i < game->height) && (game->j >= 0) && (game->j < game->width))
				game->board[game->i][game->j] = game->alive;
		}
	}
}

int count_near(t_game *game, int init_i, int init_j)
{
	int count = 0;

	for (int i = init_i - 1; i <= (init_i + 1); ++i)
	{
		if (i < 0 || i >= game->height)
			continue;
		for (int j = init_j - 1; j <= (init_j + 1); ++j)
		{
			if (j < 0 || j >= game->width || (i == init_i && j == init_j))
				continue;
			if (game->board[i][j] == game->alive)
				count++;
		}
	}

	return (count);
}

int play(t_game *game)
{
	char **tmp = calloc(game->height, sizeof(char *));
	if (!tmp)
		return (1);
	for (int i = 0; i < game->height; ++i)
	{
		tmp[i] = calloc(game->width, sizeof(char));
		if (!(tmp[i]))
		{
			free_array(tmp, i);
			return (1);
		}
	}

	for (int i = 0; i < game->height; ++i)
	{
		for (int j = 0; j < game->width; ++j)
		{
			int near = count_near(game, i, j);
			if (near != 2 && near != 3)
				tmp[i][j] = game->dead;
			else if (near == 2 && game->board[i][j] == game->dead)
				tmp[i][j] = game->dead;
			else
				tmp[i][j] = game->alive;
		}
	}

	free_board(game, game->height);
	game->board = tmp;

	return (0);
}

void print_board(t_game *game)
{
	for (int i = 0; i < game->height; ++i)
	{
		for (int j = 0; j < game->width; ++j)
		{
			putchar(game->board[i][j]);
		}
		putchar('\n');
	}
}

int main(int ac, char **av)
{
	if (ac != 4)
		return (1);

	t_game game;

	if (init_game(&game, av))
		return (1);

	fill_board(&game);

	for (int i = 0; i < game.iterations; i++)
	{
		if (play(&game))
		{
			free_board(&game, game.height);
			return (1);
		}
	}
	print_board(&game);
	free_board(&game, game.height);

	return (0);
}