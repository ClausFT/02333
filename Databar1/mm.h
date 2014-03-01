/**
 * @file   mm.h
 * @Author Nicklas Bo Jensen (nboa@dtu.dk)
 * @date   January, 2014
 * @brief  Memory management skeleton header file.
 * 
 * Copyright 2013-14 Nicklas Bo Jensen, et. al., All rights reserved.
 *
 * You are allowed to change the file for the purpose of solving
 * exercises in the 02333 course at DTU. You are not allowed to
 * change this message or disclose this file to anyone except for
 * course staff in the 02333 course at DTU. Disclosing contents
 * to fellow course mates or redistributing contents is a direct
 * violation.
*/

#include <stddef.h>
#include <stdint.h>

/**
 * @name    embedded_malloc
 * @brief   Allocate at least size contiguous bytes of memory and return a pointer to the first byte.
 */
void* embedded_malloc(size_t size);


/**
 * @name    embedded_free
 * @brief   Frees previously allocated memory and make it available for subsequent calls to embedded_malloc.
 */
void embedded_free(void *ptr);


/**
 * @name    The lowest address of the memory you will manage
 * @brief   This points to the lowest address of memory you will manage
 */
extern const uintptr_t lowest_available_physical_memory;


/**
 * @name    The highest address of the memory you will manage
 * @brief   This points to the highest address of memory you will manage
 */
extern const uintptr_t top_of_available_physical_memory;


