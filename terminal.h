#ifndef _TERMINAL_H
#define _TERMINAL_H
#include "system.h"

enum vga_color {
  COLOR_BLACK = 0,
  COLOR_BLUE = 1,
  COLOR_GREEN = 2,
  COLOR_CYAN = 3,
  COLOR_RED = 4,
  COLOR_MAGENTA = 5,
  COLOR_BROWN = 6,
  COLOR_LIGHT_GREY = 7,
  COLOR_DARK_GREY = 8,
  COLOR_LIGHT_BLUE = 9,
  COLOR_LIGHT_GREEN = 10,
  COLOR_LIGHT_CYAN = 11,
  COLOR_LIGHT_RED = 12,
  COLOR_LIGHT_MAGENTA = 13,
  COLOR_LIGHT_BROWN = 14,
  COLOR_WHITE = 15,
};

uint8_t make_color(enum vga_color, enum vga_color);
uint16_t make_vgaentry(char, uint8_t);
void terminal_scrolldisplay();
void terminal_initialize();
void terminal_setcolor(uint8_t);
void terminal_putentryat(char, uint8_t, size_t, size_t);
void terminal_putchar(char);
void terminal_writestring(const char *);
void terminal_writeint(size_t);

#endif
