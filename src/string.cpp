#include "string.hpp"

#include "types.hpp"

extern "C" u32 __attribute__ ((pure)) strlen(const char *str)
{
  u32 res = 0;

  while (*str)
    {
      ++str;
      ++res;
    }

  return res;
}
