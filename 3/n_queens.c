/*Assignement name : n_queens

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
etc...*/

#include <stdio.h>
#include <stdlib.h>

int ft_abs(int n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

void print_sol(int *pos, int size)
{
	for (int i = 0; i < size; i++)
		fprintf(stdout, "%d%c", pos[i], (i == size - 1) ? '\n' : ' ');
	return ;
}

int	is_safe(int *pos, int col, int row)
{
	for (int i = 0; i < col; i++)
	{
		if (pos[i] == row || ft_abs(pos[i] - row) == ft_abs(i - col))
			return (0);
	}
	return (1);
}

void solve(int *pos, int col, int size)
{
	if (col == size)
		return (print_sol(pos, size));
	for (int row = 0; row < size; row++)
	{
		if(is_safe(pos, col, row))
		{
			pos[col] = row;
			solve(pos, col + 1, size);
		}
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int n = atoi(av[1]);
	if (n <= 0)
		return (1);
	int *pos = calloc(n, sizeof(int));
	if (!n)
		return (1);
	solve(pos, 0, n);
	free(pos);
}
