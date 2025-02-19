/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 9;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "mononoki Nerd Font:size=16:autohint=true:antialias=true", "JoyPixels:pixelsize=11" };
static const char dmenufont[]       = "mononoki Nerd Font:size=16:autohint=true:antialias=true";
static const char col_gray1[]       = "#262731";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#dedede";
static const char col_gray4[]       = "#ffffff";
static const char col_highlight[]   = "#6f00be";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_highlight, col_highlight },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class                    instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
    { "St",                     NULL,     NULL,           0,         0,          1,           0,        -1 }, /* suckless simple terminal */
    { "Qemu-system-x86_64",     NULL,     NULL,           0,         1,          0,           0,        -1 }, /* qemu */
    { "Virt-viewer",            NULL,     NULL,           0,         1,          0,           0,        -1 }, /* virt-viwer */
    { NULL,                     NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0";      /* component of dmenucmd, manipulated in spawn() */
static char dmenulines[] = "20";    /* number of lines dmenu displays */
static char dmenuborder[] = "5";    /* dmenu border weight */
static const char *dmenucmd[] = { "dmenu_run", "-c", "-l", dmenulines, "-bw", dmenuborder, "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_highlight, "-sf", col_gray4, NULL };

#include <X11/XF86keysym.h>

static const Key keys[] = {
    /* modifier                     key             function        argument */
    { MODKEY,                       XK_p,           spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return,      spawn,          SHCMD("$TERMINAL") },
    { MODKEY|ShiftMask,             XK_h,           spawn,          SHCMD("$TERMINAL -e htop") },
    { MODKEY|ShiftMask,             XK_e,           spawn,          SHCMD("$TERMINAL -e nvim") },
    { MODKEY|ShiftMask,             XK_b,           spawn,          SHCMD("$BROWSER") },
    { MODKEY|ShiftMask,             XK_v,           spawn,          SHCMD("vmmenu") },
    { MODKEY|ShiftMask,             XK_d,           spawn,          SHCMD("discord") },
    { MODKEY|ShiftMask,             XK_m,           spawn,          SHCMD("$TERMINAL -e ncmpcpp") },
    { MODKEY|ShiftMask,             XK_l,           spawn,          SHCMD("passmenu") },
    { MODKEY,                       XK_j,           focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,           focusstack,     {.i = -1 } },
    { MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_o,           incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_o,           incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_Return,      zoom,           {0} },
    { MODKEY,                       XK_z,           setgaps,        {.i = +1 } },
    { MODKEY,                       XK_x,           setgaps,        {.i = -1 } },
    { MODKEY,                       XK_a,           togglegaps,     {0} },
    { MODKEY,                       XK_b,           togglebar,      {0} },
    { MODKEY,                       XK_w,           spawn,          SHCMD("wallpaper") },
    { MODKEY,                       XK_backslash,   spawn,          SHCMD("nowplaying") },
    { MODKEY,                       XK_BackSpace,   spawn,          SHCMD("sysact") },
    { MODKEY,                       XK_Print,       spawn,          SHCMD("screenshot") },
    { MODKEY,                       XK_Delete,      spawn,          SHCMD("slock") },
    { MODKEY,                       XK_F1,          spawn,          SHCMD("mansplainer") },
    { MODKEY,                       XK_F2,          spawn,          SHCMD("updater") },
    { MODKEY,                       XK_F9,          spawn,          SHCMD("mediaplayer") },
    { MODKEY,                       XK_F10,         spawn,          SHCMD("mounter") },
    { MODKEY,                       XK_F11,         spawn,          SHCMD("unmounter") },
    { MODKEY,                       XK_F12,         spawn,          SHCMD("displayselect") },
    { MODKEY,                       XK_q,           killclient,     {0} },
    { MODKEY,                       XK_space,       setlayout,      {0} },
    { MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,             XK_t,           setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_f,           togglefloating, {0} },
    { MODKEY,                       XK_period,      focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_period,      tagmon,         {.i = +1 } },
    { MODKEY,                       XK_0,           view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,           tag,            {.ui = ~0 } },
    { MODKEY,                       XK_Tab,         view,           {0} },
    { MODKEY|ShiftMask,             XK_q,           quit,           {0} },
    { 0, XF86XK_AudioRaiseVolume,                   spawn,          SHCMD("wpctl set-volume @DEFAULT_SINK@ 5%+") },
    { 0, XF86XK_AudioLowerVolume,                   spawn,          SHCMD("wpctl set-volume @DEFAULT_SINK@ 5%-") },
    { 0, XF86XK_AudioMute,                          spawn,          SHCMD("wpctl set-mute @DEFAULT_SINK@ toggle") },
    { 0, XF86XK_AudioPrev,                          spawn,          SHCMD("mpc prev") },
    { 0, XF86XK_AudioNext,                          spawn,          SHCMD("mpc next") },
    { 0, XF86XK_AudioPlay,                          spawn,          SHCMD("mpc toggle") },
    { 0, XF86XK_MonBrightnessUp,                    spawn,          SHCMD("xbacklight -inc 15") },
    { 0, XF86XK_MonBrightnessDown,                  spawn,          SHCMD("xbacklight -dec 15") },
    { 0, XF86XK_TouchpadToggle,                     spawn,          SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
    { 0, XF86XK_TouchpadOn,                         spawn,          SHCMD("synclient TouchpadOff=0") },
    { 0, XF86XK_TouchpadOff,                        spawn,          SHCMD("synclient TouchpadOff=1") },
    TAGKEYS(XK_1, 0)
    TAGKEYS(XK_2, 1)
    TAGKEYS(XK_3, 2)
    TAGKEYS(XK_4, 3)
    TAGKEYS(XK_5, 4)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};
