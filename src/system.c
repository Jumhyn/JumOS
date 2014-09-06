#include "system.h"
#include "terminal.h"

uint8_t *memcpy(uint8_t *dest, uint8_t *src, size_t size) {
  for (size_t i = 0; i < size; i++) {
    dest[i] = src[i];
  }
  return dest;
}

uint8_t *memset(uint8_t *dest, size_t size, uint8_t val) {
  for (size_t i = 0; i < size; i++) {
    dest[i] = val;
  }
  return dest;
}

uint16_t *memsetw(uint16_t *dest, size_t size, uint16_t val) {
  for (size_t i = 0; i < size; i++) {
    dest[i] = val;
  }
  return dest;
}

size_t strlen(const char *str) {
  size_t ret = 0;
  while (str[ret] != 0) {
    ret++;
  }
  return ret;
}

void panic(const char *file, uint32_t line, const char *reason) {
  asm volatile ("cli");
  terminal_writestring("KERNEL PANIC in ");
  terminal_writestring(file);
  terminal_writestring(" on line ");
  terminal_writeint(line);
  terminal_writestring("\n");
  terminal_writestring(reason);
  for(;;);
}
