#ifndef _KB_H
#define _KB_H

#include "system.h"

enum kb_state_mask {
  KB_STATE_NONE = 0x0,
  KB_STATE_SHFT1 = (0x1 << 0),
  KB_STATE_SHFT2 = (0x1 << 1),
  KB_STATE_CTRL = (0x1 << 2),
  KB_STATE_OPTN = (0x1 << 3),
  KB_STATE_CAPS = (0x1 << 4),
};

enum kb_event_type {
  KB_EVENT_PRESS = 0x0,
  KB_EVENT_RELEASE = 0x80,
};

struct kb_event {
  enum kb_event_type type;
  uint8_t scancode;
  uint8_t keycode;
  char ascii;
};

void kb_initialize();

#endif
