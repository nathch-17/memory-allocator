#include <stdio.h>
#include <unistd.h> 

#include "my_malloc.h"

static my_stats *global_info = NULL;

void split(area* block, size_t size){
  
  area *nouveau_bloc = (area*)((uint8_t*)block+sizeof(area)+size);
  block -> inUse = true;
  area* ancien_next = block -> next;
  uint32_t ancien_length = block-> length;
  
  if(ancien_next != NULL ){
    ancien_next -> prev = nouveau_bloc;
    }
    
  /*si ancien next pas null, son prev doit pointer vers nouveau_bloc et non plus vers block*/
  block -> next = nouveau_bloc;

  block -> length = size;
  /*block -> prev =  deja fait*/
  
  nouveau_bloc -> inUse = false;
  nouveau_bloc -> prev = block;
  nouveau_bloc -> length = ancien_length - size - sizeof(area);
  nouveau_bloc -> next = ancien_next;
  
  global_info -> amount_of_pages ++;

}

void init(size_t size){
  int page_size = getpagesize();

  /*Réserve une zone de mémoire pour inscrire toute les donées nécessaire pour le bloc global et le petit bloc ainsi que l'epsace demandé par l'utilisateur*/
  size_t besoin = sizeof(my_stats)+sizeof(area)+size;
  int nb_pages = (besoin+page_size-1)/page_size;
  size_t total = nb_pages*page_size;
  void* ptr_1 = sbrk(total);
  
  global_info = (my_stats *)ptr_1;
  global_info -> magical_bytes = 0x42;
  global_info -> amount_of_blocks = 1;
  global_info -> amount_of_pages = nb_pages;

  area *premier_bloc = (area*)(global_info + 1);
  /*En c si on ajoute 1 a un pointeur vers un structure, il saute exactement la taille de la strcuture*/
  premier_bloc -> inUse = false;
  premier_bloc -> prev = NULL;
  premier_bloc -> next = NULL;
  premier_bloc -> length = total - sizeof(my_stats) - sizeof(area);
}

void *my_malloc(size_t size){
  if(global_info == NULL)
    init(size);

  area *courant = (area*)(global_info+1);
  
  while (courant!= NULL){
    
    if(!courant ->inUse && courant->length >=size){
     
      courant ->inUse = true;
      /*vérfifier si on peut splitter */
      if(courant -> length >= size + sizeof(area) +1){
        split(courant,size);
      }
      
      return (void*) (courant+1); /*renvoi un pointeur vers le début de la zone utilisable du bloc alloué*/
    }

   
      if(courant->next == NULL){
        
        area* ptr_prev = courant; 
        size_t total = (sizeof(area)+size);
   
        void* ptr = sbrk(total);
   
        if(ptr == (void *)-1) return NULL;
    

        area* nouveau_bloc = (area*)(ptr);
        
        nouveau_bloc -> next = NULL;
        nouveau_bloc -> length = total - sizeof(area);
        nouveau_bloc -> prev = ptr_prev;
        ptr_prev -> next = nouveau_bloc;
        

        nouveau_bloc -> inUse = true;


        return (void*)(nouveau_bloc+1); /*renvoi pointeur vers la nouvelle zone utilisable */

    

      }
  courant = courant->next; /*si taille insuffisante passe au prochain bloc*/
 
  }

return NULL;
}
