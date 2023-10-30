#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;fcntl.h&gt;

#define BUF_SIZE 1024

void exit_with_error(int code, const char *message, const char *arg);

int main(int argc, char *argv[])
{
int from_fd, to_fd, bytes_read, bytes_written;
char buffer[BUF_SIZE];

if (argc != 3)
exit_with_error(97, &quot;Usage: cp file_from file_to\n&quot;);

from_fd = open(argv[1], O_RDONLY);
if (from_fd == -1)
exit_with_error(98, &quot;Error: Can&#39;t read from file %s\n&quot;, argv[1]);

to_fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP);
if (to_fd == -1)
exit_with_error(99, &quot;Error: Can&#39;t write to file %s\n&quot;, argv[2);

while ((bytes_read = read(from_fd, buffer, BUF_SIZE)) &gt; 0)
{
bytes_written = write(to_fd, buffer, bytes_read);
if (bytes_written == -1)
exit_with_error(99, &quot;Error: Can&#39;t write to file %s\n&quot;, argv[2]);
}

if (bytes_read == -1)
exit_with_error(98, &quot;Error: Can&#39;t read from file %s\n&quot;, argv[1);

if (close(from_fd) == -1)
exit_with_error(100, &quot;Error: Can&#39;t close fd %d\n&quot;, from_fd);

if (close(to_fd) == -1)
exit_with_error(100, &quot;Error: Can&#39;t close fd %d\n&quot;, to_fd);

return 0;
}

void exit_with_error(int code, const char *message, const char *arg)
{
dprintf(STDERR_FILENO, message, arg);
exit(code);
}
