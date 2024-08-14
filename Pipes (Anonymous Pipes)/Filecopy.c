#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
int main(int argc,char ** argv){
  char *fileS = argv[1];
  char *fileD = argv[2];
  char Buff[100];
  char content[100];
  ssize_t SIZE;
  int pip[2];
  pipe(pip);
  pid_t pid1=fork();
  
  if(pid1>0){ //parent process created
     //close(pip[0]);
     //opening the source file
     ssize_t sfd=0;
     sfd=open(fileS,O_RDONLY);
     if(sfd==-1){
       printf("Error opening the file!");
       close(sfd);
       exit(0);
     }
     ssize_t byteR=0;
     while((byteR=read(sfd,Buff,sizeof(Buff))>0)){
        write(pip[1],Buff,sizeof(Buff));
     }
     wait(NULL);
     close(pip[1]);
     read(pip[0],&SIZE,sizeof(SIZE));
     read(pip[0],content,SIZE);
     content[SIZE]='\0';
     printf("[PARENT:%d] - Size of Content to Send: %ld\n",getpid(),SIZE);
     printf("[PARENT:%d] - Contents to send : %s\n",getpid(),content);
     close(pip[0]);
     close(pip[1]);
     close(sfd);  
  }
  else if(pid1==0){ //child process created
     ssize_t bytesR=0;
     bytesR=read(pip[0],content,sizeof(content));
     content[bytesR]='\0';
     SIZE=strlen(content);
     printf("[CHILD:%d] - Size of Content to Send: %ld\n",getpid(),SIZE);
     printf("[CHILD:%d] - Content Received: %.*s\n",getpid(),(int)bytesR,content);
     //opening the file to write into it 
     ssize_t fd=0;
     fd=open(fileD,O_WRONLY);
     if(fd==-1){
       printf("Error opening the file!");
       close(fd);
       exit(0);
     }
     ssize_t BYTE=0;
     BYTE=write(fd,content,SIZE);
     if(BYTE==-1){
       printf("Error writing to the file!");
       close(fd);
       close(pip[1]);
       close(pip[0]);
       exit(0);
     }
     write(pip[1],&SIZE,sizeof(SIZE)); //sending size of the content to the parent
     write(pip[1],content,sizeof(content)); //sending content back to the parent
     close(pip[1]);
     close(pip[0]);
  }
  else{
     printf("Error creating child!");
     close(pip[0]);
     close(pip[1]);
     exit(0);
  }
  

  return 0;
}
