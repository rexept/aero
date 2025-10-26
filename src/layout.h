#ifndef LAYOUT_H
#define LAYOUT_H

typedef struct monitor_t monitor_t;

typedef struct {
	const char *symbol;
	void (*arrange)(monitor_t *);
} layout_t;

#endif // LAYOUT_H
