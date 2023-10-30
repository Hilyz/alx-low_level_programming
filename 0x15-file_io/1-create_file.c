#include &lt;fcntl.h&gt;
#include &lt;unistd.h&gt;

/**
* create_file - Creates a file with specified permissions and writes text content.
* @filename: The name of the file to create.
* @text_content: The NULL-terminated string to write to the file.
*
* Return: 1 on success, -1 on failure.
*/
int create_file(const char *filename, char *text_content)

{
int fd, write_result;
mode_t file_permissions = S_IRUSR | S_IWUSR; // rw-------

if (filename == NULL)
return -1;

fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, file_permissions);
if (fd == -1)
return -1;

if (text_content != NULL)
{
write_result = write(fd, text_content, strlen(text_content));
if (write_result == -1)
{
close(fd);
return -1;
}
}

close(fd);
return 1;
}#include &lt;fcntl.h&gt;
#include &lt;unistd.h&gt;

/**
* create_file - Creates a file with specified permissions and writes text content.
* @filename: The name of the file to create.
* @text_content: The NULL-terminated string to write to the file.
*
* Return: 1 on success, -1 on failure.
*/
int create_file(const char *filename, char *text_content)
{
int fd, write_result;
mode_t file_permissions = S_IRUSR | S_IWUSR; // rw-------

if (filename == NULL)
return -1;

fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, file_permissions);
if (fd == -1)
return -1;

if (text_content != NULL)
{
write_result = write(fd, text_content, strlen(text_content));
if (write_result == -1)
{

close(fd);
return -1;
}
}

close(fd);
return 1;
}
