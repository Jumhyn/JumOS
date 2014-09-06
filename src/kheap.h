#ifndef _KHEAP_H
#define _KHEAP_H

#include "system.h"

uint32_t kmalloc(uint32_t sz, int align, uint32_t *phys);

#endif
