#include "kb.h"
#include "isrs.h"
#include "terminal.h"

enum kb_state_mask state = 0;
uint8_t escape = 0;

char asciilowermap[128] = {
  '\0', //error
  '\0', //esc
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
  '\0', //delete 
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 
  '\n',
  '\0', //lctrl
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
  '`',
  '\0', //lshift
  '\\',
  'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
  '\0', //rshift
  '*',
  '\0', //alt
  ' ',
  '\0', //caps
  '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', //F1-F10
  '\0', //numlock
  '\0', //scrolllock
  '7', '8', '9',
  '-',
  '4', '5', '6',
  '+',
  '1', '2', '3',
  '0',
  '.',
};

char asciiuppermap[128] = {
  '\0', //error
  '\0', //esc
  '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
  '\0', //delete 
  '\0', //backtab
  'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 
  '\n',
  '\0', //lctrl
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"',
  '~',
  '\0', //lshift
  '|',
  'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',
  '\0', //rshift
  '*',
  '\0', //alt
  ' ',
  '\0', //caps
  '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', //F1-F10
  '\0', //numlock
  '\0', //scrolllock
  '7', '8', '9',
  '-',
  '4', '5', '6',
  '+',
  '1', '2', '3',
  '0',
  '.',
};

struct kb_event kb_event_create(uint8_t scancode) {
  struct kb_event ret;
  ret.scancode = scancode;
  ret.type = scancode & 0x80;
  ret.keycode = scancode & 0x7F;

  switch (ret.keycode) {
  case 42:
    if (ret.type == KB_EVENT_PRESS) {
      state |= KB_STATE_SHFT1;
    }
    else {
      state &= ~(KB_STATE_SHFT1);
    }
    break;
  case 54:
    if (ret.type == KB_EVENT_PRESS) {
      state |= KB_STATE_SHFT2;
    }
    else {
      state &= ~(KB_STATE_SHFT2);
    }
    break;
  case 58:
    if (ret.type == KB_EVENT_RELEASE) {
      state ^= KB_STATE_CAPS;
    }
    break;
  default:
    break;
  }

  char ascii = '\0';
  if (state & KB_STATE_SHFT1 || state & KB_STATE_SHFT2 || state & KB_STATE_CAPS) {
    ascii = asciiuppermap[ret.keycode];
    if (state & KB_STATE_CAPS && !ascii) {
      ascii = asciilowermap[ret.keycode];
    }
  }
  else {
    ascii = asciilowermap[ret.keycode];
  }
  
  ret.ascii = ascii;

  return ret;
}

void kb_interrupt(struct regs *r) {
  uint8_t scancode = inb(0x60);

  if (scancode == 0xE0) {
    escape = scancode;
    return;
  }

  struct kb_event event = kb_event_create(scancode);

  terminal_handle_kb_event(event);

#if DEBUG
  terminal_writestring("KB EVENT - scancode: ");
  terminal_writehex(event.scancode, 1);
  terminal_writestring(" keycode: ");
  terminal_writehex(event.keycode, 1);
  terminal_writestring(" 0x0-press/0x80-release: ");
  terminal_writehex(event.type, 1);
  terminal_writestring(" ascii: ");
  terminal_putchar(event.ascii);
  terminal_writestring("\n");
#endif
}

void kb_initialize() {
  register_interrupt_handler(IRQ(1), &kb_interrupt);
}
