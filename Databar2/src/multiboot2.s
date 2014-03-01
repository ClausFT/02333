################################################################################
#
# File  : multiboot2.s
# Author: Sven Karlsson (svea@dtu.dk)
# Date  : January, 2014 
# Brief : Source code skeleton for databar assignment 2 in 02333.
#
# Copyright 2007-2014, Sven Karlsson, et. al., All rights reserved.
#
# You are allowed to change this file for the purpose of solving
# exercises in the 02333 course at DTU. You are not allowed to 
# change this message or disclose this file to anyone except for
# the course staff in the 02333 course at DTU. Disclosing the contents
# to fellow course mates or redistributing contents is a direct violation.
#

 .text
 .global _start
 .global _init
 .align  8

multiboot2_header:	
# Multiboot 2 header
 .int    0xe85250d6                         # Magic
 .int    0                                  # Architecture
 .int    multiboot2_header_end-multiboot2_header # Length
 .int    -(0xe85250d6+0+multiboot2_header_end-multiboot2_header) # Checksum
 .align  8

 .short  1                                  # Information request
 .short  0
 .int    8
 .int    0                                  # END
	                                    # The spec is not clear about if
	                                    # the END tag is needed but grub
	                                    # complains if it is not there.
 .align  8

# The last tag
 .short  0                                  # End tag
 .short  0
 .int    8
multiboot2_header_end:

 .align  4

/**
 * Entry point used by the multiboot 2 loader.
 */
 .align  4
_start:
 /* Disable interrupts. This should already been done by GRUB but lets be
    thorough. */
 cli

 jmp _init				# Jump to code in window.s
