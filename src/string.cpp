#include "string.hpp"

#include <stdint.h>

extern "C" uint_fast32_t __attribute__ ((pure)) strlen(const char *str)
{
   uint_fast32_t res = 0;

   while (*str) {
      ++str;
      ++res;
   }

   return res;
}
