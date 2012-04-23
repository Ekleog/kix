#ifndef pic_hpp_included
#define pic_hpp_included 1

#include <stdint.h>

namespace pic
{
   void remap(uint8_t off1 = 0x50, uint8_t off2 = 0x58);
}

#endif
