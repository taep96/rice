/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 4;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const char autostartblocksh[]     = "autostart_blocking.sh";
static const char autostartsh[]          = "autostart.sh";
static const char dwmdir[]               = "dwm";
static const char localshare[]           = ".local/share";
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';
static const int horizpadbar             = 6;   /* horizontal padding for statusbar */
static const int vertpadbar              = 7;   /* vertical padding for statusbar */

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_BOTTOM_BAR_SLIM;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static const char *fonts[]               = { "monospace:size=9:weight=bold:antialias=true:hinting=true",
                                             "emoji:size=10:antialias=true:autohint=true" };

/* Theme */
#include "themes/gruvbox.h"



static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};



/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static char *tagicons[][NUMTAGS] = {
	[DEFAULT_TAGS]        = { "一", "二", "三", "四", "五", "六", "七", "八", "九" },
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};


/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "discord", .tags = 1 << 0)
	RULE(.class = "firefox", .tags = 1 << 1)
};



/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor   bar    alignment         widthfunc                drawfunc                clickfunc                name */
	{ -1,        0,     BAR_ALIGN_LEFT,   width_tags,              draw_tags,              click_tags,              "tags" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,          draw_ltsymbol,          click_ltsymbol,          "layout" },
	{ statusmon, 0,     BAR_ALIGN_RIGHT,  width_pwrl_status,       draw_pwrl_status,       click_pwrl_status,       "powerline_status" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_wintitle,          draw_wintitle,          click_wintitle,          "wintitle" },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */



static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};


/* key definitions */
#define MODKEY Mod4Mask
#define Alt Mod1Mask
#define Ctrl ControlMask
#define Shift ShiftMask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                 KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|Ctrl,            KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|Shift,           KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|Ctrl|Shift,      KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|Alt|Shift,       KEY,      swaptags,       {.ui = 1 << TAG} },



/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char j4dmenucmd[]       = "j4-dmenu-desktop";
static const char dmenucmd[]         = "dmenu_run";
static const char termcmd[]          = "alacritty";

static const char lockcmd[]          = "betterlockscreen --lock blur";
static const char screenshotcmd[]    = "flameshot gui";
static const char toggleplayercmd[]  = "playerctl play-pause";

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key               function                argument */
	{ 0,                            XF86XK_AudioPlay, spawn,                  SHCMD(toggleplayercmd) },
	{ Ctrl,                         XK_Insert,        spawn,                  SHCMD(screenshotcmd) },
	{ MODKEY,                       XK_Escape,        spawn,                  SHCMD(lockcmd) },
	{ MODKEY,                       XK_Return,        spawn,                  SHCMD(termcmd) },
	{ MODKEY|Alt,                   XK_Return,        spawn,                  SHCMD(dmenucmd) },
	{ MODKEY|Shift,                 XK_Return,        spawn,                  SHCMD(j4dmenucmd) },
	{ MODKEY,                       XK_b,             togglebar,              {0} },
	{ MODKEY,                       XK_j,             focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,             focusstack,             {.i = -1 } },
	{ MODKEY|Shift,                 XK_j,             rotatestack,            {.i = +1 } },
	{ MODKEY|Shift,                 XK_k,             rotatestack,            {.i = -1 } },
	{ MODKEY,                       XK_u,             incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_p,             incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_i,             setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_o,             setmfact,               {.f = +0.05} },
	{ MODKEY|Alt|Shift,             XK_j,             movestack,              {.i = +1 } },
	{ MODKEY|Alt|Shift,             XK_k,             movestack,              {.i = -1 } },
	{ MODKEY,                       XK_slash,         zoom,                   {0} },
	{ MODKEY,                       XK_Tab,           view,                   {0} },
	{ MODKEY,                       XK_h,             shiftview,              { .i = -1 } },
	{ MODKEY,                       XK_l,             shiftview,              { .i = +1 } },
	{ MODKEY|Shift,                 XK_h,             shiftboth,              { .i = -1 } }, // note keybinding conflict with focusadjacenttag tagandviewtoleft
	{ MODKEY|Shift,                 XK_l,             shiftboth,              { .i = +1 } }, // note keybinding conflict with focusadjacenttag tagandviewtoright
	{ MODKEY|Ctrl,                  XK_h,             shiftswaptags,          { .i = -1 } },
	{ MODKEY|Ctrl,                  XK_l,             shiftswaptags,          { .i = +1 } },
	{ MODKEY|Shift,                 XK_c,             killclient,             {0} },
	{ MODKEY|Shift,                 XK_q,             quit,                   {0} },
	{ MODKEY,                       XK_t,             setlayout,              {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,             setlayout,              {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,             setlayout,              {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,         setlayout,              {0} },
	{ MODKEY|Shift,                 XK_space,         togglefloating,         {0} },
	{ MODKEY,                       XK_0,             view,                   {.ui = ~0 } },
	{ MODKEY|Shift,                 XK_0,             tag,                    {.ui = ~0 } },
	{ MODKEY,                       XK_comma,         focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period,        focusmon,               {.i = +1 } },
	{ MODKEY|Shift,                 XK_comma,         tagmon,                 {.i = -1 } },
	{ MODKEY|Shift,                 XK_period,        tagmon,                 {.i = +1 } },
	TAGKEYS(                        XK_1,                                     0)
	TAGKEYS(                        XK_2,                                     1)
	TAGKEYS(                        XK_3,                                     2)
	TAGKEYS(                        XK_4,                                     3)
	TAGKEYS(                        XK_5,                                     4)
	TAGKEYS(                        XK_6,                                     5)
	TAGKEYS(                        XK_7,                                     6)
	TAGKEYS(                        XK_8,                                     7)
	TAGKEYS(                        XK_9,                                     8)
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};


