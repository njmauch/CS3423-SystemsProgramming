#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

#include <errno.h>
#include <string.h>

#include <stdlib.h>
#include <stdarg.h>

#define ERR_EXIT 999
void errExit(const char szFmt[], ...);
int main(int argc, char *argv[])
{
	long lForkPid;
	long lWaitPid;
	int iExitStatus = 0;
	char *command[5];
	int i;
	int j = 0;

	for (i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], ",") == 0)
		{
			j++;
			continue;
		}
		strcat(command[j], argv[i]);
	}
	for (i = 0; i < j; i++)
	{
		printf("%s\n", command[j]);
	}
	/*
	for(i = 0; i < j; i++)
	{
	  lForkPid = fork();
	  switch(lForkPid)
	  {
		case -1:
		  errExit("fork failed: %s", strerror(errno));
		case 0:
		  printf("PID: %ld, PPID: %ld, CMD: %s\n", (long) getpid(), (long) getppid(), command[0]);
		  break;
		default:
		  printf("PID: %ld, PPID: %ld, CMD: %s\n", (long) getpid(), (long) getppid(), command[0]);
	  }
	}*/
	return 0;
}

void errExit(const char szFmt[], ...)
{
	va_list args;               // This is the standard C variable argument list type
	va_start(args, szFmt);      // This tells the compiler where the variable arguments
								// begins.  They begin after szFmt.
	printf("ERROR: ");
	vprintf(szFmt, args);       // vprintf receives a printf format string and  a
								// va_list argument
	va_end(args);               // let the C environment know we are finished with the
								// va_list argument
	printf("\n");
	exit(ERR_EXIT);
}