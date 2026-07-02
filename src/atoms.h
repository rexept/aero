#ifndef ATOM_H
#define ATOM_H

#include "types.h"
#include <X11/X.h>
void init_atoms(void);
Atom getatomprop(client_t *c, Atom prop);


#endif // ATOM_H
