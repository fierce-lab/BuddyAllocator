#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* 
 * New implementation: One linked list, one bitmap
 */

/*
typedef struct _metadata {
    void *ptr;
    size_t size;
   // int free;
    struct _metadata *next;
    //struct _metadata_entry_t *prev;
} metadata;



metadata * freelist_head = NULL;
*/
//where do we store the metadata?  sbrk some memory for it?

/**
 * Allocate memory block
 *
 * Allocates a block of size bytes of memory, returning a pointer to the
 * beginning of the block. The content of the newly allocated block of
 * memory is not initialized, giving it indeterminate values.
 *
 * @param size
 *    Size of the memory block, in bytes.
 *
 * @return
 *    On success, a pointer to the memory block allocated by the function.
 *
 *    The type of this pointer is always void*, which can be cast to the
 *    desired type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory,
 *    a null pointer is returned.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/malloc/
 */
 
/*void * alloc(size_t size)
{
	//get the actual size that we are going to alloc
	size_t realsize = next_power_2(size);

	//search through the list of free blocks
	metadata * p = freelist_head;
	metadata * temp = NULL;
	void *chosen = NULL;
	
	while(p!=NULL)
	{
		if(p->size==realsize)
		{
			//find 
			chosen = p->ptr;
			if(temp==NULL)
			{
				//the first item on the free list fullfills required size
				freelist_head = p->next;
			}
			else
			{
				//delete current block from the free list
				temp->next=p->next
			}
			return chosen;
		}
		temp=p;
		p=p->next;
	}
	
//	nothing in the freelist, or no required size is find
    if(p==NULL)
    {
    	//if it's nothing in the freelist
    	//should alloc a new big block for buddy ==> double the size of current buddy
    	//what about the first time? sbrk?
    	freelist_head = sbrk(sizeof(struct _metadata));
    	//shall we alloc heap memory for this linked list? shall we alloc one node at a time or alloc enough memory for all the nodes
    	freelist_head->ptr = sbrk(size);
    	freelist_head->size=size;
    	freelist_head->next = NULL;
    	chosen = ptr;
    	
    	
    	
    	
    	//otherwise should look for bigger free block and split them until required size
    	
    	//how to track the parent block?
    	
    	//use bst? or several linked lists with different size?
    }
    return chosen;
} */

struct mem_buddy * merge(struct mem_buddy *mb, struct mem_buddy *mb2)
{
	
}
 
/*
	helper: next power of 2
	given the request size, return the power of 2 that is immediately bigger than size
	
	@param size
		given size of the memory block
		
	@return 
		the power of 2 that is immediately bigger than size
*/ 

size_t next_power_2(size_t size)
{
	int cursize =1;
	while(cursize<size)
		cursize*=2;
		
	return cursize;
	
	
	//should we use bitwise operation?
}



void * malloc(struct mem_buddy *mb, unsigned long order)
{
	if(mb==NULL)
		return NULL;
	
	if(order>mb->order)
	{
		//want to alloc a memory that's bigger than our current biggest buddy
		//alloc a new buddy, merge the two buddies
		struct mem_buddy *mb2;
		mem_init((mb->addr)+(1UL<<(mb->order)), mb->order,mb->min_size);
		mb = merge(struct mem_buddy *mb, struct mem_buddy *mb2);
		
	}
	if(order<mb->min_size)
	{
		order=mb->min_size;
	}
	
	unsigned long i;
	struct block* block;
	struct list_head * curlist;
	struct block* split_block;
	for(i=0;i<mb->order;i++)
	{
		//first fit
		curlist = &(mb->avail_blocks[i]);
		if(list_empty(curlist))
			continue;
		else
		{
			block = list_entry(list->next,block,block->link);
			list_del(&block->link);
			mark_allocated(mb,block);
		}
		while(block->order>order)
		{
			//split
			split_block = (struct block *)((unsigned long)block + (1UL << (block->order)));
			split_block->order = block->order;
			//mark available
			list_add(&(split_block->link));
		}
		return block		
	}
	return NULL;
}
 

/*
	helper: merge
	merge 2 free blocks together to make a bigger block
*/
 
/*
	helper: split
	split the larger memory block into 2 buddy blocks
*/

/*
	helper: Address_index
	creates an index value in the buddy allocator from the block's address
	used to find block's availability
*/

unsigned long address_index(struct mem_buddy *mb, struct block *block){
	unsigned long block_index, block;
	
    block_index = (block - mb->addr) >> mb->min_size;
    return block_index;
}

/*
	helper: mark_free
	the tag bit is set to 1, which makes the block available
	uses macro _set_bit
*/
void mark_free(struct mem_buddy *mb, struct block *block){
	_set_bit(address_index(mb,block),mb->bit_availability);
}

/*
	helper: mark_allocated
	the tag bit is set to 0, which makes the block allocated
	uses macro _clear_bit
*/
void mark_allocated(struct mem_buddy *mb, struct block *block){
	_clear_bit(address_index(mb, block), mb->bit_availability);
}

/* 
 * helper: checks availability of block
 * 
 * Specifically looks at a block to see if it is free or has been
 * allocated
 *
 * @param mem_buddy *mb
 *  Pointer passing reference to specific memory block. The block will 
 *  be merged or allocated based on its availability
 * 
 * @return
 *  If the memory block is free, then true is returned. If the block has
 *  been allocated, then false. 
 */
 
 int availablity(void *block)
 	//adds double negation to the test_bit so that only a 1/0 is returned
 	return test_bit(address_index(mb,block), mb->bit_availability) !! ( address_index(mb,block) & ( 1u << mb->bit_availability));
 }
 
 /**
  *helper: finds buddy block 
  * 
  *@param mem_buddy *mb
  * Pointer passing reference to specific memory block.
  *@param size
  * Size of the memory block, in bytes
  *
  *@return
  * Return address of the buddy of the memory block
  */
 
 void findBuddy(struct mem_buddy *mb, size_t size){
	unsigned long block, buddy;
   	
    	//make address 0 relative
    	block -= mb->addr;
    
    	//calculate buddy
    	buddy= block ^ (1UL << size);
    
    	return buddy;
 }
  
/**
 * Free a block of memory
 * 
 * A block of memory previously allocated using a call to alloc(),
 * is deallocated, making it available again for
 * further allocations.
 *
 *
 * @param ptr
 *    Pointer to a memory block previously allocated with alloc(),
 *   to be deallocated.  If a null pointer is
 *    passed as argument, no action occurs.
 */ 
 
void free(void *ptr)
{
	if (!ptr)
		return; 
		
	//find the block of memory that ptr points to
	// how do we find the metadata of ptr?
	
	//then add metadata of ptr into the linked list
}

/**
 * Initializes a buddy allocator object
 *
 * Required: addr (address of the base memory block), order (size of 
 * memory block), min_size (minimum size of block)
 *
 *@return
 * Pointer to initialized memory allocator
 * If this did not work, a null pointer is returned
 */
 
struct mem_buddy * mem_init(unsigned long addr, unsigned long order, unsigned long min_size){
 
    struct mem_buddy *mb;
    int i = 0;
    unsigned long j =1;
    
    //Check that the minimum size of block is smaller than the order
    if(min_size > order){
    	return NULL;
    }
    
    mb = malloc(size_t(struct mem_buddy));    //allocates for the buddy allocator
    mb->addr = addr;
    mb->order = order;
    mb->min_size = min_size;
    
    //Allocate linkedlist for every order
    mp->avail_blocks = malloc(size_t(struct list_head));
  
    //List should be empty in the beginning
    for(i=0; i <=order;i++){
    	INIT_LIST_HEAD(&mb->avail_blocks[i]); //Gets and initializes list head * of linkedlist
    }
    
    //Allocates bitmap
    mb->number_blocks = (j << order) /(j << min_size);
    
    //BITS_TO_LONGS file not included in .c file
    mb->bit_availability = malloc(BITS_TO_LONGS(mb->number_blocks)*sizeof(long));

	return mb;
}
