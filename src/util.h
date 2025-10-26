#ifndef UTIL_H
#define UTIL_H

// clang-format off
#define MAX(A, B)               ((A) > (B) ? (A) : (B))
#define MIN(A, B)               ((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B)        ((A) <= (X) && (X) <= (B))
#define ISVISIBLE(C)            ((C->tags & C->mon->tagset[C->mon->seltags]))
/* Calculates how much a monitor's window area intersects with a given size and position.
 * See the writeup in the recttomon function for more information on this. */
#define INTERSECT(x,y,w,h,m)    (MAX(0, MIN((x)+(w),(m)->wx+(m)->ww) - MAX((x),(m)->wx)) \
                               * MAX(0, MIN((y)+(h),(m)->wy+(m)->wh) - MAX((y),(m)->wy)))
#define LENGTH(X)               (sizeof X / sizeof X[0])
// clang-format on

#include <X11/Xlib.h>

void die(const char *fmt, ...);
void checkotherwm(void);
void *ecalloc(size_t nmemb, size_t size);
int xerrorstart(Display *dpy, XErrorEvent *ee);

#endif // UTIL_H
