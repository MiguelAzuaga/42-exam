/* Assignement name : n_queens

Expected files : *.c *.h

Allowed functions : atoi, fprintf, write, calloc, malloc, free, realloc, stdout, stderr

-------------------------------------------------------------------------

Write a program that will print all the solutions to the n queens problem
for a n given as argument.
We will not test with negative values.
The order of the solutions is not important.

You will display the solutions under the following format :
<p1> <p2> <p3> ... \n
where pn are the line index of the queen in each colum starting from 0.

For example this should work :
$> ./n_queens 2 | cat -e

$> ./n_queens 4 | cat -e
1 3 0 2$
2 0 3 1$

$> ./n_queens 7 | cat -e
0 2 4 6 1 3 5$
0 3 6 2 5 1 4$
etc... */

#include <stdio.h>
#include <stdlib.h>

int	ft_abs(int n)
{
	return(n < 0 ? - n : n);
}

int	is_safe(int *board, int col, int row)
{
	int	i = 0;

	while (i < col)
	{
		if (board[i] == row)
			return (0);
		if (ft_abs(board[i] - row) == ft_abs(i - col))
			return (0);
		i++;
	}
	return (1);
}

void	print_solution(int *board, int size)
{
	int i = 0;

	while (i < size)
	{
		printf("%d%c", board[i], i == size - 1 ? '\n' : ' ');
		i++;
	}
}

void	solve(int *board, int size, int col)
{
	int row = 0;

	if (col == size)
		print_solution(board, size);
	while(row < size)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;
			solve(board, size, col + 1);
		}
		row++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	int n = atoi(argv[1]);
	int board[n];
	solve(board, n , 0);
}