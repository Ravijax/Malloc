#include<stdio.h>
#include<stddef.h>

#define MEM_SIZE 25000          

char memory[MEM_SIZE];          //initializing the memory of 25000 bytes

typedef struct Block {
    size_t size;                //size of the newly creating block
    int free;                   //boolien value to see it the block is free or not
    struct block *next;         //pointer to the next memory block
}Block;


#ifndef MY_MALLOC_H
#define MY_MALLOC_H

void Initialize();
void split(Block *fitting_slot, size_t size);
void *MyMalloc(size_t size);
void Merge();
void MyFree(void *ptr);

#endif
