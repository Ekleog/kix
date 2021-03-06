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

ISO      := kix.iso

ISODIR   := build/iso
PAD      := build/pad
BIN      := $(ISODIR)/boot/kix.bin
TODO     := TODO
TGZ      := src.tgz

TMPS     := $(OBJFILES) $(DEPFILES) $(PAD) $(BIN)
BUILT    := $(TMPS) $(ISO) $(TGZ) $(TODO) $(STGFILES)

.PHONY: all mrproper clean dist todo builddirs

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

CXXFLAGS := $(WARNINGS) -ffreestanding                   				\
	-O3 -std=c++11 -nostdlib -fno-builtin -nostartfiles -nodefaultlibs\
	-fno-exceptions -fno-rtti -fno-stack-protector -masm=intel			\
	$(CXXFLAGS)
ASMFLAGS := -Ox $(ASMFLAGS)
LDFLAGS  := -O3 -T $(LDFILE) --oformat=binary $(LDFLAGS)

all: $(ISO) $(TODO)

# TODO: Include a better way of configuring make process
include config.mk
-include $(DEPFILES)

$(shell [ -d "$(ISODIR)/boot/grub" ] || mkdir -p $(ISODIR)/boot/grub)
$(shell [ -d "build/src" ] || mkdir -p build/src)
$(shell [ -d "ext" ] || mkdir -p ext)

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

$(ISO): $(STGFILES) $(PAD) $(BIN) Makefile
	$(call color,1;34m,-> Putting all together)
	@grub-mkrescue -o $(ISO) $(ISODIR) > /dev/null 2>&1

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
