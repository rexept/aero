#ifndef MONITOR_H
#define MONITOR_H

#include "bar.h"
#include "client.h"
#include "layout.h"
typedef struct layout_t layout_t;

typedef struct {
  int isgap;
  int realgap;
  int gappx;
} Gap;

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
  Gap *gap;
  client_t *clients;
  client_t *sel;
  client_t *stack;
  monitor_t *next;
  Window barwin;
  const Layout *lt[2];
  const layout_t *lt[2];
  bar_t bar;
};

monitor_t *createmon(void);

#endif // MONITOR_H
