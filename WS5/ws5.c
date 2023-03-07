#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	pid_t pid;
	
	for(int i = 0; i < 4; i++){
		pid = fork();
		
		if(pid == 0){
			printf("Hello world from PID %d!\n", getpid());
			return 0;
		}
	}
	
	return 0;
}
