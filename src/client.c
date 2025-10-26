#include "client.h"
#include "monitor.h"
#include "util.h"
#include "wm.h"

void detachstack(client_t *c) {
  client_t **tc, *t;

  for (tc = &c->mon->stack; *tc && *tc != c; tc = &(*tc)->snext)
    ;
  *tc = c->snext;

  if (c == c->mon->sel) {
    for (t = c->mon->stack; t && !ISVISIBLE(t); t = t->snext)
      ;
    c->mon->sel = t;
  }
}

void attach(client_t *c) {
  c->next = c->mon->clients;
  c->mon->clients = c;
}

void attachstack(client_t *c) {
  c->snext = c->mon->stack;
  c->mon->stack = c;
}

client_t *wintoclient(Window w) {
    client_t *c;
    monitor_t *m;

    for (m = g_wm->mons; m; m = m->next)
        for (c = m->clients; c; c = c->next)
            if (c->win == w)
                return c;

    return NULL;

}
