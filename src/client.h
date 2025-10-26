#ifndef CLIENT_H
#define CLIENT_H

#include <X11/X.h>
#include "types.h"

struct client_t {
  char name[256];
  float mina, mixa;
  int x, y, w, h;
  int oldx, oldy, oldw, oldh;
  int basew, baseh, incw, inch, maxw, maxh, minw, minh, hintsvalid;
  int bw, oldbw;
  unsigned int tags;
  int isfixed, isfloating, isurgent, neverfocus, oldstate, isfullscreen;
  client_t *next;
  client_t *snext;
  monitor_t *mon;
  Window *win;
};

void detachstack(client_t *c);
void attach(client_t *c);
void attachstack(client_t *c);
#endif // CLIENT_H
