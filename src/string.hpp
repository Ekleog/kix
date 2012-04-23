#ifndef string_hpp_included
#define string_hpp_included 1

#include <stdint.h>

extern "C" inline uint_fast32_t __attribute__ ((pure)) strlen(const char *str)
{
   uint_fast32_t res = 0;

   while (*str) {
      ++str;
      ++res;
   }

   return res;
}

#endif
