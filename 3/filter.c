// Assignment name: filter
// Expected files: filter.c
// Allowed functions: read, write, strlen, memmem, memmove, malloc, calloc,
// realloc, free, printf, fprintf, stdout, stderr, perror
// --------------------------------------------------------------------------------

// Write a program that will take one and only one argument.

// Your program will then read from stdin and write all the content read in stdout
// except that every occurrence of s must be replaced by '*' (as many as the length
// of s). Your program will be tested with random buffer sizes, using a custom read
// function. Therefore the buffer being set in your program will be filled with a
// different number of chars each new call.


// For example:

// ./filter bonjour
// will behave in the same way as:
// sed 's/bonjour/*******/g'

// ./filter abc
// will behave in the same way as:
// sed's/abc/***/g'

// More generally your program must be the equivalent of the shell script filter.sh
// present in this directory (you can compare your program with it).

// In case of error during a read or a malloc, you must write "Error: " followed by
// the error message in stderr and return 1.

// If the program is called without arguments or with an empty argument or with multiple
// arguments, it must return 1.

// For example this should work:

// $> echo 'abcdefaaaabcdeabcabcdabc' | ./filter abc | cat -e
// ***defaaa***de******d***$
// $> echo 'ababcabababc' | ./filter ababc | cat -e
// *****ab*****$
// $>

// NOTES:
// memmem includes:
//                 #define _GNU_SOURCE
// 			    #include <string.h>

// perror includes:
//                 #include <errno.h>

// read includes:
//                 #include <unistd.h>


#define _GNU_SOURCE
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#ifndef BUF_SIZE
# define BUF_SIZE 3
#endif


int	main(int ac, char **av)
{
	if (ac != 2 || !av[1][0])
		return (1);

	char	buffer[999999];
	ssize_t	bytes_read;
	size_t	total = 0;
	size_t	needle_len = strlen(av[1]);
	char	*p;

	while((bytes_read = read(0, buffer + total, BUF_SIZE)) > 0)
		total += bytes_read;
	if (bytes_read < 0)
		return(perror("Error"), 1);
	p = buffer;
	while((p = memmem(p, total - (p - buffer), av[1], needle_len)) != NULL)
	{
		for(int i = 0; i < needle_len; i++)
			p[i] = '*';
		p += needle_len;
	}
	write(1, buffer, total);
	return (0);
}