#include "system.h"
#include "terminal.h"

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

  for (size_t count = 0; count < 22; count++) {
    terminal_putchar('c');
    terminal_putchar(' ');
    terminal_writeint(count);
    terminal_putchar('\n');
  }
  //terminal_putchar('c');
  //terminal_putchar(' ');
  //terminal_writeint(21);
  //terminal_putchar('\n');
  terminal_writestring("Scrolling works!\n");
}
