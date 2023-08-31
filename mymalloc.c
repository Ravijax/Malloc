#include <stdio.h>
#include <stddef.h>
#include "mymalloc.h"

Block *freelist = (void*)memory;

void Initialize()
{
    freelist->size = MEM_SIZE - sizeof(Block);          //creating the 1st meta data block        
    freelist->free = 1; 
    freelist->next = NULL;
}
  

void split(Block *current, size_t size)
{
    Block *new_block = (void*)current + size + sizeof(Block);      //creating a new block
    new_block->size = current->size - (size + sizeof(Block));      //initializing the size of the new block        
    new_block->free = 1;                                           //freeing the new block
    new_block->next = current->next;                               //pointing the new block to the next block
    current->free = 0;
    current->next = new_block;                                     //pointing the current block to the new block
}


void Merge(void *curr)
{
    Block *curr_block = curr;
    Block *next_block = curr_block->next;
    Block *prev_block = freelist;

    //Merging with the right adjacent free block
    if((next_block != NULL) && next_block->free)
    {
        curr_block->size += next_block->size + sizeof(Block);       //merging two free blocks
        curr_block->next = next_block->next;                        //pointing the current block to the next block
        printf("Merged with right adjacent free block!\n");
    }

    //Merging with the left adjacent free block
    while ((prev_block != NULL) && (prev_block->next != curr_block))
    {
        prev_block = prev_block->next;                              //traversing memory blocks till the previous block 
    }
    if (prev_block != NULL && prev_block->free)
    {
        prev_block->size += sizeof(Block) + curr_block->size;       //merging two free blocks
        prev_block->next = curr_block->next;
        printf("Merged with left adjacent free block!\n");
    }
}


void *MyMalloc(size_t size)
{
    Block *curr;
    void *result;

    if(!(freelist->size))               //if the memory is empty
    {
        Initialize();
        printf("Memory has been Initialized!\n");
    }

    curr = freelist;                    //curr points to the starting point of the memory

    while (curr != NULL)
    {
        if ((curr->size >= size) && (curr->free))
        {
            if (curr->size > (size + sizeof(Block)))
            {
                split(curr, size);                      //spliting the current free block
            }
            curr->size = size;                          //allocating the memory
            curr->free = 0;
            printf("Memory Allocated!\n");
            result = (void*)++curr;                     //incrementing the curr pointer to the starting location of the allocated block
            return result;                              //returning the address of the starting location to the ptr pointer 
        }
        curr = curr->next;                              //travers the pointer from the curr block to the next block
    }
    printf("Failed to Allocate Memory!\n");
    return NULL;
}


void MyFree(void *ptr)
{
    if(((void*)memory <= ptr) && (((void*)memory + 25000) >= ptr))      //checking the boundaries of the memory(array)
    {
        Block *curr = ptr;
        --curr;
        curr->free = 1;                                                 //freeing the current memory block
        printf("Memory has been Freed!\n");
        Merge(curr);
    }
    else                                                                //if the pointer is not within the memory boundaries 
    {
        printf("Provide a valid pointer!\n");      
    }
}