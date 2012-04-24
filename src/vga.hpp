#ifndef vga_hpp_included
#define vga_hpp_included 1

#include <stdint.h>
#include "asm.hpp"

namespace vga
{
   // {{{ max_c, max_r, max_i, (base_ptr, max_ptr)
   constexpr uint32_t max_c = 80;
   constexpr uint32_t max_r = 25;

   constexpr uint32_t max_i = max_c * max_r;

   constexpr uint8_t *base_ptr = reinterpret_cast <uint8_t *>(0xb8000);
   constexpr uint8_t *max_ptr  = base_ptr + 2 * max_i;
   // }}}

   // {{{ color
   enum color : uint8_t
   {
      black    = 0x00,
      dgray    = 0x08,
      lgray    = 0x07,
      white    = 0x0F,

      blue     = 0x01,
      lblue    = 0x09,
      cyan     = 0x03,
      lcyan    = 0x0B,

      red      = 0x04,
      lred     = 0x0C,
      magenta  = 0x05,
      lmagenta = 0x0D,

      green    = 0x02,
      lgreen   = 0x0A,

      brown    = 0x06,
      yellow   = 0x0E
   };
   // }}}

   // {{{ pos
   constexpr uint32_t pos(uint32_t r, uint32_t c)
   {
      return r * max_c + c;
   }
   // }}}

   // {{{ fg, bg
   constexpr uint8_t fg(uint8_t c)
   {
      return c;
   }

   constexpr uint8_t bg(uint8_t c)
   {
      return static_cast <uint8_t>(c << 4);
   }
   // }}}

   // {{{ write
   // {{{ write(pos, char, [color])
   inline void write(uint32_t pos, char c)
   {
      *(reinterpret_cast <char *>(base_ptr + (pos << 1))) = c;
   }

   inline void write(uint32_t pos, char c, uint8_t color)
   {
      *(reinterpret_cast <char *>(base_ptr + (pos << 1))) = c;
      *(                      1 + base_ptr + (pos << 1))  = color;
   }
   // }}}

   // {{{ write(pos, string, [color])
   inline void write(uint32_t pos, const char *str)
   {
      char * ptr = reinterpret_cast <char *>(base_ptr + (pos << 1));
      while (*str)
      {
         *ptr = *str;
         ptr += 2;
         ++str;
      }
   }

   inline void write(uint32_t pos, const char *str, uint8_t color)
   {
      uint8_t * ptr = base_ptr + (pos << 1);
      while (*str)
      {
         *(reinterpret_cast <char *>(ptr)) = *str;
         ++ptr; ++str;
         *ptr = color;
         ++ptr;
      }
   }
   // }}}
   // }}}

   // {{{ clear
   inline void clear(uint8_t color = 0x07)
   {
      uint8_t *ptr = base_ptr;
      while (ptr != max_ptr)
      {
         *ptr = ' ';
         ++ptr;
         *ptr = color;
         ++ptr;
      }
   }
   // }}}

   // {{{ move, hide
   inline void move(uint32_t pos)
   {
      outb(0x3d4, 0x0F);
      outb(0x3d5, pos & 0xFF);
      outb(0x3d4, 0x0E);
      outb(0x3d5, (pos >> 8) & 0xFF);
   }

   inline void hide()
   {
      move(max_i);
   }
   // }}}
}

#endif
