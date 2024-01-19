#pragma once



#define SIK_BACK		0x08	/* backspace */
#define SIK_TAB			0x09
#define SIK_CLEAR		0x0C	//Clear(NumLock を外した状態のテンキー5) キー	
#define SIK_ENTER		0x0D	/* Enter on main keyboard */
#define SIK_SHIFT		0x10
#define SIK_CTRL		0x11
#define SIK_ALT			0x12
#define SIK_PAUSE		0x13	/* Pause */
#define SIK_ESCAPE		0x1B
#define SIK_SPACE		0x20
#define SIK_PAGEUP		0x21	/* PgUp on arrow keypad */
#define SIK_PAGEDN		0x22	/* PgDn on arrow keypad */
#define SIK_HOME		0x23	/* Home on arrow keypad */
#define SIK_END			0x24	/* End on arrow keypad */
#define SIK_LEFT		0x25    /* LeftArrow on arrow keypad */
#define SIK_UP			0x26    /* UpArrow on arrow keypad */
#define SIK_RIGHT		0x27    /* RightArrow on arrow keypad */
#define SIK_DOWN		0x28    /* DownArrow on arrow keypad */
#define SIK_PRNTSCRN	0x2C
#define SIK_INSERT		0x2D    /* Insert on arrow keypad */
#define SIK_DELETE		0x2E    /* Delete on arrow keypad */

#define SIK_0			0x30
#define SIK_1			0x31
#define SIK_2			0x32
#define SIK_3			0x33
#define SIK_4			0x34
#define SIK_5			0x35
#define SIK_6			0x36
#define SIK_7			0x37
#define SIK_8			0x38
#define SIK_9			0x39
#define SIK_A			0x41
#define SIK_B			0x42
#define SIK_C			0x43
#define SIK_D			0x44
#define SIK_E			0x45
#define SIK_F			0x46
#define SIK_G			0x47
#define SIK_H			0x48
#define SIK_I			0x49
#define SIK_J			0x4A
#define SIK_K			0x4B
#define SIK_L			0x4C
#define SIK_M			0x4D
#define SIK_N			0x4E
#define SIK_O			0x4F
#define SIK_P			0x50
#define SIK_Q			0x51
#define SIK_R			0x52
#define SIK_S			0x53
#define SIK_T			0x54
#define SIK_U			0x55
#define SIK_V			0x56
#define SIK_W			0x57
#define SIK_X			0x58
#define SIK_Y			0x59
#define SIK_Z			0x5A

#define SIK_NUMPAD0		0x60
#define SIK_NUMPAD1		0x61
#define SIK_NUMPAD2		0x62
#define SIK_NUMPAD3		0x63
#define SIK_NUMPAD4		0x64
#define SIK_NUMPAD5		0x65
#define SIK_NUMPAD6		0x66
#define SIK_NUMPAD7		0x67
#define SIK_NUMPAD8		0x68
#define SIK_NUMPAD9		0x69

#define SIK_MULTIPLY	0x6A		/*	*	 on numeric keypad */
#define SIK_ADD			0x6B		/*	+	 on numeric keypad */
#define SIK_NUMPADENTER	0x6C		/* Enter on numeric keypad */
#define SIK_SUBTRACT	0x6D		/*	-	 on numeric keypad */
#define SIK_DECIMAL		0x6E		/*	.	 on numeric keypad */
#define SIK_DIVIDE		0x6F		/*	/	 on numeric keypad */

#define SIK_F1			0x70
#define SIK_F2			0x71
#define SIK_F3			0x72
#define SIK_F4			0x73
#define SIK_F5			0x74
#define SIK_F6			0x75
#define SIK_F7			0x76
#define SIK_F8			0x77
#define SIK_F9			0x78
#define SIK_F10			0x79
#define SIK_F11			0x7A
#define SIK_F12			0x7B
#define SIK_F13			0x7C
#define SIK_F14			0x7D
#define SIK_F15			0x7E
#define SIK_F16			0x7F
#define SIK_F17			0x80
#define SIK_F18			0x81
#define SIK_F19			0x82
#define SIK_F20			0x83
#define SIK_F21			0x84
#define SIK_F22			0x85
#define SIK_F23			0x86
#define SIK_F24			0x87

#define SIK_NUMLOCK		0x90

#define SIK_LSHIFT		0xA0
#define SIK_RSHIFT		0xA1
#define SIK_LCONTROL	0xA2
#define SIK_RCONTROL	0xA3
#define SIK_LALT		0xA4
#define SIK_RALT		0xA5

#define SIK_PREVTRACK	0xB0    /* Previous Track (SIK_CIRCUMFLEX on Japanese keyboard) */
#define SIK_NEXTTRACK	0xB1    /* Next Track */
#define SIK_PLAYPAUSE	0xB2    /* Play / Pause */
#define SIK_MEDIASTOP	0xB3    /* Media Stop */

#define SIK_COLON_JIS		0xBA    /*JIS*/
#define SIK_SEMICOLON_US	0xBA	/*US*/
#define SIK_SEMICOLON_JIS	0xBB	/*JIS*/
#define SIK_EQUAL_US		0xBB	/*US*/





#define SIK_MINUS           0x0C    /* - on main keyboard */
#define SIK_EQUALS          0x0D
#define SIK_LBRACKET        0x1A
#define SIK_RBRACKET        0x1B
#define SIK_APOSTROPHE      0x28
#define SIK_GRAVE           0x29    /* accent grave */
#define SIK_BACKSLASH       0x2B
#define SIK_COMMA           0x33
#define SIK_PERIOD          0x34    /* . on main keyboard */
#define SIK_SLASH           0x35    /* / on main keyboard */
#define SIK_LMENU           0x38    /* left Alt */

#define SIK_CAPITAL         0x3A
#define SIK_SCROLL          0x46    /* Scroll Lock */

#define SIK_OEM_102         0x56    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
#define SIK_KANA            0x70    /* (Japanese keyboard)            */
#define SIK_ABNT_C1         0x73    /* /? on Brazilian keyboard */
#define SIK_CONVERT         0x79    /* (Japanese keyboard)            */
#define SIK_NOCONVERT       0x7B    /* (Japanese keyboard)            */
#define SIK_YEN             0x7D    /* (Japanese keyboard)            */
#define SIK_ABNT_C2         0x7E    /* Numpad . on Brazilian keyboard */
#define SIK_NUMPADEQUALS    0x8D    /* = on numeric keypad (NEC PC98) */
#define SIK_AT              0x91    /*                     (NEC PC98) */
#define SIK_UNDERLINE       0x93    /*                     (NEC PC98) */
#define SIK_KANJI           0x94    /* (Japanese keyboard)            */
#define SIK_STOP            0x95    /*                     (NEC PC98) */
#define SIK_AX              0x96    /*                     (Japan AX) */
#define SIK_UNLABELED       0x97    /*                        (J3100) */

#define SIK_MUTE            0xA0    /* Mute */
#define SIK_CALCULATOR      0xA1    /* Calculator */
#define SIK_VOLUMEDOWN      0xAE    /* Volume - */
#define SIK_VOLUMEUP        0xB0    /* Volume + */
#define SIK_WEBHOME         0xB2    /* Web home */
#define SIK_NUMPADCOMMA     0xB3    /* , on numeric keypad (NEC PC98) */
#define SIK_SYSRQ           0xB7
#define SIK_RMENU           0xB8    /* right Alt */

#define SIK_LWIN            0xDB    /* Left Windows key */
#define SIK_RWIN            0xDC    /* Right Windows key */
#define SIK_APPS            0xDD    /* AppMenu key */
#define SIK_POWER           0xDE    /* System Power */
#define SIK_SLEEP           0xDF    /* System Sleep */
#define SIK_WAKE            0xE3    /* System Wake */
#define SIK_WEBSEARCH       0xE5    /* Web Search */
#define SIK_WEBFAVORITES    0xE6    /* Web Favorites */
#define SIK_WEBREFRESH      0xE7    /* Web Refresh */
#define SIK_WEBSTOP         0xE8    /* Web Stop */
#define SIK_WEBFORWARD      0xE9    /* Web Forward */
#define SIK_WEBBACK         0xEA    /* Web Back */
#define SIK_MYCOMPUTER      0xEB    /* My Computer */
#define SIK_MAIL            0xEC    /* Mail */
#define SIK_MEDIASELECT     0xED    /* Media Select */

