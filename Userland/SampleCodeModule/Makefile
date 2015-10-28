include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
ASMSOURCES=$(wildcard *.asm)
ASMOBJECTS=$(ASMSOURCES:.asm=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS) $(ASMOBJECTS) $(STATICLIBS)
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld -o ../$(MODULE) $(OBJECTS) $(ASMOBJECTS) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@
%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@



clean:
	rm -rf *.o

.PHONY: all clean