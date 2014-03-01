/**
 * @file   mm.c
 * @Author Laust Brock-Nannestad (laub@dtu.dk)
 * @date   January, 2013
 * @brief  Memory management skeleton.
 * 
 * Copyright 2013-14 Laust Brock-Nannestad, et. al., All rights reserved.
 *
 * You are allowed to change the file for the purpose of solving
 * exercises in the 02333 course at DTU. You are not allowed to
 * change this message or disclose this file to anyone except for
 * course staff in the 02333 course at DTU. Disclosing contents
 * to fellow course mates or redistributing contents is a direct
 * violation.
 *
 * This file contains low level initialization of memory. You should
 * not need to edit this file as part of the assignment.
 *
 */

#include "mm.h"
#include <stdlib.h>
#include <assert.h>


/**
 * @name    ALLOCATE_SIZE
 * @brief   Amount of memory available for allocation, 32MB.
 *
 */
#define ALLOCATE_SIZE    32*1024*1024

static int8_t memory[ALLOCATE_SIZE];

const uintptr_t lowest_available_physical_memory = (uintptr_t) memory;
const uintptr_t top_of_available_physical_memory = (uintptr_t) memory + ALLOCATE_SIZE;
