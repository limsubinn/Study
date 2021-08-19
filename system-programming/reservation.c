#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int password(void);
int writename(char *buf);
int printname(int fd);
void printtime(void);


int main()
{
	int ans;
	int p;
	int n;

	char list[][20]={
		"titanic",
		"matrix",
		"aladin",
		"parasite"
	}; 

	atexit(printtime);

	while(1)
	{
		printf("Would you like to add a movie? (1:YES, 2:NO): ");
		scanf("%d",&ans);

		if (ans==1)
		{
			p=password();
			if (p>=4)
				continue;
			else
			{
				printf("Add movie name: ");
				scanf("%s",list[4]);
				n=5;
				break;
			}
		}
		else if (ans==2)
		{
			n=4;
			break;
		}
		else 
			printf("You have to enter 1 or 2\n");

	}
	
	int i=0;
	int num;
	int fd;

	printf("================================\n");
	for (i=0;i<n;i++)
		printf("%d. %s\n",i+1,list[i]);
	printf("================================\n");
	
	while(1)
	{
		printf("Choose the movie you want(number): ");
		scanf("%d",&num);

		if ((num>=1)&&(num<=n))
		{
			int size=strlen(list[num-1]);
			char s[size];
			for (i=0;i<size;i++)
			{
				s[i]=list[num-1][i];
				printf("%c",s[i]);
			}
			char *buf=s;
			fd=writename(buf);
			break;
		}
		else
			printf("You have to enter 1~%d\n",n);
	}

	printf("\nThank you~~~^^ Enjoy your movie!\n");
	printname(fd);
	exit(1);
}

void printtime(void) 
{
	FILE *myfd;
	struct stat statbuf;
	char *path="./movie.txt";

	if ((myfd=fopen(path,"r"))==NULL)
	{
		perror("failed to open file");
	}
	else
	{
		if (stat(path,&statbuf)==-1)
			perror("Failed to get file status");
		else 
			printf("%s",ctime(&statbuf.st_ctime));
	}

	while ((fclose(myfd)==-1)&&(errno==EINTR));
}


