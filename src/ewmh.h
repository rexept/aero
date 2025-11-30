#ifndef EWMH_H
#define EWMH_H

#include "types.h"

void init_ewmh_support_window(void);
void init_ewmh_root_properties(void);
void seturgent(client_t *c, int urg);

#endif // EWMH_H
