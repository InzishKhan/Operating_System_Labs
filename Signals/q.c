#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include"header.h"
int nLaps=0;
int LapT=0;

int main(int argc,char *argv[]){
   printf("Enter the number of Laps: ");
   scanf("%d",&nLaps);
   printf("Enter Lap Time: ");
   scanf("%d",&LapT);
   if(signal(SIGCHLD,OWN_Handler)==SIG_ERR){
     printf("Cannot execute SIGCHILD\n");
   }
   pid_t p1;
   p1=fork();
   if(p1==0){ //child process
      for (int i=1;i<=nLaps;i++){
         printf("Lap: %d  Completed\n",i);
         alarm(nLaps);
         sleep(1);
      }
      exit(1);
   }
   else if(p1>0){
      wait(NULL);
   }
   else{
      printf("Error creating child\n");
      exit(0);
   }
   
   return 0;
}
