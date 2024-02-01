#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int shmid;
	key_t key;
	char *shmaddr;
	
	key = ftok("helloshm",1);
	shmid = shmget(key, 1023, IPC_CREAT|0644); //shared memory create
	// using key and size of shared memory create
	//return created share memory's id
	if(shmid == -1){
		perror("shmget");
		exit(1);
	}
	printf("shmid : %d", shmid);
	shmaddr = (char *) shmat(shmid, NULL, 0); //shared memory connect
	//shmid (shared memory) and shmaddr connect and return address
	strcpy(shmaddr, "hello shared memory");

	return 0;
}
