#ifndef _PAGING_H
#define _PAGING_H

#include "system.h"
#include "isrs.h"

struct page {
  uint32_t present  : 1;
  uint32_t rw       : 1;
  uint32_t user     : 1;
  uint32_t accessed : 1;
  uint32_t dirty    : 1;
  uint32_t unused   : 7;
  uint32_t frame    : 20;
} __attribute__((packed));

struct page_table {
  struct page pages[1024];
} __attribute__((packed));

struct page_directory {
  struct page_table *tables[1024];

  uint32_t tables_physical[1024];

  uint32_t physical_addr;
} __attribute__((packed));

void paging_initialize();

void page_directory_switch(struct page_directory *);

struct page *page_get(uint32_t, int make, struct page_directory *);

void page_fault(struct regs *);

#endif
