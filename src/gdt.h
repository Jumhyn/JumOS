#ifndef _GDT_H
#define _GDT_H

#include "system.h"

struct gdt_entry {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
}__attribute__((packed));

struct gdt_ptr {
  uint16_t limit;
  struct gdt_entry *base;
}__attribute__((packed));

extern void gdt_flush();
void gdt_install();

#endif
