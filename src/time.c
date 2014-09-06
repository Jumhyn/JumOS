#include "time.h"
#include "isrs.h"
#include "terminal.h"

uint32_t tick = 0;

static void timer_callback(struct regs *r) {
  tick++;
  terminal_writestring("Tick: ");
  terminal_writeint(tick);
  terminal_putchar('\n');
}

void timer_initialize(uint32_t freq) {
  register_interrupt_handler(IRQ(0), &timer_callback);
  
  uint32_t divisor = 1193180 / freq;

  outb(0x43, 0x36);

  uint8_t low = (uint8_t)(divisor & 0xFF);
  uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

  outb(0x40, low);
  outb(0x40, high);
}
