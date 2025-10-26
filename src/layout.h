#ifndef LAYOUT_H
#define LAYOUT_H

typedef struct monitor_t monitor_t;

typedef struct {
	const char *symbol;
	void (*arrange)(monitor_t *);
} Layout;

#endif // LAYOUT_H
