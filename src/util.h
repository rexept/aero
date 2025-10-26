#ifndef UTIL_H
#define UTIL_H

// clang-format off
#define MAX(A, B)               ((A) > (B) ? (A) : (B))
#define MIN(A, B)               ((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B)        ((A) <= (X) && (X) <= (B))
#define ISVISIBLE(C)            ((C->tags & C->mon->tagset[C->mon->seltags]))
#define LENGTH(X)               (sizeof X / sizeof X[0])
// clang-format on

#include <X11/Xlib.h>

void die(const char *fmt, ...);
void checkotherwm(void);
void *ecalloc(size_t nmemb, size_t size);
int xerrorstart(Display *dpy, XErrorEvent *ee);

#endif // UTIL_H
