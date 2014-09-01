#include "paging.h"
#include "kheap.h"
#include "terminal.h"

struct page_directory *kernel_directory = 0;
struct page_directory *current_directory = 0;

uint8_t *frames;
uint32_t nframes;

extern uint32_t placement_address;

#define BYTE_INDEX(a) (a/8)
#define BIT_OFFSET(a) (a%8)

static void frame_set(uint32_t frame_addr) {
  uint32_t frame = frame_addr / 0x1000;
  frames[BYTE_INDEX(frame)] |= (0x1 << BIT_OFFSET(frame));
}

static void frame_clear(uint32_t frame_addr) {
  uint32_t frame = frame_addr / 0x1000;
  frames[BYTE_INDEX(frame)] &= ~(0x1 << BIT_OFFSET(frame));
}

static uint8_t frame_test(uint32_t frame_addr) {
  uint32_t frame = frame_addr / 0x1000;
  return (frames[BYTE_INDEX(frame)] & (0x1 << BIT_OFFSET(frame)));
}

static uint32_t frame_first() {
  uint32_t i, j;
  for (i = 0; i < BYTE_INDEX(nframes); i++) {
    if (frames[i] != 0xFF) {
      for (j = 0; j < 8; j++) {
	if (!(frames[i] & (0x1 << j))) {
	  return i * 8 + j;
	}
      }
    }
  }
  return (uint32_t)-1;
}

void frame_alloc(struct page *page, int is_kernel, int is_writable) {
  if (page->frame) {
    return;
  }
  uint32_t index = frame_first();
  if (index == (uint32_t)-1) {
    PANIC("No free frames!");
  }
  frame_set(index * 0x1000);
  page->present = 1;
  page->rw = (is_writable) ? 1 : 0;
  page->user = (is_kernel) ? 0 : 1;
  page->frame = index;
}

void frame_free(struct page *page) {
  uint32_t frame;
  if (!(frame = page->frame)) {
    return;
  }
  frame_clear(frame);
  page->frame = 0x0;
}

void paging_initialize() {
  uint32_t mem_end_page = 0x1000000;

  nframes = mem_end_page / 0x1000;
  frames = (uint8_t *)kmalloc(BYTE_INDEX(nframes), 0, 0);
  memset((uint8_t *)frames, BYTE_INDEX(nframes), 0);

  kernel_directory = (struct page_directory *)kmalloc(sizeof(struct page_directory), 1, 0);
  memset((uint8_t *)kernel_directory, sizeof(struct page_directory), 0);
  current_directory = kernel_directory;

  uint32_t i = 0;
  while (i < placement_address) {
    frame_alloc(page_get(i, 1, kernel_directory), 0, 0);
    i += 0x1000;
  }

  register_interrupt_handler(14, &page_fault);

  page_directory_switch(kernel_directory);
}

void page_directory_switch(struct page_directory *dir) {
  current_directory = dir;
  asm volatile ("mov %0, %%cr3" :: "r"(&dir->tables_physical));
  uint32_t cr0;
  asm volatile ("mov %%cr0, %0" : "=r"(cr0));
  cr0 |= 0x80000000;
  asm volatile ("mov %0, %%cr0" :: "r"(cr0));
}

struct page *page_get(uint32_t addr, int make, struct page_directory *dir) {
  addr /= 0x1000;

  uint32_t table_index = addr / 1024;

  if (dir->tables[table_index]) {
    return &dir->tables[table_index]->pages[addr % 1024];
  }
  else if (make) {
    uint32_t tmp;
    dir->tables[table_index] = (struct page_table *)kmalloc(sizeof(struct page_table), 1, &tmp);
    memset((uint8_t *)dir->tables[table_index], 0x1000, 0);
    dir->tables_physical[table_index] = tmp | 0x7;
    return &dir->tables[table_index]->pages[addr % 1024];
  }
  return 0;
}

void page_fault(struct regs *r) {
  uint32_t fault_addr;
  asm volatile ("mov %%cr2, %0" : "=r"(fault_addr));

  int present = !(r->err_code & 0x1);
  int rw = r->err_code & (0x1 << 1);
  int us = r->err_code & (0x1 << 2);
  int reserved = r->err_code & (0x1 << 3);
  int id = r->err_code & 0x10;

  terminal_writestring("Page fault! ( ");
  if (present) terminal_writestring("present ");
  if (rw) terminal_writestring("read-only ");
  if (us) terminal_writestring("user-mode ");
  if (reserved) terminal_writestring("reserved ");
  terminal_writestring(") at ");
  terminal_writehex(fault_addr, 1);
  terminal_writestring("\n");
  PANIC("Page fault");
}
