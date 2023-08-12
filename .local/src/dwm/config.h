/* appearance */
//# include 'colors/gruvbox.h'
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 5, .realgap = 5, .gappx = 5};
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=12:antialias=true:autohint:true","NotoColorEmoji:size=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=12";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3]      = {
	/*                  fg     	     bg         	border   */
         [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const char *const autostart[] = {
	"polkit", NULL,
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	 instance      title    tags mask     isfloating    monitor */
        { "Telegram",      NULL,     NULL,       3,       0,           -1 },
        { "Spotify",       NULL,     NULL,       5,       0,           -1 },
        { "Firefox",       NULL,     NULL,       2,       0,           -1 },
        { "Chrome",        NULL,     NULL,       3,            0,           -1 },
        { "St",            NULL,     NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     	= 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     	= 1;    /* number of clients in master area */
static const int resizehints 	= 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
//#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont};
static const char *termcmd[]  = { "st", NULL };
static const char *alttermcmd[]  = { "st -e ranger", NULL };
static const char *webcmd[]  = { "google-chrome-stable", NULL };
static const char *privwebcmd[]  = { "google-chrome-stable", "--incognito", NULL };
static const char *altwebcmd[]  = { "firefox", NULL };
static const char *privaltwebcmd[]  = { "firefox", "--private-window", NULL };

static const Key keys[] = {
   /* modifier                     key        function        argument */
																						//
	// WM CONTROLS
        { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
        { MODKEY,XK_Return, spawn,          {.v = termcmd } },
        { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = alttermcmd } },
        { MODKEY,                       XK_c,      spawn,          {.v = webcmd } },
        { MODKEY|ShiftMask,             XK_c,      spawn,          {.v = privwebcmd } },
        { MODKEY,                       XK_f,      spawn,          {.v = altwebcmd } },
        { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = privaltwebcmd } },
        { MODKEY,                       XK_g,      togglebar,      {0} },					// toggle statusbar visibility
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },			// change focus down
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },			// change focus up
	{ MODKEY,                       XK_d,      incnmaster,     {.i = +1 } },			// increment master area +1
	{ MODKEY,                       XK_s,      incnmaster,     {.i = -1 } },			// decrement master area -1
	{ MODKEY,                       XK_q,      killclient,     {0} },					// kill currently selected window
	{ MODKEY,                       XK_w,      setlayout,      {.v = &layouts[0]} },	// switch to layout 0 (tiling)
	{ MODKEY|ShiftMask,             XK_e,      setlayout,      {.v = &layouts[1]} },	// switch to layout 1 (floating)
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[2]} },	// switch to layout 2 (monocle)
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },			// view all windows on current tag	
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },			// make current window sticky to all tags	
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },			// shift focus to monitor left	
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },			// shift focus to monitor right	
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },			// move window to monitor left	
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },			// move window to monitor right	
	
	{ MODKEY,			XK_minus,  setgaps,	   {.i = -1 } },			// decrease gaps
	{ MODKEY,		        XK_k,  	   setgaps,	   {.i = +1 } },			// increase gaps
	{ MODKEY|ShiftMask,		XK_equal,  setgaps,	   {.i = 0 } },	// reset gaps
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
        TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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
