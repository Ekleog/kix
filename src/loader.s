global loader
 
extern kmain
 
MODULEALIGN equ  1<<0  ; align loaded modules on page boundaries
MEMINFO     equ  1<<1  ; provide memory map
VIDEOMODE   equ  1<<2  ; I provide video mode preferences
PROVIDELOCS equ  1<<16 ; I provide loading locations

FLAGS       equ  MODULEALIGN | MEMINFO
MAGIC       equ  0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)
 
section .text
 
align 4
   dd MAGIC
   dd FLAGS
   dd CHECKSUM
 
STACKSIZE equ 0x4000 ; 16k.
 
loader:
   mov   esp, stack + STACKSIZE
   push  eax ; Multiboot magic number
   push  ebx ; Multiboot info structure

   call  kmain

   ; Unreachable !
 
section .bss
 
align 4
stack:
   resb STACKSIZE
