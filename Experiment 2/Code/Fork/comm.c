// comm.c

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void sig_p(int dunno)
{
	printf("[System] Signal has been transmitted to the signal processing program.\n\tThe number of signal is: %d.\n", dunno);
}


int main()
{
	int pid, sum = 0, status = 0;

	char output[] = "result.txt";

	// bind the signal processing function and SIGUSR1
	signal(SIGUSR1, sig_p);

	// creating sub-process failed
	while((pid = fork()) == -1)
		;
	
	// father process
	if(pid)
	{
		char buffer[20] = {'\0'};
		int ret = 0;

		printf("[Father] This is the father process. My process number is: %d.\n", getpid());
		
		printf("[Father] Start calculating.\n");
		// main task: calculating
		for(int i = 0; i < 10000; ++i)
		{
			sum += i;
		}

		printf("[Father] Have got the sum.\n");

		// transport int to char
		sprintf(buffer, "%d", sum); 

		char str[] = "The result calculated by father is: ";

		char *final = (char*) malloc(strlen(str) + strlen(buffer) + 1);
		
		if (final == NULL)
		{
			// malloc fail
			printf("malloc memory failed.\n");
			exit(2);
		}

		strcpy(final, str);
		strcat(final, buffer);

		printf("[Father] What I will write is: %s.\n", final);

		FILE *out = fopen(output, "w");
		if(out == NULL)
		{
			printf("[Father] Open file %s fail.\n", output);
			exit(1);
		}
                
                fwrite(final, sizeof(char), strlen(final), out);
		// remember to close the file
		fclose(out);

		printf("[Father] Have written result to the file.\n");

		// send signal to child
		printf("[Father] Send the signal.\n");
		kill(pid, SIGUSR1);

		// father sleep
		printf("[Father] Start sleeping.\n");
		sleep(3);

		// test child process finished or not
		if( (waitpid(pid, NULL, WNOHANG)) == 0)
		{
			if( (ret = kill(pid, SIGKILL)) == 0)
				printf("[Father] Father have killed the child process: %d.\n", pid);
		}
		
		// pid = wait(&status);
		// printf("[Father] child process:%d, status:%d.\n", pid, status);

	}
	// children process
	else
	{
		printf("[Child] This is the child process. My process number is: %d; my father is: %d.\n", getpid(), getppid());

		// waiting for the signal
		pause();

		printf("[Child] Get the signal, ready to read the file.\n");

		FILE *in = fopen(output, "r");
		char readout[50] = {'\0'};

		fread(readout, sizeof(char), 50, in);
		fclose(in);

		// after getting the signal
	        printf("[Child] I get the result!\n");
		printf("[Child] The message in the file is:\n\t%s\n", readout);

		printf("[Child] Child sleep.\n");
		sleep(10);
		exit(3);
	}

	return 0;
}
