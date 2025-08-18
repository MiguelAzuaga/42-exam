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

int ft_abs(int n)
{
	return ((n >= 0) ? n : -n);
}

int is_solved(char *str)
{
	int i = 0, balance = 0;
	while (str[i])
	{
		if (str[i] == '(')
			balance++;
		else if (str[i] == ')')
		{
			balance--;
			if (balance < 0)
				return 0;
		}
		i++;
	}
	return (balance == 0);
}

// Try all combinations of removing `qty` occurrences of `c`
void get_answer(char *str, char c, int qty)
{
	int len = 0, i;
	while (str[len])
		len++;

	int total = 0;
	for (i = 0; i < len; i++)
		if (str[i] == c)
			total++;

	int max_mask = 1 << total;
	for (int mask = 0; mask < max_mask; mask++)
	{
		// Count bits set to 1
		int count = 0;
		for (int b = 0; b < total; b++)
			if ((mask >> b) & 1)
				count++;

		if (count != qty)
			continue;

		// Backup original characters
		char backup[256];  // assuming max input length < 256
		for (i = 0; i < len; i++)
			backup[i] = str[i];

		int skip_idx = 0;
		for (i = 0; i < len; i++)
		{
			if (str[i] == c)
			{
				if ((mask >> skip_idx) & 1)
					str[i] = ' ';
				skip_idx++;
			}
		}

		if (is_solved(str))
			puts(str);

		// Restore string
		for (i = 0; i < len; i++)
			str[i] = backup[i];
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	char *str = argv[1];
	int open = 0, close = 0, i = 0;

	while (str[i])
	{
		if (str[i] == '(')
			open++;
		else if (str[i] == ')')
			close++;
		i++;
	}

	int balance = open - close;

	if (balance == 0)
	{
		if (is_solved(str))
			puts(str);
		else
			get_answer(str, ')', 1);
	}
	else if (balance > 0)
		get_answer(str, '(', balance);
	else
		get_answer(str, ')', -balance);

	return 0;
}
