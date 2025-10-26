#ifndef MONITOR_H
#define MONITOR_H

#include "client.h"
#include "layout.h"

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
  client_t *clients;
  client_t *sel;
  client_t *stack;
  monitor_t *next;
  Window barwin;
  const Layout *lt[2];
}; 

#endif // MONITOR_H
