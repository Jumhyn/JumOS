#include "system.h"
#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "isrs.h"

#if defined(__cplusplus)
extern "C"
#endif

void kernel_main() {
  gdt_install();
  idt_install();
  isrs_install();
  terminal_initialize();
  terminal_writestring("Hello, kernel World!\n");
  terminal_writestring("Newlines Work!\n");
  uint32_t count = 0;
  for (; count < 20; count++) {
    terminal_putchar('c');
    terminal_putchar(' ');
    terminal_writeint(count);
    terminal_putchar('\n');
  }
  terminal_writestring("Scrolling works!\n");
}
