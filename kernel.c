#include "system.h"
#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "paging.h"
#include "time.h"
#include "kb.h"

#if defined(__cplusplus)
extern "C"
#endif

void kernel_main() {
  gdt_install();
  idt_install();
  isrs_install();
  terminal_initialize();
  paging_initialize();
  //timer_initialize(50);
  kb_initialize();

  terminal_writestring("Hello, kernel World!\n");
  terminal_writestring("Newlines Work!\n");

  for(;;);

  PANIC("kernel main finished!");
}
