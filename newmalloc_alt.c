#include <stdio.h>
#include "mymalloc.h"

#define MEM_SIZE 25000
char memory[MEM_SIZE];
typedef struct Block
{
    size_t size;
    int isfree; // 1 - free , 0 - allocated
    struct Block *next;
} Block;

Block *free_list;

void *MyMalloc(size_t size)
{
    if (!free_list)
    {
        free_list = (Block *)memory;
        free_list->size = MEM_SIZE - sizeof(Block);
        free_list->isfree = 1;
        free_list->next = NULL;
    }

    Block *curr = free_list;
    while (curr != NULL)
    {
        if (curr->size >= size && curr->isfree)
        {
            if (curr->size > size + sizeof(Block))
            {
                Block *new_block = (Block *)((char *)curr + sizeof(Block) + size);
                new_block->size = curr->size - sizeof(Block) - size;
                new_block->isfree = 1;
                new_block->next = curr->next;
                curr->next = new_block;
            }
            curr->size = size;
            curr->isfree = 0;
            printf("Memory allocated!!!\n");
            return (void *)(curr + 1);
        }
        curr = curr->next;
    }
    printf("Failed to allocate memory!!!\n");
    return NULL;
}

// void MyFree(void* ptr) {
//     Block* curr = (Block*) ptr - 1;
//     curr->isfree = 1;
//     printf("Memory freed!!!\n");
// }

void MyFree(void *ptr)
{
    Block *curr = (Block *)ptr - 1;
    curr->isfree = 1;
    printf("Memory freed!!!\n");

    Block *next_block = curr->next;
    if (next_block != NULL && next_block->isfree)
    {
        curr->size += sizeof(Block) + next_block->size;
        curr->next = next_block->next;
        printf("Merged with right adjacent free block\n");
    }

    Block *prev_block = free_list;
    while (prev_block != NULL && prev_block->next != curr)
    {
        prev_block = prev_block->next;
    }
    if (prev_block != NULL)
    {
        Block *prev_next_block = prev_block->next;
        if (prev_block->isfree && prev_next_block != NULL)
        {
            prev_block->size += sizeof(Block) + prev_next_block->size;
            prev_block->next = prev_next_block->next;
            printf("Merged with left adjacent free block\n");
        }
    }
}
