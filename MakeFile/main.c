#include<stdio.h>
#include"header.h"
void main(){
   int arr[5]={1,8,5,2,3};
   printf("Original Array is :\n");
   for( int i=0;i<5;i++){
     printf("%d",arr[i]);
     printf("\t");
   }
   int order=1;//sort in ascending order
   sort(arr,order);
   printf("\n");
   print(arr);
   int highest=2;
   printf("\n");
   findHighest(arr,highest);
   printf("\n");
}
