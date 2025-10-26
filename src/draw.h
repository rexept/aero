#ifndef DRAW_H
#define DRAW_H

#ifdef XINERAMA
#include <X11/extensions/Xinerama.h>
static int isuniquegeom(XineramaScreenInfo *unique, size_t n,
                        XineramaScreenInfo *info);
#endif /* XINERAMA */

// TODO: simplify
int updategeom(void);

#endif // DRAW_H
