#ifndef LAYOUT_H
#define LAYOUT_H

#include "types.h"

struct layout_t {
	const char *symbol;
	void (*arrange)(monitor_t *);
};

#endif // LAYOUT_H
