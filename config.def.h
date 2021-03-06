/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Code:size=10" };
static const char dmenufont[]       = "Fira Code:size=10";
static const char col_gray1[]       = "#5e81ac";
static const char col_gray2[]       = "#81a1c1";
static const char col_gray3[]       = "#4c566a";
static const char col_gray4[]       = "#434c5e";
static const char col_gray5[]       = "#E5E9F0";
static const char col_cyan[]        = "#3b4252";
static const char col_golden[]		= "#EBCB8B";
static const char col_aurora1[]		= "#BF616A";
static const char col_aurora2[]		= "#D08770";
static const char col_aurora3[]		= "#A3BE8C";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_golden, col_cyan, col_cyan},
	[SchemeSel]  = { col_golden, col_cyan,  col_golden},
	[SchemeStatus]  = { col_golden, col_cyan,  "#222222"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_golden, col_gray1,  "#444444"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_golden, col_cyan,  "#4c566a"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_golden, col_cyan,  "#4c566a"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_golden, col_cyan,  "#4c566a"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
	[SchemeTitle]  = { col_aurora3, col_cyan,  col_cyan  }
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	//{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	//{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Brave-browser",  NULL,       NULL,	1,			0,			-1 },
	{ "Slack",			NULL,       NULL,	1 << 1,			0,           0 },
	{ "Mailspring",		NULL,       NULL,	1 << 6,		0,			-1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray4, "-nf", col_gray5, "-sb", col_gray2, "-sf", col_gray5, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *brave[]  = { "brave", NULL };
static const char *flameshot[]  = { "flameshot", "gui", NULL };
static const char *power[]  = { "/home/rojan/dotfiles/dmenu_scripts/power.sh", NULL };
static const char *thunar[]  = { "thunar", NULL };
static const char *monitors[]  = { "/home/rojan/dotfiles/dmenu_scripts/monitors.sh", NULL };

#include "shiftview.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0,XF86XK_AudioMute,			spawn,		SHCMD("pulsemixer --toggle-mute; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pulsemixer --change-volume -5; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pulsemixer --change-volume +5; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,                       XK_w,		spawn,       { .v = brave } },
	{ 0,							XK_Print,		spawn,       { .v = flameshot } },
	{ MODKEY,						XK_n,		shiftview,       { .i = +1  } },
	{ MODKEY|ShiftMask,				XK_n,		shiftview,       { .i = -1  } },
	{ MODKEY|ShiftMask,				XK_x,		spawn,			{ .v = power  } },
	{ MODKEY,						XK_o,		spawn,			{.v = thunar }},
	{ 0,							XF86XK_Display,	spawn,		{ .v = monitors} },

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

