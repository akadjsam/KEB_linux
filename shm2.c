#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
	int shmid;
	char *shmptr1, *shmptr2;
	int i;
	
	shmid = shmget(IPC_PRIVATE, 10*sizeof(char), IPC_CREAT|0666); //create shared memory
	if(shmid == -1){
		printf("shmget failed\n");
		exit(0);
	}
	// now create process
	if(fork()==0){
		shmptr1 = (char *) shmat(shmid, NULL, 0);//shared memory connect, reference
		for(i=0;i<10;i++)
			shmptr1[i] = i*10;
		shmdt(shmptr1); //child process connect with shared memory, reference clear
		exit(0);
	}
	else{//parent process
		wait(NULL);
		shmptr2 = (char *) shmat(shmid, NULL, 0);
		for(i=0;i<10;i++)
			printf("%d\n", shmptr2[i]);
		shmdt(shmptr2); //child process connect with shared memory, reference clear
		if(shmctl(shmid, IPC_RMID, NULL) == -1) //shared memory control, IPC_RMID delete shared memory in os
			printf("shmctl failed!\n");
	}
	return 0;
}
