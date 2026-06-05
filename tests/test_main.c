#include <stdio.h>
#include <my_malloc.h>

int main(){
 void *p1 = my_malloc(10);
 void *p2 = my_malloc(20);

 printf("p1 : %p\n",p1);
 printf("p2 : %p",p2);





 return 0;


}
