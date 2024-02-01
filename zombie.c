#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	pid_t childPid;
	childPid = fork();

	if(childPid > 0){//parents
		printf("parents pid : %d\n", getpid());
		sleep(30);
		printf("parents termination\n");
		exit(0);
	}
	else if(childPid == 0){ //child
		printf("child\n");
		sleep(1);
		printf("child termination\n");
		exit(0);
	}
	else{
		perror("fork Fail!\n");
		return -1;
	}
	return 0;
}
