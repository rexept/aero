#ifndef EVENT_H
#define EVENT_H

#include "types.h"
#include <X11/X.h>

int sendevent(client_t *c, Atom proto);

#endif // EVENT_H
