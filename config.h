/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int focusonwheel       = 0;        /* for focus on click */
static const char *fonts[]          = { "TamzenForPowerline:size=12", "-wuncon-siji-medium-r-normal--10-100-75-75-c-80-iso10646-1" };

/* useless gaps */
static const int gappx = 10;

/* colors and fonts */
static const char dmenufont[]       = "TamzenForPowerline:size=12";
static const char col_gray1[]       = "#86AECA";
static const char col_gray2[]       = "#C9D7D5";
static const char col_gray3[]       = "#0F2436";
static const char col_gray4[]       = "#86AECA";
static const char col_cyan[]        = "#0F2436";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Brave",     NULL,       NULL,       1,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_q,      killclient,     {0} },                       // kill current window
	{ MODKEY,                       XK_b,      togglebar,      {0} },                       // toggle bar 
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },                // move foreward in stack
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },                // move forward in stack
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },                // increase number of master nodes
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },                // decrease number of master nodes
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },              // increase master size
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },              // decrease master size
	{ MODKEY,                       XK_space,  zoom,           {0} },                       // push active window to master
	{ MODKEY,                       XK_Tab,    view,           {0} },                       // switch to last tag
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },        // set to tiled layout
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },        // set all to floating
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },        // set to monocle
	{ MODKEY|ShiftMask,             XK_Return, setlayout,      {0} },                       // return to previous layout
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },                       // toggle individual window floating
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },               // view all windows on screen
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },               // make active window show on all tags
	{ MODKEY|ShiftMask,                       XK_comma,  focusmon,       {.i = -1 } },                // focus next screen
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },                // focus last screen
	{ MODKEY|ShiftMask,             XK_l,  tagmon,         {.i = -1 } },                // move window to next screen
	{ MODKEY|ShiftMask,             XK_h, tagmon,         {.i = +1 } },                // move window to next screen
	{ MODKEY,             		XK_r,      spawn,          {.v = dmenucmd } }, // open dmenu
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } }, // open st 
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_Escape,      quit,           {0} },
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

