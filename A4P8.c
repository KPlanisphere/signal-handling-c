#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main() {
	int pid, i=10;
	if((pid=fork())==0){
		while(i!=0)
		{
		printf("HIJO, PID = %d\n", getpid());
		i--;
		sleep(1);
		}
	}
	else{
		sleep(10);
		printf("PADRE. Terminacion del proceso %d\n", getpid());
		kill (pid, SIGTERM);
	}
	exit(0);
}

