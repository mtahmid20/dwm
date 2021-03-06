/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const char *fonts[]          = { "Iosevka Nerd Font:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_gray1[]       = "#2e3440";
static const char col_gray2[]       = "#434c53";
static const char col_gray3[]       = "#d8dee9";
static const char col_gray4[]       = "#eceff4";
static const char col_cyan[]        = "#bf616a";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance    title       tags mask     isfloating   monitor */
	{ "firefox",    NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Thunar",     NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Pcmanfm",    NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Engrampa",   NULL,       NULL,       1 << 2,       0,           -1 },
	{ "code-oss",   NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Gimp",       NULL,       NULL,       1 << 5,       0,           -1 },
	{ "Audacity",   NULL,       NULL,       1 << 5,       0,           -1 },
	{ "obs",        NULL,       NULL,       1 << 7,       0,           -1 },
	{ "kdenlive",   NULL,       NULL,       1 << 6,       0,           -1 },
	{ "openshot",   NULL,       NULL,       1 << 6,       0,           -1 },
	{ "virtualbox", NULL,       NULL,       1 << 8,       0,           -1 },
	{ "qBittorrent",NULL,       NULL,       1 << 9,       0,           -1 },
	{ "Pavucontrol",NULL,       NULL,       0,            1,           -1 },
	{ "qt5ct",      NULL,       NULL,       0,            1,           -1 },
   { "Lxappearance",NULL,       NULL,       0,            1,           -1 },
	{ "Gparted",    NULL,       NULL,       0,            1,           -1 },
	{ "Gcalculator",NULL,       NULL,       0,            1,           -1 },
	{ "Nitrogen",   NULL,       NULL,       0,            1,           -1 },
	{ "mpv",        NULL,       NULL,       1 << 4,       0,           -1 },
	{ "vlc",        NULL,       NULL,       1 << 4,       0,           -1 },
	{ "Io.github.celluloid_player.Celluloid",        NULL,       NULL,       1 << 4,       0,           -1 },
	{ "File Transfer*", NULL,   NULL,       0,            1,           -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[\\]",     dwindle },
 	{ "[@]",      spiral },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MOD1    Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("~/.config/rofi/powermenu.sh") },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_x,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
    { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_minus,  view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_minus,  tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MOD1,                         XK_minus,  setgaps,        {.i = -1 } },
	{ MOD1,                         XK_equal,  setgaps,        {.i = +1 } },
	{ MOD1|ShiftMask,               XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("xkill") },


    { MODKEY,			            XK_w,		spawn,		   SHCMD("firefox") },
    { MOD1,			                XK_w,		spawn,		   SHCMD("chromium") },
    { MODKEY|ShiftMask,	            XK_w,		spawn,		   SHCMD("alacritty -e nmtui connect") },
    { MODKEY|ShiftMask,	            XK_n,		spawn,		   SHCMD("alacritty -e ncmpcpp") },
    { MODKEY|ShiftMask,	            XK_m,		spawn,		   SHCMD("pavucontrol") },
    { MOD1,		                    XK_space,	spawn,		   SHCMD("rofi -show drun -theme Monokai -show-icons") },
    { MODKEY,			            XK_e,		spawn,		   SHCMD("pcmanfm") },
    { ControlMask,			        XK_Print,	spawn,		   SHCMD("flameshot gui") },
    { MOD1,			                XK_F1,		spawn,		   SHCMD("xbacklight -dec 10") },
    { MOD1,			                XK_F2,		spawn,		   SHCMD("xbacklight -inc 10") },
    { 0,			                XK_Pause,	spawn,		   SHCMD("mpc toggle") },
    { ControlMask,			    XK_bracketright,	spawn,	   SHCMD("amixer -q set Master 5%+") },
    { ControlMask,			    XK_bracketleft,		spawn,	   SHCMD("amixer -q set Master 5%-") },


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

