#ifndef compiler_hpp_included
#define compiler_hpp_included 1

#ifdef __GNUC__
#  define asm __asm__
#  define unreachable __builtin_unreachable
#else
// TODO : Use C++11 attribute syntax
#  error "Only GCC is supported at the moment !"
#endif

#endif
