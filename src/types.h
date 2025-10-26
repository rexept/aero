#ifndef TYPES_H
#define TYPES_H

typedef struct client_t client_t;
typedef struct monitor_t monitor_t;
typedef struct bar_t bar_t;
typedef struct gap_t gap_t;
typedef struct wm_t wm_t;
typedef struct layout_t layout_t;

enum { CurNormal, CurResize, CurMove, CurLast };
enum { SchemeNorm, SchemeSel };
enum {
  NetSupported,
  NetWMName,
  NetWMState,
  NetWMCheck,
  NetWMFullscreen,
  NetActiveWindow,
  NetWMWindowType,
  NetWMWindowsOpacity,
  NetWMWindowTypeDialog,
  NetClientList,
  NetLast
};
enum { WMProtocols, WMDelete, WMState, WMTakeFocus, WMLast };
enum {
  ClkTagBar,
  ClkLtSymbol,
  ClkStatusText,
  ClkWinTitle,
  ClkClientWin,
  ClkRootWin,
  ClkLast
};

typedef union {
  int i;
  unsigned int ui;
  float f;
  const void *v;
} Arg;

#endif // TYPES_H
