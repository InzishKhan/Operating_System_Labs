#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>
int main(){
  int pipe1[2]; //for sending first message
  int pipe2[2]; //for sending sum of the received message
  pid_t pid1;
  int arr[]={1,5,7,2,15};
  int arr2[5];
  int noE=5;
  int sum=0;
  int size=sizeof(int)*noE; //calculating size of array in bytes for further system call
  pipe(pipe1);
  pipe(pipe2);
  pid1=fork();
  if(pid1>0){ //parent process created
     close(pipe1[0]);
     close(pipe2[1]);
     write(pipe1[1],arr,size);
     close(pipe1[1]);
     wait(NULL);
     read(pipe2[0],&sum,sizeof(sum));
     close(pipe2[0]);
     printf("Sum received from the child is: %d\n",sum);
  }
  else if(pid1==0){  //child process created
     close(pipe1[1]);
     close(pipe2[0]);
     read(pipe1[0],arr2,size);
     for (int i=0;i<noE;i++){
        sum+=arr2[i];
     }
     close(pipe1[0]);
     write(pipe2[1],&sum,sizeof(sum));
     close(pipe2[1]);
     exit(0);
     
  }
  else{ //no process created
     printf("Error creating child!\n");
     exit(0);
  }
  return 0;
}
