#ifndef quit_hpp_included
#define quit_hpp_included 1

extern "C" void __attribute__ ((noreturn)) shutdown();
extern "C" void __attribute__ ((noreturn)) panic(const char *msg);

#endif
