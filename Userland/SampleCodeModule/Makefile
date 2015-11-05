include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
ASMSOURCES=$(wildcard *.asm)
ASMOBJECTS=$(ASMSOURCES:.asm=.o)
ENTRYSRC=entry/main.c
ENTRYOBJ=entry/main.o

all: $(MODULE)

$(MODULE): $(OBJECTS) $(ASMOBJECTS) $(STATICLIBS) $(ENTRYOBJ)
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld -o ../$(MODULE) $(ENTRYOBJ) $(OBJECTS) $(ASMOBJECTS) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@
%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@
	
$(ENTRYOBJ): $(ENTRYSRC)
	$(GCC) $(GCCFLAGS) -c $(ENTRYSRC) -o $(ENTRYOBJ)



clean:
	rm -rf *.o
	rm -rf entry/*.o

.PHONY: all clean
