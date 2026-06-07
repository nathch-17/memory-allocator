#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include <stdlib.h>



struct free_area{

    uint8_t marker;               //The marker at the beginning is a fixed number which indicates that the structure has been initialized
    struct free_area *prev;
    bool inUse;
    uint32_t length;
    struct free_area *next;

};

struct stats{
    uint8_t magical_bytes;
    bool simple_lock; // to avoid race condition
    uint32_t amount_of_blocks;
    uint8_t amount_of_pages;

};
typedef struct stats my_stats ;
typedef struct free_area area;

void* my_malloc(size_t size);
void my_free(void* ptr);

my_stats* get_global_info(void);
void print_heap();

