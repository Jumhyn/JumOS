#ifndef _SYSTEM_H
#define _SYSTEM_H
#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "You suck! Cross-compile!"
#endif

struct regs {
  uint32_t gs, fs, es, ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, useresp, ss;
}__attribute__((packed));

uint8_t *memcpy(uint8_t *, uint8_t *, size_t);
uint8_t *memset(uint8_t *, size_t, uint8_t);
uint16_t *memsetw(uint16_t *, size_t, uint16_t);
size_t strlen(const char *);

void gdt_install();
void idt_install();
void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);
void isrs_install();

#endif
