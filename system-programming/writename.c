#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#define BYTES 1024
#define FLAGS (O_RDWR | O_CREAT | O_TRUNC)
#define PERMS (S_IRUSR | S_IWUSR)

int writename(char *buf)
{
	int fd;
	char *path="./movie.txt";

	if ((fd=open(path,FLAGS,PERMS))==-1)
	{
		perror("Failed to open file");
		return 1;
	}
	
	write(fd,buf,BYTES);
	
	close(fd);

	return fd;
}
