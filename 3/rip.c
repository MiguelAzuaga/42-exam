/*Assignment name  : rip
Expected files   : *.c *.h
Allowed functions: puts, write
--------------------------------------------------------------------------------

Write a program that will take as argument a string containing only parenthesis.
if the parenthesis are unbalanced (for example "())")
your program shall remove the minimum number of parentheses for the expression to be balanced.
By removing we mean replacing by spaces.
You will then print all the solutions (can be more than one).

The order of the solutions is not important.

For example this should work:
$> ./rip '(()' | cat -e
 ()$
( )$
$> ./rip '((()()())())' | cat -e
((()()())())$
$> ./rip '()())()'| cat -e
()() ()$
()( )()$
( ())()$
$> ./rip '(()(()(' | cat -e
(()  ) $
( )( ) $
( ) () $
 ()( ) $*/


#include <stdio.h>
#include <unistd.h>

int	is_valid(char *str, int *rm, int rm_size)
{
	int i = 0, j = 0;
	int balance = 0;

	for (i = 0; str[i]; i++)
	{
		if (j < rm_size && i == rm[j])
		{
			j++;
			continue ;
		}
		if (str[i] == '(')
			balance++;
		if (str[i] == ')')
			if (--balance < 0)
				return (0);
	}
	return (balance == 0);
}

void print_solution(char *str, int *rm, int rm_size)
{
	int j = 0;
	for (int i = 0; str[i]; i++)
	{
		if (j < rm_size && i == rm[j])
		{
			write(1, " ", 1);
			j++;
		}
		else
			write(1, &str[i], 1);
	}
	write(1, "\n", 1);
}

void	solve(char *str, int str_size, int *rm, int rm_size, int start, int i)
{
	if (i == rm_size)
	{
		if (is_valid(str, rm, rm_size))
			print_solution(str, rm, rm_size);
		return ;
	}
	int j = start;
	while (j < str_size)
	{
		rm[i] = j;
		solve(str, str_size, rm, rm_size, start + 1, i + 1);
		j++;
	}
	
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	char	*str = argv[1];
	int		balance = 0
	int		remove = 0;

	while (str[i])
	{
		if (str[i] == '(')
		{
			balance++;
		}
		else if (str[i] == ')')
		{
			if (balance > 0)
				balance--;
			else
				remove ++;
		}

		i++;
	}
	remove += balance;
	int rm[remove];
	solve(str, i, rm, remove, 0, 0);
	return (0);
}
