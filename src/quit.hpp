#ifndef quit_hpp_included
#define quit_hpp_included 1

void __attribute__ ((noreturn)) shutdown();
void __attribute__ ((noreturn)) panic(const char *msg);

#endif
