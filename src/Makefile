CC=i586-elf-gcc
AS=i586-elf-as
CFLAGS=-Wall -Wextra -O2 -ffreestanding -lgcc -nostdlib
CFLAGS2=-std=gnu99
CSOURCES=kernel.c gdt.c system.c idt.c isrs.c terminal.c time.c paging.c kheap.c kb.c
ASSOURCES=boot.s interrupt.s
OBJECTS=$(CSOURCES:.c=.o) $(ASSOURCES:.s=.o)
EXECUTABLE=jumos.bin
PACKAGER=grub-mkrescue
GRUBCFG=grub.cfg
LINKCFG=linker.ld
ISODIR=../isodir
PACKAGE=jumos.iso
DEPLOYPATH=/media/sf_Ubuntu-Shared

deploy: $(EXECUTABLE)
	cp $(EXECUTABLE) $(ISODIR)/boot/$(EXECUTABLE)
	cp ../cfg/$(GRUBCFG) $(ISODIR)/boot/grub/$(GRUBCFG)
	$(PACKAGER) -o ../bin/$(PACKAGE) $(ISODIR)
	cp ../bin/$(PACKAGE) $(DEPLOYPATH)/$(PACKAGE)
	cp $(EXECUTABLE) $(DEPLOYPATH)/$(EXECUTABLE)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -T ../cfg/$(LINKCFG) $(CFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $(CFLAGS2) -c $< -o $@

.s.o:
	$(AS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
	rm -rf *~
	rm -rf \#*\#

