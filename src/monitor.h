#ifndef MONITOR_H
#define MONITOR_H

#include <X11/X.h>
#include "types.h"

struct gap_t {
  int isgap;
  int realgap;
  int gappx;
};

struct monitor_t {
  char ltsymbol[16];
  float mfact;
  int nmaster;
  int num;
  int by;
  int mx, my, mw, mh;
  int wx, wy, ww, wh;
  unsigned int seltags;
  unsigned int sellt;
  unsigned int tagset[2];
  int showbar;
  int topbar;
  gap_t *gap;
  client_t *clients;
  client_t *sel;
  client_t *stack;
  monitor_t *next;
  Window barwin;
  const layout_t *lt[2];
  bar_t bar;
};

monitor_t *createmon(void);
void cleanupmon(monitor_t *mon);

#endif // MONITOR_H
