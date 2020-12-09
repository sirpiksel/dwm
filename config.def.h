/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const unsigned int gappx     = 15;        /* gaps between windows */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 15;       /* vertical padding of bar */
static const int sidepad            = 15;       /* horizontal padding of bar */
static const char *fonts[]          = { "MesloLGS NF:style=Regular:pixelsize=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "MesloLGS NF:style=Regular:pixelsize=10:antialias=true:autohint=true";
static const char col_norm[]       = "#b3b3b3";
static const char col_sel[]       = "#ffffff";
static const char col_bg[]       = "#101214";
static const char *colors[][3]      = {
        /*               fg         bg      border   */
        [SchemeNorm] = { col_norm, col_bg, col_bg },
        [SchemeSel]  = { col_sel, col_bg, col_bg  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{  NULL,      NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "tile",     tile },    /* first entry is default */
	{ "float",    NULL },    /* no layout function means floating behavior */
	{ "monocle",  monocle },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "exec /home/philip/Documents/dev/scripts/spotlight.sh",  NULL };
static const char *termcmd[]     = { "st", NULL };
static const char *browsercmd[]  = { "chromium", NULL };
static const char *toriumcmd[]   = { "/home/philip/Documents/dev/scripts/torium.sh", NULL };
static const char *trackpadcmd[] = { "/home/philip/Documents/dev/scripts/toggletrackpad.sh", NULL };
static const char *lfcmd[]       = { "st", "-e", "\"lf\"", NULL };
static const char *voldowncmd[]  = { "/home/philip/Documents/dev/scripts/volumecontrol.sh -r", NULL };
static const char *volupcmd[]    = { "/home/philip/Documents/dev/scripts/volumecontrol.sh -i", NULL };
static const char *nvimcmd[]     = { "st -e \"nvim\"", NULL };
static const char *m3morycmd[]   = { "/home/philip/Documents/dev/scripts/m3mory.sh", NULL };
static const char *spotifycmd[]  = { "spotify", NULL };
static const char *lockcmd[]     = { "sudo sh -c 'echo 0 > /sys/class/leds/spi::kbd_backlight/brightness' && xsecurelock && sudo sh -c 'echo 255 > /sys/class/leds/spi::kbd_backlight/brightness'", NULL };
static const char *mbpfancmd[]   = { "sudo systemctl is-active mbpfan.service && sudo systemctl stop mbpfan.service || sudo systemctl start mbpfan.service", NULL };
static const char *randrcmd[]    = { "autorandr --force -c", NULL };
static const char *passcmd[]     = { "passmenu -c -l 5", NULL };

static Key keys[] = {
	/* modifier                     key           function        argument */
	{ MODKEY,                       XK_space,     spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,    zoom,           {0} },
	{ MODKEY,                       XK_semicolon, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_d,         spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_d,         spawn,          {.v = toriumcmd } },
	{ MODKEY,                       XK_z,         spawn,          {.v = trackpadcmd } },
	{ MODKEY,                       XK_f,         spawn,          {.v = lfcmd } },
	{ MODKEY,                       XK_c,         spawn,          {.v = voldowncmd } },
	{ MODKEY,                       XK_v,         spawn,          {.v = volupcmd } },
	{ MODKEY,                       XK_g,         spawn,          {.v = nvimcmd } },
	{ MODKEY|ShiftMask,             XK_g,         spawn,          {.v = m3morycmd } },
	{ MODKEY,                       XK_s,         spawn,          {.v = spotifycmd } },
	{ MODKEY,                       XK_o,         spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_x,         spawn,          {.v = mbpfancmd } },
	{ MODKEY,                       XK_b,         spawn,          {.v = randrcmd } },
	{ MODKEY,                       XK_a,         spawn,          {.v = passcmd } },
	{ MODKEY,                       XK_r,         togglebar,      {0} },
	{ MODKEY,                       XK_j,         focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,         focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,         setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,         setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_q,         killclient,     {0} },
	{ MODKEY,                       XK_y,         setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_u,         setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_i,         setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_p,         togglefloating, {0} },
	{ MODKEY,                       XK_0,         view,           {.ui = ~0 } },
	{ MODKEY,                       XK_m,         focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_comma,     focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_m,         tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,     tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
