#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *create_buffer(char *file);
void close_file(int fd);

/**
 * create_buffer - Allocates 1024 bytes for a buffer.
 * @file: The name of the file buffer is storing chars for.
 *
 * Return: A pointer to the newly-allocated buffer.
 */
char *create_buffer(char *file)
{
	char *buffer;

        buffer = malloc(sizeof(char) * 1024);

        if (buffer == NULL)
	{
		dprintf(STDERR_FILENO,
                        "Error: Can't write to %s\n", file);
                exit(99);
	}

	return (buffer);
}

/**
 * close_file - Closes file descriptors.
 * @fd: The file descriptor to be closed.
 */
void close_file(int fd)
{
	int c;

        c = close(fd);

        if (c == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
                exit(100);
	}
}

0x15. C - File I/O
0x15. C - File I/O


README.md


Project




































main.h


#ifndef MAIN_H

#define MAIN_H


#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <unistd.h>


ssize_t read_textfile(const char *filename, size_t letters);

int create_file(const char *filename, char *text_content);

int append_text_to_file(const char *filename, char *text_content);


#endif


























0-read_textfile.c


#include "main.h"

#include <stdlib.h>


/**

 * read_textfile- Read text file print to STDOUT.

 * @filename: text file being read

 * @letters: number of letters to be read

 * Return: w- actual number of bytes read and printed

 *        0 when function fails or filename is NULL.

 */

ssize_t read_textfile(const char *filename, size_t letters)

{

        char *buf;

        ssize_t fd;

        ssize_t w;

        ssize_t t;


        fd = open(filename, O_RDONLY);

        if (fd == -1)

                return (0);

        buf = malloc(sizeof(char) * letters);

        t = read(fd, buf, letters);

        w = write(STDOUT_FILENO, buf, t);


        free(buf);

        close(fd);

        return (w);

}











1-create_file.c


#include "main.h"


/**

 * create_file - Creates a file.

 * @filename: A pointer to the name of the file to create.

 * @text_content: A pointer to a string to write to the file.

 *

 * Return: If the function fails - -1.

 *         Otherwise - 1.

 */

int create_file(const char *filename, char *text_content)

{

        int fd, w, len = 0;


        if (filename == NULL)

                return (-1);


        if (text_content != NULL)

        {

                for (len = 0; text_content[len];)

                        len++;

        }


        fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0600);

        w = write(fd, text_content, len);


        if (fd == -1 || w == -1)

                return (-1);


        close(fd);


        return (1);

}






2-append_text_to_file.c


#include "main.h"


/**

 * append_text_to_file - Appends text at the end of a file.

 * @filename: A pointer to the name of the file.

 * @text_content: The string to add to the end of the file.

 *

 * Return: If the function fails or filename is NULL - -1.

 *         If the file does not exist the user lacks write permissions - -1.

 *         Otherwise - 1.

 */

int append_text_to_file(const char *filename, char *text_content)

{

        int o, w, len = 0;


        if (filename == NULL)

                return (-1);


        if (text_content != NULL)

        {

                for (len = 0; text_content[len];)

                        len++;

        }


        o = open(filename, O_WRONLY | O_APPEND);

        w = write(o, text_content, len);


        if (o == -1 || w == -1)

                return (-1);


        close(o);


        return (1);

}





3-cp.c


#include "main.h"

#include <stdio.h>

#include <stdlib.h>


char *create_buffer(char *file);

void close_file(int fd);


/**

 * create_buffer - Allocates 1024 bytes for a buffer.

 * @file: The name of the file buffer is storing chars for.

 *

 * Return: A pointer to the newly-allocated buffer.

 */

char *create_buffer(char *file)

{

        char *buffer;


        buffer = malloc(sizeof(char) * 1024);


        if (buffer == NULL)

        {

                dprintf(STDERR_FILENO,

                        "Error: Can't write to %s\n", file);

                exit(99);

        }


        return (buffer);

}


/**

 * close_file - Closes file descriptors.

 * @fd: The file descriptor to be closed.

 */

void close_file(int fd)

{

        int c;


        c = close(fd);


        if (c == -1)

        {

                dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);

                exit(100);

        }

}


/**
 * main - Copies the contents of a file to another file.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the argument count is incorrect - exit code 97.
 * If file_from does not exist or cannot be read - exit code 98.
 * If file_to cannot be created or written to - exit code 99.
 * If file_to or file_from cannot be closed - exit code 100.
 */
int main(int argc, char *argv[])
{
	int from, to, r, w;
        char *buffer;

        if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
                exit(97);
	}

	buffer = create_buffer(argv[2]);
        from = open(argv[1], O_RDONLY);
        r = read(from, buffer, 1024);
        to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);

	do {
                if (from == -1 || r == -1)
			dprintf(STDERR_FILENO,
                                "Error: Can't read from file %s\n", argv[1]);
                        free(buffer);
                        exit(98);
	}

	w = write(to, buffer, r);
	if (to == -1 || w == -1)
	{
		dprintf(STDERR_FILENO,
                                "Error: Can't write to %s\n",
				argv[2]);
		free(buffer);
                        exit(99);
	}

	r = read(from, buffer, 1024);
                to = open(argv[2], O_WRONLY | O_APPEND);

} while (r > 0);

free(buffer);
close_file(from);
close_file(to);

return (0);
}
