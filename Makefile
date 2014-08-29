CC=i586-elf-gcc
AS=i586-elf-as
CFLAGS=-Wall -Wextra -O2 -ffreestanding -lgcc -nostdlib
CFLAGS2=-std=gnu99
CSOURCES=kernel.c gdt.c system.c interrupt.c isrs.c terminal.c
ASSOURCES=boot.s
OBJECTS=$(CSOURCES:.c=.o) $(ASSOURCES:.s=.o)
EXECUTABLE=jumos.bin
PACKAGER=grub-mkrescue
GRUBCFG=grub.cfg
ISODIR=isodir
PACKAGE=jumos.iso
DEPLOYPATH=/media/sf_Ubuntu-Shared

deploy: $(EXECUTABLE)
	cp $(EXECUTABLE) $(ISODIR)/boot/$(EXECUTABLE)
	cp $(GRUBCFG) $(ISODIR)/boot/grub/$(GRUBCFG)
	$(PACKAGER) -o $(PACKAGE) $(ISODIR)
	cp $(PACKAGE) $(DEPLOYPATH)/$(PACKAGE)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -T linker.ld $(CFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $(CFLAGS2) -c $< -o $@

.s.o:
	$(AS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
	rm -rf *~
	rm -rf \#*\#
	rm -rf *.iso