#ifndef BAR_H
#define BAR_H

#include <X11/X.h>

struct bar_t {
  int bh;
  int lrpad;
  Window win;
};

void init_bar(void);

#endif // BAR_H
