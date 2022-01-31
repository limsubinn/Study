#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#define BYTES 1024

int printname(int fd) 
{

	char buf[BYTES];
	
	int numread=0;
	int returnval;

	while (numread < BYTES - 1)
	{
		returnval = read(fd, buf + numread, 1);
		if ((returnval == -1) && (errno == EINTR))
			continue;
		if ( (returnval == 0) && (numread == 0) )
			return 0;
		if (returnval == 0)
			break;
		if (returnval == -1)
			return -1;
		numread++;
 		if (buf[numread-1] == '\n') 
		{
			buf[numread] = '\0';
			return numread;
		}
	}
	errno = EINVAL;
	
	write(STDOUT_FILENO,buf,BYTES);
}
