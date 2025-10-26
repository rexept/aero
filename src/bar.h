#ifndef BAR_H
#define BAR_H

#include <X11/X.h>
typedef struct Bar {
  int bh;
  int lrpad;
  Window win;
} bar_t;

void init_bar(void);

#endif // BAR_H
