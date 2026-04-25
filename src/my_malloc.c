#include<stdio.h>
#include"my_malloc.h"


static my_stats *global_info = NULL;


/*if (global_info == NULL)
 * init(size) à ajouter dans le malloc plus tard*/

void init(size_t size){
  size_t total = sizeof(my_stats)+sizeof(area)+size;
  void ptr_1 = sbrk(total);
  
  global_info = (my_stats *)ptr_1;
  global_info -> magical_bytes = 0x42;
  global_info -> amount_of_blocks = 1;
  global_info -> amount_of_pages = 1;

  area *premier_bloc = (area*)(global_info + 1);
  /*En c si on ajoute 1 a un pointeur vers un structure, il saute exactement la taille de la strcuture*/
  premier_bloc -> inUse = false;
  premier_bloc -> prev = NULL;
  premier_bloc -> next = NULL;
  premier_bloc -> length = total - sizeof(my_stats) - sizeof(area);

}

void *my_malloc(size_t size){
  if(global_info) == NULL
    init(size);
  area *courant = (area *)(char *)(global_info+1);
  
  while courant!= NULL{
  if(!courant ->inUse && courant->length >=size){
  courant ->inUse = true;
  return courant+1;
  }
  courant = courant->next;
  }

  return NULL;
}
