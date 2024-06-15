This repository contains a simple memory management system implemented in C. 
The code provides basic functionality to allocate and free memory blocks within a statically allocated array. 
The system manages a fixed-size memory pool and allows for dynamic memory allocation and deallocation.
The main components include:
initialize(): Initializes the memory pool and sets up the initial free block.
split(): Splits a free block to allocate a smaller block.
My_Alloc(): Allocates a block of memory of the requested size.
merge(): Merges consecutive free blocks to reduce fragmentation.
My_Free(): Frees a previously allocated block of memory.
 First-fit algorithm  is used for memory allocation, block splitting, and merging to handle  fragmentation
