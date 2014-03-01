/*

 File  : link32.ld
 Author: Sven Karlsson (svea@dtu.dk)
 Date  : January, 2014 
 Brief : Source code skeleton for databar assignment 2 in 02333.

 Copyright 2007-2014, Sven Karlsson, et. al., All rights reserved.

 You are allowed to change this file for the purpose of solving
 exercises in the 02333 course at DTU. You are not allowed to 
 change this message or disclose this file to anyone except for
 the course staff in the 02333 course at DTU. Disclosing the contents
 to fellow course mates or redistributing contents is a direct violation.

 */

OUTPUT_ARCH ( "i386" )
OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)

PHDRS
{
 text PT_LOAD FILEHDR PHDRS FLAGS(5);
 data PT_LOAD FLAGS(6);
}

SECTIONS
{
  . = SIZEOF_HEADERS;

  /* You can make to image to be much more compact. This link script
     was done so that it is remotely possible to read. It is complex 
     but could have been much more complex.*/
  .text (0x00100000 + SIZEOF_HEADERS) :
   AT (0x00100000 + SIZEOF_HEADERS)
  {
    * (.*text) /* All text sections. */
  } : text

  .data (ADDR(.text) + SIZEOF (.text)) :
   AT (LOADADDR(.text) + SIZEOF (.text))
  {
   * (.*data) /* All data sections including read-only data. */ 
  } : data

  .bss (ADDR(.data) + SIZEOF (.data)) :
   AT (LOADADDR(.data) + SIZEOF (.data))
  {
   * (.bss)  /* Any remaining bss sections. */
  }
 
  /* Various debug sections. */
  .stab 0 : 
  { 
   * (.stab)
  }
  .stabstr 0 :
  { 
   * (.stabstr)
  }
  .stab.excl 0 :
  { 
   * (.stab.excl)
  }
  .stab.exclstr 0 :
  {
   * (.stab.exclstr)
  }
  .stab.index 0 :
  {
   * (.stab.index)
  }
  .stab.indexstr 0 :
  {
   * (.stab.indexstr)
  }
  .comment 0 :
  {
   * (.comment)
  }
  .debug 0 :
  {
   * (.debug)
  }
  .line 0 :
  {
   * (.line)
  }
  .debug_srcinfo 0 :
  {
   * (.debug_srcinfo)
  }
  .debug_sfnames 0 :
  {
   * (.debug_sfnames)
  }
  .debug_aranges 0 :
  {
   * (.debug_aranges)
  }
  .debug_pubnames 0 :
  {
   * (.debug_pubnames)
  }
  .debug_info 0 :
  {
   * (.debug_info .gnu.linkonce.wi.*)
  }
  .debug_abbrev 0 :
  {
   * (.debug_abbrev)
  }
  .debug_line 0 :
  {
   * (.debug_line)
  }
  .debug_frame 0 :
  {
   * (.debug_frame)
  }
  .debug_str 0 :
  {
   * (.debug_str)
  }
  .debug_loc 0 :
  {
   * (.debug_loc)
  }
  .debug_macinfo 0 :
  {
   * (.debug_macinfo)
  }
  .debug_weaknames 0 :
  {
   * (.debug_weaknames)
  }
  .debug_funcnames 0 :
  {
   * (.debug_funcnames)
  }
  .debug_typenames 0 :
  {
   * (.debug_typenames)
  }
  .debug_varnames 0 :
  {
   * (.debug_varnames)
  }
  .debug_pubtypes 0 :
  {
   * (.debug_pubtypes)
  }
  .debug_ranges 0 :
  {
   * (.debug_ranges)
  }
  .gnu.attributes 0 :
  { 
   KEEP (* (.gnu.attributes))
  }

  /DISCARD/ :
  {
   * (.note.GNU-stack)
   * (.gnu_debuglink)
   * (*)
  }
}
