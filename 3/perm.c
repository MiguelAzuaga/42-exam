/* Assignment name  : permutations
Expected files   : *.c *.h
Allowed functions: puts, malloc, calloc, realloc, free, write
---------------------------------------------------------------

Write a program that will print all the permutations of a string given as argument.

The solutions must be given in alphabetical order.

We will not try your program with strings containing duplicates (eg: 'abccd').

For example this should work:

$> ./permutations a | cat -e
a$

$> ./permutations ab | cat -e
ab$
ba$

$> ./permutations abc | cat -e
abc$
acb$
bac$
bca$
cab$
cba$ */


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void swap(char *a, char *b)
{
	char temp = *a;

	*a = *b;
	*b = temp;
}

char	*sort(char *str)
{
	int i, j;

	i = 0;
	while (str[i])
	{
		j = -1;
		while (str[++j])
			if (str[j] < str[j - 1])
				swap(&str[j], &str[j - 1]);
		i++;
	}
	return (str);
}

// Recursive function to generate permutations
void permute(char *str, int i, int len)
{
	int	j;

	if (i == len)
		puts(str);
	else
	{
		j = i;
		while(j <= len)
		{
			swap(&str[i], &str[j]);
			permute(str, i + 1, len);
			swap(&str[i], &str[j]);
			j++;
		}
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	char	*str = av[1];
	int		len = 0;

	str = sort(str);
	while(str[len])
		len++;
	permute(str, 0, len - 1);
}