#ifndef _IDT_H
#define _IDT_H

#include "system.h"

struct idt_entry {
  uint16_t base_low;
  uint16_t selector;
  uint8_t zero;
  uint8_t flags;
  uint16_t base_high;
}__attribute__((packed));

struct idt_ptr {
  uint16_t limit;
  struct idt_entry *base;
}__attribute__((packed));

extern void idt_load(struct idt_ptr *);
void idt_install();
void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

#endif
