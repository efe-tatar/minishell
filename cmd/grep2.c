#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048
#define MAX_LENGTH BUFFER_SIZE

int match(char* pattern, char *buffer)
{
	for(int i = 0 ; i < strlen(pattern) ; i++)
	{
		if(pattern[i] != buffer[i])
			return 0;
	}
	return 1;
}

void grep(char *pattern, int fd)
{
	char buffer[BUFFER_SIZE];
	int i = 0, e = 0;
	int line_count = 1;

	while(1)
	{
		i = 0; e = 0;
		for(i = 0 ; i < BUFFER_SIZE ; i++)
		{
			//buffer[i] = getc(fd);
			read(fd, buffer+i, 1);
			if(*(buffer+i) == EOF)
			{
				e = 1;
				break;
			}
			if(*(buffer+i) == '\n')
			{
				line_count++;
				break;
			}
		}

		if(i >= strlen(pattern))
			for(int j = 0 ; j <= i - strlen(pattern) ; j++)
				if(match(pattern, buffer + j))
				{
					write(1, buffer, i);
					write(1, "\n", 1);
					break;
				}
					
		if(e == 1)
			break;
	}
}

int help()
{
	printf("correct usage:\n");
	printf("grep [pattern] [file path]\n");
	exit(-1);
}

int panic(char *msg)
{
	printf("%s\n", msg);
	exit(-1);
}

int main(int argc, char **argv)
{
	if(argc < 2) help();
	if(strlen(argv[1]) > 2048) panic("pattern max length : 2048\n");

	int fd = 0;

	if(argc > 2){
		fd = open(argv[2], O_RDONLY);
		if(fd == -1){
			write(2, "grep failed to open file\n", 26);
			exit(-1);
		}
	}

	grep(argv[1], fd);

	char eof = EOF;
	write(1, &eof, 1);

	exit(0);
}
