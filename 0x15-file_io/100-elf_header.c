#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;fcntl.h&gt;
#include &lt;elf.h&gt;

void exit_with_error(int code, const char *message);

int main(int argc, char *argv[])
{
int fd;
Elf64_Ehdr elf_header;

if (argc != 2)
exit_with_error(98, &quot;Usage: elf_header elf_filename\n&quot;);

fd = open(argv[1], O_RDONLY);
if (fd == -1)
exit_with_error(98, &quot;Error: Cannot open file %s\n&quot;, argv[1]);

if (read(fd, &amp;elf_header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
exit_with_error(98, &quot;Error: Cannot read ELF header from file %s\n&quot;, argv[1]);

if (elf_header.e_ident[EI_MAG0] != ELFMAG0 || elf_header.e_ident[EI_MAG1] != ELFMAG1 ||
elf_header.e_ident[EI_MAG2] != ELFMAG2 || elf_header.e_ident[EI_MAG3] != ELFMAG3)
exit_with_error(98, &quot;Error: Not an ELF file: %s\n&quot;, argv[1]);

printf(&quot; Magic: &quot;);
for (int i = 0; i &lt; EI_NIDENT; i++)
printf(&quot;%02x%c&quot;, elf_header.e_ident[i], (i &lt; EI_NIDENT - 1) ? &#39; &#39; : &#39;\n&#39;);

printf(&quot; Class: %s\n&quot;,
(elf_header.e_ident[EI_CLASS] == ELFCLASS64) ? &quot;ELF64&quot; : &quot;ELF32&quot;);
printf(&quot; Data: %s\n&quot;,
(elf_header.e_ident[EI_DATA] == ELFDATA2LSB) ? &quot;2&#39;s complement, little-endian&quot; : &quot;2&#39;s
complement, big-endian&quot;);
printf(&quot; Version: %d (current)\n&quot;, elf_header.e_ident[EI_VERSION]);
printf(&quot; OS/ABI: %d\n&quot;, elf_header.e_ident[EI_OSABI]);
printf(&quot; ABI Version: %d\n&quot;, elf_header.e_ident[EI_ABIVERSION]);
printf(&quot; Type: %s\n&quot;,
(elf_header.e_type == ET_EXEC) ? &quot;EXEC (Executable file)&quot; :
(elf_header.e_type == ET_DYN) ? &quot;DYN (Shared object file)&quot; :
(elf_header.e_type == ET_REL) ? &quot;REL (Relocatable file)&quot; :
&quot;Unknown&quot;);
printf(&quot; Entry point address: 0x%lx\n&quot;, (unsigned long)elf_header.e_entry);

close(fd);
return 0;

}

void exit_with_error(int code, const char *message)
{
dprintf(STDERR_FILENO, message);
exit(code);
}
