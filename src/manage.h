#ifndef MANAGE_H
#define MANAGE_H

#include "types.h"

void setfocus(client_t *c);
void focus(client_t *c);
void unfocus(client_t *c, int setfocus);

#endif // MANAGE_H
