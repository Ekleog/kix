AUXFILES := Makefile config.mk
PROJDIRS := src
LOADER   := src/loader.s
LDFILE   := src/linker.ld
STAGES   := grub1.stage grub2.stage

CPPFILES := $(shell find $(PROJDIRS) -type f -name '*.cpp')
HPPFILES := $(shell find $(PROJDIRS) -type f -name '*.hpp')
ASMFILES := $(shell find $(PROJDIRS) -type f -name '*.s')

OBJFILES := $(patsubst %, build/%.o, $(CPPFILES) $(ASMFILES))
DEPFILES := $(patsubst %, build/%.d, $(CPPFILES) $(ASMFILES))
STGFILES := $(patsubst %, ext/%, $(STAGES))
OBJLDR   := build/$(LOADER).o

ALLFILES := $(AUXFILES) $(CPPFILES) $(HPPFILES) $(ASMFILES) $(LDFILE)

.PHONY: all mrproper clean dist todo

WARNINGS :=                                                          \
   -Wall -Wextra -Werror -Winline -Wdouble-promotion -Winit-self     \
   -Wmissing-include-dirs -Wswitch-default -Wstrict-overflow=5       \
   -Wsuggest-attribute=pure -Wsuggest-attribute=const                \
   -Wsuggest-attribute=noreturn -Wtrampolines -Wfloat-equal -Wundef  \
   -Wunsafe-loop-optimizations -Wpointer-arith -Wcast-qual           \
   -Wwrite-strings -Wconversion -Wsign-conversion -Wlogical-op       \
   -Wmissing-declarations -Wmissing-format-attribute -Wno-multichar  \
   -Wpadded -Wredundant-decls -pedantic -Winvalid-pch -Wvla          \
   -Wdisabled-optimization -Wstack-protector -Wcast-align            \
   -Wctor-dtor-privacy -Weffc++ -Wmissing-noreturn -Wnoexcept        \
   -Wold-style-cast -Woverloaded-virtual -Wpacked -Wpadded -Wreorder \
   -Wsign-promo -Wstrict-null-sentinel

CXXFLAGS := $(WARNINGS)                                              \
	-O3 -std=c++11 -nostdlib -fno-builtin -nostartfiles -nodefaultlibs\
	-fno-exceptions -fno-rtti -fno-stack-protector
ASMFLAGS := -Ox
 LDFLAGS := -O3 -T $(LDFILE)

IMG  := kix.img
PAD  := build/pad
BIN  := build/kernel.bin
TODO := TODO
TGZ  := src.tgz

TMPS  := $(OBJFILES) $(DEPFILES) $(PAD) $(BIN)
BUILT := $(TMPS) $(IMG) $(TGZ) $(TODO) $(STGFILES)

all: $(IMG) $(TODO)

# TODO: Include a better way of configuring make process
include config.mk
-include $(DEPFILES)

color =	@echo -e '\033[$(1)$(2)\033[0m'

mrproper:
	$(call color,31m,-> Removing all non-source files)
	-@$(RM) $(BUILT)

clean:
	$(call color,31m,-> Removing all temporary files)
	-@$(RM) $(TMPS)

dist: $(ALLFILES) Makefile
	$(call color,33m,-> Building $(TGZ))
	@tar czf $(TGZ) $(ALLFILES)

todo: $(TODO)
	@cat $(TODO)

$(TODO): $(ALLFILES) Makefile
	-@$(RM) $(TODO)
	-@for file in $(ALLFILES); do                                     \
	      grep -FHnT -e TODO -e FIXME $$file                          \
	      | grep -v '$$(TODO)'                                        \
	      | grep -v '-e TODO -e FIXME'                                \
	      | grep -v 'TODO := TODO'                                    \
	      | sed -e 's/:/\t:/'                                         \
	      >> $(TODO);                                                 \
	  done; true

$(IMG): $(STGFILES) $(PAD) $(BIN) Makefile
	$(call color,1;34m,-> Putting all together)
	@cat $(STGFILES) $(PAD) $(BIN) > $(IMG)

# TODO: Find a better way to download this
GRUB := grub-0.97-i386-pc
ext/%.stage:
	$(call color,35m,-> Downloading GRUB stages)
	@wget ftp://alpha.gnu.org/gnu/grub/$(GRUB).tar.gz
	@tar xzf $(GRUB).tar.gz
	@mv $(GRUB)/boot/grub/$(@:ext/grub%.stage=stage%) $@
	-@$(RM) -Rf $(GRUB).tar.gz $(GRUB)

# TODO: Compute the pad size from grub size
$(PAD): Makefile
	$(call color,35m,-> Creating padding file)
	@dd if=/dev/zero of=$(PAD) bs=1 count=750 2> /dev/null

$(BIN): $(OBJFILES) $(LDFILE) Makefile
	$(call color,32m,-> Linking to $(BIN))
	@$(LD) $(LDFLAGS) $(OBJLDR) $(OBJFILES:$(OBJLDR)=) -o $(BIN)

# mkdir / rmdir is a quick&dirty "hack" to create the directory for the .d
# TODO: Improve that
build/%.cpp.o: %.cpp Makefile
	$(call color,1;32m,-> Building $<)
	@mkdir -p $@ 2> /dev/null ; true
	@rmdir $@    2> /dev/null ; true
	@$(CXX) $(CXXFLAGS) -MD -MP -c $< -o $@

build/%.s.o: %.s Makefile
	$(call color,1;32m,-> Building $<)
	@mkdir -p $@ 2> /dev/null ; true
	@rmdir $@    2> /dev/null ; true
	@$(AS) $(ASMFLAGS) $< -f elf -o $@
