#include <stdio.h>
#include <my_malloc.h>
#include <string.h>

int main(){

  printf("test1 -- petit malloc simple\n");
  void *p1 = my_malloc(10);
  printf("p1 = %p\n", p1);
  
  printf("test2 -- plusieurs petits\n");
  void *p2 = my_malloc(20);
  void *p3 = my_malloc(30);
  printf("p2 : %p\n",p2);
  printf("p3 : %p\n",p3);
 
  printf("test 3 -- gros malloc seul\n");
  void *big = my_malloc(1000000);
  printf("big : %p\n",big);
 
 
  printf("test 4 -- petit puis gros\n");
  void *small = my_malloc(10);
  void *big2 = my_malloc(1000000);
  printf("small : %p\n",small);
  printf("big2 : %p\n",big2);

  printf("test 5 -- remplir puis gros\n");
  my_malloc(2000);
  my_malloc(2000);
  my_malloc(50000);


  printf("test 6 -- free puis realloc meme taille\n");
  void *a = my_malloc(100);
  printf("a (avant free): %p\n",a);
  my_free(a);
  void *b = my_malloc(100);
  printf("b (apres free): %p\n",b);

  printf("test 7 -- fusion avec next\n");
  void *x = my_malloc(100);
  void *y = my_malloc(100);
  void *z = my_malloc(100);

  my_free(y);
  my_free(x);/*doit fusionner avec y */
  void *xy = my_malloc(220);
  
  printf("xy : %p (devrait etre proche de x =%p)\n", xy , x);

  (void)z;


  printf("test 8 -- fusion avec prev \n");
  void *u = my_malloc(100);
  void *v = my_malloc(100);
  void *w = my_malloc(100);
  my_free(u);
  my_free(v);  // v doit fusionner avec u (via le branchement prev)
  (void)w;


  printf("\n");

  print_heap();





  return 0;


}
