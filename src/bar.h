#ifndef BAR_H
#define BAR_H

#include <X11/X.h>
#include "types.h"

struct bar_t {
  int bh;
  int lrpad;
  char stext[256];
  Window win;
};

void init_bars(void);
void updatebars(void);
void updatestatus(void);
void drawbar(monitor_t *m);
void drawbars(void);

#endif // BAR_H
