#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;fcntl.h&gt;

/**
* read_textfile - Reads a text file and prints it to the POSIX standard output.
* @filename: The name of the file to be read.
* @letters: The number of letters to read and print.
*
* Return: The actual number of letters it could read and print.
*/
ssize_t read_textfile(const char *filename, size_t letters)
{
int fd, bytes_read, bytes_written;
char *buffer;

if (filename == NULL)
return (0);

buffer = malloc(letters);
if (buffer == NULL)
return (0);

fd = open(filename, O_RDONLY);
if (fd == -1)
{
free(buffer);
return (0);
}

bytes_read = read(fd, buffer, letters);
if (bytes_read == -1)
{
free(buffer);
close(fd);
return (0);
}

close(fd);

bytes_written = 0;
while (bytes_written &lt; bytes_read)
{
if (_putchar(buffer[bytes_written]) == -1)
{
free(buffer);
return (0);
}

bytes_written++;
}

free(buffer);

if (bytes_written &lt; letters)
return (0);

return (bytes_read);
}
