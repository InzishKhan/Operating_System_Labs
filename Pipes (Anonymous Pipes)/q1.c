#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>
int main(){
  char SBuff[]="Hi THere";
  int size=strlen(SBuff)+1;
  char RBuff[size];
  //making pipe
  int pipefd[2];
  pipe(pipefd);
  pid_t f1=fork();
  if(f1>0){ //parent Process
     close(pipefd[0]);
     printf("Parent Process [ID:%d]\n",getpid());
     write(pipefd[1],SBuff,size);
     close(pipefd[1]);
     wait(NULL);
  }
  else if (f1==0){ //child process
    close(pipefd[1]);
    read(pipefd[0],RBuff,size);
    printf("Child Process [ID:%d]\n ",getpid());
    printf("Orignal String: %s\n",SBuff);
    for (int i=0;RBuff[i]!='\0';i++){
        if(RBuff[i]>='a' && RBuff[i]<='z'){
             RBuff[i]=RBuff[i]-32;
        }
        else if (RBuff[i]>='A' && RBuff[i]<='Z'){
            RBuff[i]=RBuff[i]+32;
        }
        else{
            RBuff[i]=RBuff[i];
        }
    }
    printf("Message :%s\n",RBuff);
    close(pipefd[0]);
  }
  else{
    printf("Error in creating child:\n");
  }

  return 0;
}
