# Lab 2 Report: Dynamic Allocator

## Authors: KHO Daniel, KAYANI Muhammad Sanaullah

## Testing platform:
    
    Personal Computer & University PC
    Linux (Ubuntu 22.04)
    CPU Type(Intel x_64)
## Implementation choices:
    Question 4.2

<br>

**(a) For the free list of your allocator, different designs are possible: using a singly linked list
can be sufficient but it also possible to choose a doubly linked list. In any case, describe one
advantage and one drawback for the choice that you have made.**

We have chosen a singly linked list. The advantage of a singly linked list is that you don't need to store the previous link, which saves both time and memory. However, a disadvantage of a singly linked list is that it doesn't support reverse iteration. If you want to move one step back, you have to use a temporary pointer and break the list. So, Our Header Size is 16 bytes for mb_free_t and 8 bytes for mb_allocated_t.


<br>

**(b) For this lab, the linked list of free blocks must be sorted by increasing block addresses. Describe one advantage and one drawback of this of this approach.**

The advantage of sorting the linked list of free blocks in increasing order is that we know the order of the memory blocks and it is easier to traverse through all the blocks while checking them. The drawback of this approach is it might be more time-consuming. For example, we are using the best-fit allocation policy and the block with the best fit is at the end of the memory pool. We have to iterate throught the whole memory pool and check each block. In contrast, if we sort the addresses by block size, we could get the best fit memory almost immeditaely without having to iterate through the whole memory pool.  
<br>

**Advantage :**
It allows for efficient search and allocation operations. When a new memory block needs to be allocated, the system can quickly find an appropriately sized free block with similar efficient search algorithm. This results in faster allocation times, making the memory management system more responsive and efficient.  
<br>

**Disadvantage:**
It requires additional effort and resources. Whenever a block is allocated or deallocated, the list must be adjusted to ensure that the blocks remain sorted by increasing addresses. Also, the cost of maintaining the sorted order might impact the overall performance of the system, especially in scenarios with a high frequency of memory allocation and deallocation operations.
<br>

## Implemented features:


- memory_init():
    Initialize the memory with MEM_POOL_SIZE and assign the pointer of first_free to this memory to keep track of the free memory.
    <br>

- memory_alloc():
    In this memory allocation function, we first check either the requested size is smaller than that of the first available free block. If it is, we allocate the memory from that free block. Otherwise, we iterate through the list of free blocks until we find an appropriate block, traversing the list until we reach the end of MEM_POOL_SIZE.
    <br>

- memory_free():
    This functions allows us to free previously allocated blocks. We start by checking whether the pointer(*p) is pointing to a valid memory block which means it has to validate the following constraints:

                            heap_start <= p <MEM_POOL_SIZE
    
    If this is valid then we can continue on the free this memory. After freeing this block, we check if the address of the first_free is bigger than this block. If it is, first_free will take this address and we return the address of the first_free block at the end of the function.

    **Confusion in alloc**: In theory, its easy to understand the concept of memory allocation theoratically. While implementing, we were confused that either we return the whole block or the block except header.
    <br>


- memory_get_allocated_block_size():
    This function allows us to get the size of an allocated memory block. When we want to free a block of memory, we will call this function to get the size of the block to free.
    <br>

- firstFit Policy:
    First Fit memory allocation policy is a simple and straightforward strategy. When allocating memory, it searches through the list of free memory blocks and uses the first block that is large enough to satisfy the request.
<br>

This C code snippet represents a basic implementation of the first-fit memory allocation policy. It iterates through a linked list of free memory blocks (mb_free_t) to find the first block that is large enough for the requested size. When found, it allocates memory from this block, updates the pointers, and reduces the free block's size. If no suitable block is found, it continues to the next free block. After allocating memory, it prints allocation information using print_alloc_info().

<br>

Inside the archive files containing our project are two directories named basic and advanced. The basic directory contains the source code for the basic memory allocator implemented wihtout any allocation policy. In the advanced directory, you can find the code with implementation policies. The program manages to pass the first two test scenarios successfully but starts facing some troubles from the third test onwards.

<br>

For our implementation, the size member of the structs (mb_allocated_t) and (mb_free_t) will include the size of the headers. The size that is requested when calling function memory_alloc() will only be the size of the payload. The operation of adding header size to size of payload will be done inside the function memory_alloc() itself.

<br>

**Memory Representation (For a closer look):**

We  tried to represent the memory in more readable tabular formate, where we can keey track of the Block, Address & Size in readable text (just to look at the memory state more closely).
                        
                        mb_free_t *curr = (mb_free_t*)i;
                        printf("Block %d: Address=%p, Size=%zu bytes\n", k, (void*)(curr + 1), curr->size); // Where K represent each byte of Memory

We also have the option to visualize the state of the memory using "." to represent free memory block and "X" to represent an allocated block.

<br>


## Problems faced:
1. A major problem we faced in this lab was accessing the right value of a pointer that was passed into a function. After allocating a memory block with memory_alloc() function, we return the whole structure of type (mb_allocated_t). However, when the pointer to the allocated block was passed into a function, and we tried accessing the "size" member of this struct, we get the address of the pointer instead of the size. (Resolved Later)
<br>

2. After freeing an occupied block, when we try to allocate a new block at the position of the newly freed block, we ended up allocating at the wrong position in the memory pool. Another situation is while allocationg new blocks after freeing some old blocks, it skips the first allocation but continues allocating the subsequent blocks.
<br>
