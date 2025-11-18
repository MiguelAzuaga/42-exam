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

int check_bits(int mask)
{
	int count = 0;

	while (mask)
	{
		count += mask & 1;
		mask >>= 1;
	}
	return (count);
}

int is_balanced(char *str, int mask)
{
	int i = 0, balance = 0;
	while (str[i])
	{
		if ((mask & (1 << i)) == 0)
		{
			if (str[i] == '(')
				balance++;
			else if (str[i] == ')')
			{
				if (balance == 0)
					return (0);
				balance--;
			}
		}
		i++;
	}
	return (balance == 0);
}

void print_solution(char *str, int mask)
{
	int i = 0;
	while (str[i])
	{
		if (mask & (1 << i))
			write(1, " ", 1);
		else
			write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	char	*str = argv[1];
	int		i = 0;
	int		balance = 0;
	int		remove = 0;
	int		mask;
	int		max_mask;

	while (str[i])
	{
		if (str[i] == '(')
			balance++;
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

	mask = 0;
	max_mask = 1 << i;
	while (mask < max_mask)
	{
		if (check_bits(mask) == remove && is_balanced(str, mask))
			print_solution(str, mask);
		mask++;
	}
	return (0);
}
