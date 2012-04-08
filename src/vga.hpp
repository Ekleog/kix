#ifndef vga_hpp_included
#define vga_hpp_included 1

#include "types.hpp"
#include "util.hpp"

namespace vga
{
  // {{{ max_c, max_r, max_i, (base_ptr, max_ptr)
  constexpr u32 max_c = 80;
  constexpr u32 max_r = 25;

  constexpr u32 max_i = max_c * max_r;

  constexpr byte *base_ptr = reinterpret_cast <byte *>(0xb8000);
  constexpr byte *max_ptr  = base_ptr + 2 * max_i;
  // }}}

  // {{{ color
  enum color : u8
  {
    black     = 0x00,
    dgray     = 0x08,
    lgray     = 0x07,
    white     = 0x0F,

    blue      = 0x01,
    lblue     = 0x09,
    cyan      = 0x03,
    lcyan     = 0x0B,

    red       = 0x04,
    lred      = 0x0C,
    magenta   = 0x05,
    lmagenta  = 0x0D,

    green     = 0x02,
    lgreen    = 0x0A,

    brown     = 0x06,
    yellow    = 0x0E
  };
  // }}}

  // {{{ pos
  constexpr u32 pos(u32 r, u32 c)
  {
    return r * max_c + c;
  }
  // }}}

  // {{{ fg, bg
  constexpr u8 fg(u8 c)
  {
    return c;
  }

  constexpr u8 bg(u8 c)
  {
    return static_cast <unsigned char>(c << 4);
  }
  // }}}

  // {{{ write
  // {{{ write(pos, char, [color])
  inline void write(u32 pos, char c)
  {
    *(reinterpret_cast <char *>(base_ptr + (pos << 1))) = c;
  }

  inline void write(u32 pos, char c, u8 color)
  {
    *(reinterpret_cast <char *>(base_ptr + (pos << 1))) = c;
    *(                          base_ptr + (pos << 1))  = color;
  }
  // }}}

  // {{{ write(pos, string, [color])
  inline void write(u32 pos, const char *c)
  {
    char * p = reinterpret_cast <char *>(base_ptr + (pos << 1));
    while (*c)
      {
        *p = *c;
        p += 2;
        ++c;
      }
  }

  inline void write(u32 pos, const char *c, u8 color)
  {
    u8 * p = base_ptr + (pos << 1);
    while (*c)
      {
        *(reinterpret_cast <char *>(p)) = *c;
        ++p; ++c;
        *p = color;
        ++p;
      }
  }
  // }}}
  // }}}

  // {{{ clear
  inline void clear(u8 color = 0x07)
  {
    u8 *p = base_ptr;
    while (p != max_ptr)
    {
      *p = ' ';
      ++p;
      *p = color;
      ++p;
    }
  }
  // }}}

  // {{{ move, hide
  inline void move(u32 pos)
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
