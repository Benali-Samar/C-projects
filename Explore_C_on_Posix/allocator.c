#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define a block structure to represent allocated and free memory blocks
typedef struct Block {
    size_t size;
    struct Block* next;
} Block;

// Define a global pointer to the start of the heap
Block* head = NULL;

// Function to initialize the heap
void initialize() {
    head = (Block*)malloc(sizeof(Block));
    head->size = 0;
    head->next = NULL;
}

// Function to allocate memory
void* my_malloc(size_t size) {
    if (head == NULL) {
        initialize();
    }

    Block* current = head;
    while (current->next != NULL) {
        if (current->next->size >= size) {
            // Allocate memory from the current block
            Block* allocated_block = (Block*)((uint8_t*)current->next + sizeof(Block));
            allocated_block->size = size;
            allocated_block->next = NULL;
            current->next = (Block*)((uint8_t*)allocated_block + size);
            current->next->size = current->next->size - size - sizeof(Block);
            current->next->next = allocated_block->next;
            return allocated_block;
        }
        current = current->next;
    }

    // If no suitable block found, allocate new memory
    Block* new_block = (Block*)malloc(size + sizeof(Block));
    if (new_block == NULL) {
        return NULL; // Allocation failed
    }
    new_block->size = size;
    new_block->next = NULL;
    return (Block*)((uint8_t*)new_block + sizeof(Block));
}

// Function to deallocate memory
void my_free(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    // Find the block to deallocate
    Block* block_to_free = (Block*)((uint8_t*)ptr - sizeof(Block));
    block_to_free->next = NULL;

    // Merge consecutive free blocks
    Block* current = head;
    while (current->next != NULL) {
        if (current->next == block_to_free) {
            current->next = block_to_free->next;
            break;
        }
        current = current->next;
    }
}

int main() {
    // Test the memory allocator
    initialize();
    int* ptr1 = (int*)my_malloc(sizeof(int));
    int* ptr2 = (int*)my_malloc(sizeof(int));
    *ptr1 = 10;
    *ptr2 = 20;
    printf("Value at ptr1: %d\n", *ptr1);
    printf("Value at ptr2: %d\n", *ptr2);
    my_free(ptr1);
    my_free(ptr2);
    return 0;
}
