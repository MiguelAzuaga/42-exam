

#include <unistd.h>
#include <stdlib.h>

#ifndef BSIZE
# define BSIZE 3
#endif

void cpy(char *dst, char *src, size_t len)
{
	size_t	i;
	for(i = 0; i < len; i++)
		dst[i] = src[i];
	dst[i] = 0;
}
char	*get_next_line(int fd)
{
	static char	buffer[999999];
	ssize_t		bytes_read;
	size_t		i = 0, j = 0;
	char		*line;

	while(buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		line = malloc(i + 1);
		if (!line)
			return (NULL);
		cpy(line, buffer, i);
		for (j = 0; buffer[i + j]; j++)
			buffer[j] = buffer[i + j];
		buffer[j] = 0;
		return (line);
	}
	while((bytes_read = read(fd, buffer + i, BSIZE)) > 0)
	{
		buffer[i + bytes_read] = 0;
		for(; buffer[i]; i++)
			if (buffer[i] == '\n')
			{
				i++;
				line = malloc(i + 1);
				if(!line)
					return (NULL);
				cpy(line, buffer, i);
				for(j = 0; buffer[i + j]; j++)
					buffer[j] = buffer[i + j];
				return (line);
			}
	}

	if(i > 0)
	{
		line = malloc(i + 1);
		if(!line)
			return (NULL);
		cpy(line, buffer, i);
		buffer[0] = 0;
		return (line);
	}
	return (NULL);
}
