#ifndef CONFIG_H
#define CONFIG_H

#include "layout.h"
#include "monitor.h"
#include "types.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef struct {
  const char *class;
  const char *instance;
  const char *title;
  unsigned int tags;
  int isfloating;
  int monitor;
} Rule;

typedef struct {
  unsigned int mod;
  KeySym keysym;
  void (*func)(void);
  const Arg arg;
} Key;

// clang-format off
/*---------------------------------------- Edit config options below this point ---------------------------------------*/

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const gap_t default_gap = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap = 32; /* snap pixel */
static const int showbar = 1;        /* 0 means no bar */
static const int topbar = 1;         /* 0 means bottom bar */
static const int startontag = 1;   /* 0 means no tag active on start */
static const int refreshrate = 60; /* Update rate for drag and resize events, in updates (frames) per second */
static const int user_bh = 2; /* 2 is the default spacing around the bar's font */
static const char *fonts[] = {"monospace:size=10"};
static const char dmenufont[] = "monospace:size=10";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
};
// clang-format on
/* window swallowing */
static const int swaldecay = 3;
static const int swalretroactive = 1;
static const char swalsymbol[] = "👅";

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

/* Lockfile */
static char lockfile[] = "/tmp/aero.lock";

// clang-format off
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating     monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,             -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,             -1 },
};
// clang-format on

/* layout(s) */
// clang-format off
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints = 1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const layout_t layouts[] = {
    /* symbol     arrange function */
    // {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    // {"[M]", monocle},
};
// clang-format on

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},
#define KEYEVENT(SRC_MOD, SRC_KEY, DST_MOD, DST_KEY)                           \
  {SRC_MOD,                                                                    \
   SRC_KEY,                                                                    \
   sendkeyevent,                                                               \
   {.v = &(const KeyBinding){DST_MOD, DST_KEY}}},

/* helper for spawning shell commands in the pre aero-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *termcmd[] = {"alacritty", NULL};
static const char *upbrightness[] = {"xbacklight", "-inc", "10", NULL};
static const char *downbrightness[] = {"xbacklight", "-dec", "10", NULL};

#include "exit.h"
// clang-format off
static const Key keys[] = {{ MODKEY|ShiftMask,             XK_e,      exitaero,       {0} }};

// const Key keys[] = {
// 	/* modifier                     key        function        argument */
// 	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = dmenucmd } },
// 	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
// 	{ MODKEY|ShiftMask,		        XK_s,	   spawn,	       SHCMD("transset-df -a --dec .1") },
// 	{ MODKEY|ShiftMask,		        XK_d,	   spawn,	       SHCMD("transset-df -a --inc .1") },
// 	{ MODKEY|ShiftMask,		        XK_f,	   spawn,	       SHCMD("transset-df -a .75") },
// 	{ MODKEY,                       XK_b,      togglebar,      {0} },
// 	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
// 	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
// 	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
// 	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
// 	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
// 	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
//     { MODKEY,                       XK_s,      togglecanfocusfloating,   {0} },
// 	{ ALTKEY,                       XK_Return, zoom,           {0} },
// 	{ MODKEY,                       XK_Tab,    view,           {0} },
// 	{ MODKEY,                       XK_g,      goback,         {0} },
// 	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
// 	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
// 	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
// 	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
// 	{ MODKEY,                       XK_space,  setlayout,      {0} },
// 	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
// 	{ MODKEY,                       XK_g,      gesture,        {0} },
// 	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
// 	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
// 	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
// 	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
// 	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
// 	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
//     { MODKEY,                       XK_u,      swalstopsel,    {0} },
// 	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
// 	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
// 	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
// 	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
// 	// Navigation(two-handed)
// 	KEYEVENT(Mod1Mask, XK_h, 0, XK_Left)
// 	KEYEVENT(Mod1Mask, XK_l, 0, XK_Right)
// 	KEYEVENT(Mod1Mask, XK_k, 0, XK_Up)
// 	KEYEVENT(Mod1Mask, XK_j, 0, XK_Down)
// 	KEYEVENT(Mod1Mask, XK_p, 0, XK_Up)
// 	KEYEVENT(Mod1Mask, XK_n, 0, XK_Down)
// 	KEYEVENT(Mod1Mask, XK_i, ControlMask, XK_Left)
// 	KEYEVENT(Mod1Mask, XK_o, ControlMask, XK_Right)
// 	KEYEVENT(Mod1Mask, XK_equal, ControlMask, XK_Home)
// 	KEYEVENT(Mod1Mask, XK_minus, ControlMask, XK_End)
// 	// Navigation(one-handed)
// 	KEYEVENT(Mod1Mask, XK_s, 0, XK_Up)
// 	KEYEVENT(Mod1Mask, XK_x, 0, XK_Down)
// 	KEYEVENT(Mod1Mask, XK_z, 0, XK_Left)
// 	KEYEVENT(Mod1Mask, XK_c, 0, XK_Right)
// 	KEYEVENT(Mod1Mask, XK_d, 0, XK_Return)
// 	KEYEVENT(Mod1Mask, XK_a, 0, XK_Home)
// 	KEYEVENT(Mod1Mask, XK_e, 0, XK_End)
// 	// Selection(two-handed)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_h, ShiftMask, XK_Left)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_l, ShiftMask, XK_Right)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_k, ShiftMask, XK_Up)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_j, ShiftMask, XK_Down)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_p, ShiftMask, XK_Up)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_n, ShiftMask, XK_Down)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_i, ControlMask|ShiftMask, XK_Left)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_o, ControlMask|ShiftMask, XK_Right)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_equal, ControlMask|ShiftMask, XK_Home)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_minus, ControlMask|ShiftMask, XK_End)
// 	// Selection(one-handed)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_s, ShiftMask, XK_Up)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_x, ShiftMask, XK_Down)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_z, ShiftMask, XK_Left)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_c, ShiftMask, XK_Right)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_a, ShiftMask, XK_Home)
// 	KEYEVENT(Mod1Mask|ShiftMask, XK_e, ShiftMask, XK_End)
// 	TAGKEYS(                        XK_1,                      0)
// 	TAGKEYS(                        XK_2,                      1)
// 	TAGKEYS(                        XK_3,                      2)
// 	TAGKEYS(                        XK_4,                      3)
// 	TAGKEYS(                        XK_5,                      4)
// 	TAGKEYS(                        XK_6,                      5)
// 	TAGKEYS(                        XK_7,                      6)
// 	TAGKEYS(                        XK_8,                      7)
// 	TAGKEYS(                        XK_9,                      8)
// 	{ MODKEY|ShiftMask,             XK_e,      exitaero,       {0} },
// 	{ 0,            XF86XK_MonBrightnessUp,    spawn,          {.v = upbrightness } },
// 	{ 0,            XF86XK_MonBrightnessDown,  spawn,          {.v = downbrightness } },
// };

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
// static const Button buttons[] = {
// 	/* click                event mask      button          function        argument */
// 	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
// 	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
// 	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
// 	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
// 	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
// 	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
// 	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
//     { ClkClientWin,         MODKEY|ShiftMask, Button1,      swalmouse,      {0} },
//   	{ ClkClientWin,         MODKEY|ShiftMask,Button3,       gesture,        {0} },
// 	{ ClkTagBar,            0,              Button1,        view,           {0} },
// 	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
// 	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
// 	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
// };

/* gestures
 * u means up
 * d means down
 * l means left
 * r means right
 * ud means up and down
 */
// static Gesture gestures[] = {
// 	{ "u",  spawn, {.v = termcmd } },
// 	{ "d",  spawn, {.v = dmenucmd } },
// };

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
// static Signal signals[] = {
// 	/* signum       function        argument  */
// 	{ 1,            setlayout,      {.v = 0} },
// };
#endif // CONFIG_H
