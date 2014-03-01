/**
 * @file   mm.c
 * @Author Nicklas Bo Jensen (nboa@dtu.dk)
 * @date   January, 2014
 * @brief  Memory management skeleton.
 * 
 * Copyright 2013-14 Nicklas Bo Jensen, et. al., All rights reserved.
 *
 * You are allowed to change the file for the purpose of solving
 * exercises in the 02333 course at DTU. You are not allowed to
 * change this message or disclose this file to anyone except for
 * course staff in the 02333 course at DTU. Disclosing contents
 * to fellow course mates or redistributing contents is a direct
 * violation.
 *
 * Replace the functions in this file with your own implementations.
 * You should not modify the function prototypes. 
 * 
 * As part of the assignment add new unit tests in 
 * check_mm.c.
 *
 */

#include <stdint.h>
#include "mm.h"

struct bookkeeping {
	int *is_initialized;
	int *allocated_blocks;
	char *bitmap;
};

struct bookkeeping bookkeeping;

typedef struct memory_block
{
	int size;
	uint8_t *start_address;
} memory_block;

/**
 * @name    embedded_malloc
 * @brief   Allocate at least size contiguous bytes of memory and return a pointer to the first byte.
 *
 * This function should behave similar to a normal malloc implementation.
 *
 * @param size_t size Number of bytes to allocate.
 * @retval Pointer to the start of the allocated memory.
 *
 */

void* embedded_malloc(size_t size) {
	/* Constants */
	const int TOTAL_MAX_SIZE = top_of_available_physical_memory - lowest_available_physical_memory;
	const int BOOKKEEPING_SIZE_MAX = (TOTAL_MAX_SIZE/32)+12;

	/* Structs */
	bookkeeping.is_initialized = (int*)lowest_available_physical_memory;
	bookkeeping.allocated_blocks = (int*)lowest_available_physical_memory+1;
	bookkeeping.bitmap = (char*)lowest_available_physical_memory+8;
	memory_block *allocated_memory = (memory_block*)top_of_available_physical_memory-1;

	/* Variables */
	int bitmap_reserve, empty_block, allocated_memory_size, bookkeeping_size_aligned, bookkeeping_size_rel;
	uint8_t *start_address = 0;
	allocated_memory_size = *bookkeeping.allocated_blocks * sizeof(memory_block) + sizeof(memory_block);
	bookkeeping_size_rel = BOOKKEEPING_SIZE_MAX - allocated_memory_size/32+1;

	/* Initialize */
	if (*bookkeeping.is_initialized != 0x13371337) {
		for(int i=0; i<BOOKKEEPING_SIZE_MAX-12; i++)
			bookkeeping.bitmap[i] = 0;

		*bookkeeping.allocated_blocks = 0;
		*bookkeeping.is_initialized = 0x13371337;
	}

	/* Check number of bits to reserve in bitmap. 1 bit in bitmap equals 32 bytes in memory */
	bitmap_reserve = size%32 == 0 ? size/32 : size/32+1;

	/* Check for empty spot in bitmap */
	for(int i=0; i<bookkeeping_size_rel; i++) {
		if(bookkeeping.bitmap[i] == 0) {
			if(bitmap_reserve == 1) { // <= If allocation is <= 32 bytes
				empty_block = 1;
			} else { // If allocation is > 32 bytes
				for(int a=1; a<bitmap_reserve; a++) {
					empty_block = bookkeeping.bitmap[i+a] == 0 ? 1 : 0;
					if(!empty_block) {
						i += a;
						break;
					}
				}
			}
			/* If an empty block was found */
			if(empty_block) {
				for(int a=0; a<bitmap_reserve; a++)
					bookkeeping.bitmap[i+a] = 1;

				/* Align bookkeeping size */
				bookkeeping_size_aligned = (BOOKKEEPING_SIZE_MAX%32 == 0) ? BOOKKEEPING_SIZE_MAX : BOOKKEEPING_SIZE_MAX + (32 - (BOOKKEEPING_SIZE_MAX%32));

				/* Calculate address */
				start_address = (uint8_t*)lowest_available_physical_memory + bookkeeping_size_aligned + i*32;

				while(allocated_memory->size > 0)
					allocated_memory--;

				allocated_memory->size = bitmap_reserve;
				allocated_memory->start_address = start_address;
				*bookkeeping.allocated_blocks += 1;
				break;
			}
		}
	}

	return start_address == 0 ? 0 : start_address;
}

/**
 * @name    embedded_free
 * @brief   Frees previously allocated memory and make it available for subsequent calls to embedded_malloc
 *
 * This function should behave similar to a normal free implementation. 
 *
 * @param void *ptr Pointer to the memory to free.
 *
 */
void embedded_free(void * ptr) {
	const int TOTAL_MAX_SIZE = top_of_available_physical_memory - lowest_available_physical_memory;
	const int BOOKKEEPING_SIZE = (TOTAL_MAX_SIZE/32)+12;
	bookkeeping.allocated_blocks = (int*)lowest_available_physical_memory+1;
	bookkeeping.bitmap = (char*)lowest_available_physical_memory+8;
	memory_block *allocated_memory = (memory_block*)top_of_available_physical_memory-1;
	int index, bookkeeping_size_aligned, counter=0;

	while ((allocated_memory->start_address != ptr) && (counter++<*bookkeeping.allocated_blocks))
		allocated_memory--;

	/* If the address was found */
	if (allocated_memory->start_address == ptr) {
		bookkeeping_size_aligned = (BOOKKEEPING_SIZE%32 == 0) ? BOOKKEEPING_SIZE : BOOKKEEPING_SIZE + (32 - (BOOKKEEPING_SIZE%32));
		index = ((int)allocated_memory->start_address - bookkeeping_size_aligned - lowest_available_physical_memory)/32;
		for (int a=0;  a<allocated_memory->size; a++)
			bookkeeping.bitmap[index++] = 0;

		*bookkeeping.allocated_blocks -= 1;
		allocated_memory->size = 0;
		allocated_memory->start_address = 0;
	}
}

/* Put any code you need to add here. */
