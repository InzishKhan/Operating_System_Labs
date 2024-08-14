#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main(int argc,char* argv[]){
   printf("Process ID before execution of execv: %d\n",getpid());
   char *args[]={"./my_info",NULL};
   execv(args[0],args);
   printf("Error executing another process\n");
   return 1;
}
