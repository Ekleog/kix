SECTIONS
{
   . = 0x00100000;
   loadbase = .;

   .text ALIGN (0x1000) :
   {
      *(.text)
      *(.gnu.linkonce.t*)
   }

   .rodata ALIGN (0x1000) :
   {
      start_ctors = .;
      *(.ctor*)
      end_ctors = .;

      start_dtors = .;
      *(.dtor*)
      end_dtors = .;

      *(.rodata*)
      *(.gnu.linkonce.r*)
   }

   .data ALIGN (0x1000) :
   {
      *(.data)
      *(.gnu.linkonce.d*)
   }

   .bss :
   {
      sbss = .;
      *(COMMON)
      *(.bss)
      *(.gnu.linkonce.b*)
      ebss = .;
   }

   /DISCARD/ :
   {
      *(.comment)
      *(.eh_frame) /* TODO: Add support for exceptions */
   }
}

