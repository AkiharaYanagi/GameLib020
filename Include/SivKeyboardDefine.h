#pragma once


//エイリアス
using KEY_NAME = uint8;

//個数
constexpr uint8 SIV_KEYBOARD_NUM = 0xff;	// 0x00 -> 0xFE

//該当無し
constexpr uint8 SIK_NODATA = 0xff;

//各キーの定義
constexpr uint8	 SIK_BACK		= 0x08;		/* backspace */
constexpr uint8	 SIK_TAB		= 0x09;	
constexpr uint8	 SIK_CLEAR		= 0x0C;		//Clear(NumLock を外した状態のテンキー5) キー	
constexpr uint8	 SIK_ENTER		= 0x0D;		/* Enter on main keyboard */
constexpr uint8	 SIK_SHIFT		= 0x10;	
constexpr uint8	 SIK_CTRL		= 0x11;	
constexpr uint8	 SIK_ALT		= 0x12;	
constexpr uint8	 SIK_PAUSE		= 0x13;		/* Pause */
constexpr uint8	 SIK_ESCAPE		= 0x1B;	
constexpr uint8	 SIK_SPACE		= 0x20;	
constexpr uint8	 SIK_PAGEUP		= 0x21;		/* PgUp on arrow keypad */
constexpr uint8	 SIK_PAGEDN		= 0x22;		/* PgDn on arrow keypad */

//END, HOMEの順番に注意
constexpr uint8	 SIK_END		= 0x23;		/* End on arrow keypad */
constexpr uint8	 SIK_HOME		= 0x24;		/* Home on arrow keypad */

constexpr uint8	 SIK_LEFT		= 0x25;	    /* LeftArrow on arrow keypad */
constexpr uint8	 SIK_UP			= 0x26;	    /* UpArrow on arrow keypad */
constexpr uint8	 SIK_RIGHT		= 0x27;	    /* RightArrow on arrow keypad */
constexpr uint8	 SIK_DOWN		= 0x28;	    /* DownArrow on arrow keypad */
constexpr uint8	 SIK_PRNTSCRN	= 0x2C;	
constexpr uint8	 SIK_INSERT		= 0x2D;	    /* Insert on arrow keypad */
constexpr uint8	 SIK_DELETE		= 0x2E;	    /* Delete on arrow keypad */
constexpr uint8	 SIK_0			= 0x30;
constexpr uint8	 SIK_1			= 0x31;
constexpr uint8	 SIK_2			= 0x32;
constexpr uint8	 SIK_3			= 0x33;
constexpr uint8	 SIK_4			= 0x34;
constexpr uint8	 SIK_5			= 0x35;
constexpr uint8	 SIK_6			= 0x36;
constexpr uint8	 SIK_7			= 0x37;
constexpr uint8	 SIK_8			= 0x38;
constexpr uint8	 SIK_9			= 0x39;
constexpr uint8	 SIK_A			= 0x41;
constexpr uint8	 SIK_B			= 0x42;
constexpr uint8	 SIK_C			= 0x43;
constexpr uint8	 SIK_D			= 0x44;
constexpr uint8	 SIK_E			= 0x45;
constexpr uint8	 SIK_F			= 0x46;
constexpr uint8	 SIK_G			= 0x47;
constexpr uint8	 SIK_H			= 0x48;
constexpr uint8	 SIK_I			= 0x49;
constexpr uint8	 SIK_J			= 0x4A;
constexpr uint8	 SIK_K			= 0x4B;
constexpr uint8	 SIK_L			= 0x4C;
constexpr uint8	 SIK_M			= 0x4D;
constexpr uint8	 SIK_N			= 0x4E;
constexpr uint8	 SIK_O			= 0x4F;
constexpr uint8	 SIK_P			= 0x50;
constexpr uint8	 SIK_Q			= 0x51;
constexpr uint8	 SIK_R			= 0x52;
constexpr uint8	 SIK_S			= 0x53;
constexpr uint8	 SIK_T			= 0x54;
constexpr uint8	 SIK_U			= 0x55;
constexpr uint8	 SIK_V			= 0x56;
constexpr uint8	 SIK_W			= 0x57;
constexpr uint8	 SIK_X			= 0x58;
constexpr uint8	 SIK_Y			= 0x59;
constexpr uint8	 SIK_Z			= 0x5A;
constexpr uint8	 SIK_NUMPAD0	= 0x60;
constexpr uint8	 SIK_NUMPAD1	= 0x61;
constexpr uint8	 SIK_NUMPAD2	= 0x62;
constexpr uint8	 SIK_NUMPAD3	= 0x63;
constexpr uint8	 SIK_NUMPAD4	= 0x64;
constexpr uint8	 SIK_NUMPAD5	= 0x65;
constexpr uint8	 SIK_NUMPAD6	= 0x66;
constexpr uint8	 SIK_NUMPAD7	= 0x67;
constexpr uint8	 SIK_NUMPAD8	= 0x68;
constexpr uint8	 SIK_NUMPAD9	= 0x69;
constexpr uint8	 SIK_MULTIPLY	= 0x6A;		/*	*	 on numeric keypad */
constexpr uint8	 SIK_ADD		= 0x6B;		/*	+	 on numeric keypad */
constexpr uint8	 SIK_NUMPADENTER= 0x6C;		/* Enter on numeric keypad */
constexpr uint8	 SIK_SUBTRACT	= 0x6D;		/*	-	 on numeric keypad */
constexpr uint8	 SIK_DECIMAL	= 0x6E;		/*	.	 on numeric keypad */
constexpr uint8	 SIK_DIVIDE		= 0x6F;		/*	/	 on numeric keypad */
constexpr uint8	 SIK_F1			= 0x70;
constexpr uint8	 SIK_F2			= 0x71;
constexpr uint8	 SIK_F3			= 0x72;
constexpr uint8	 SIK_F4			= 0x73;
constexpr uint8	 SIK_F5			= 0x74;
constexpr uint8	 SIK_F6			= 0x75;
constexpr uint8	 SIK_F7			= 0x76;
constexpr uint8	 SIK_F8			= 0x77;
constexpr uint8	 SIK_F9			= 0x78;
constexpr uint8	 SIK_F10		= 0x79;
constexpr uint8	 SIK_F11		= 0x7A;
constexpr uint8	 SIK_F12		= 0x7B;
constexpr uint8	 SIK_F13		= 0x7C;
constexpr uint8	 SIK_F14		= 0x7D;
constexpr uint8	 SIK_F15		= 0x7E;
constexpr uint8	 SIK_F16		= 0x7F;
constexpr uint8	 SIK_F17		= 0x80;
constexpr uint8	 SIK_F18		= 0x81;
constexpr uint8	 SIK_F19		= 0x82;
constexpr uint8	 SIK_F20		= 0x83;
constexpr uint8	 SIK_F21		= 0x84;
constexpr uint8	 SIK_F22		= 0x85;
constexpr uint8	 SIK_F23		= 0x86;
constexpr uint8	 SIK_F24		= 0x87;
constexpr uint8	 SIK_NUMLOCK	= 0x90;
constexpr uint8	 SIK_LSHIFT		= 0xA0;
constexpr uint8	 SIK_RSHIFT		= 0xA1;
constexpr uint8	 SIK_LCONTROL	= 0xA2;
constexpr uint8	 SIK_RCONTROL	= 0xA3;
constexpr uint8	 SIK_LALT		= 0xA4;
constexpr uint8	 SIK_RALT		= 0xA5;
constexpr uint8	 SIK_PREVTRACK	= 0xB0;    /* Previous Track (SIK_CIRCUMFLEX on Japanese keyboard) */
constexpr uint8	 SIK_NEXTTRACK	= 0xB1;    /* Next Track */
constexpr uint8	 SIK_PLAYPAUSE	= 0xB2;    /* Play / Pause */
constexpr uint8	 SIK_MEDIASTOP	= 0xB3;    /* Media Stop */
constexpr uint8	 SIK_COLON_JIS	= 0xBA;    /*JIS*/
constexpr uint8	 SIK_SEMICOLON_US	= 	0xBA;	/*US*/
constexpr uint8	 SIK_SEMICOLON_JIS	= 	0xBB;	/*JIS*/
constexpr uint8	 SIK_EQUAL_US		= 	0xBB;	/*US*/
constexpr uint8	 SIK_COMMA		= 0xBC;
constexpr uint8	 SIK_MINUS		= 0xBD;	/* - on main keyboard */
constexpr uint8	 SIK_PERIOD		= 0xBE;	/* . on main keyboard */
constexpr uint8	 SIK_SLASH		= 0xBF;	/* / on main keyboard */
constexpr uint8	 SIK_GRAVE		= 0xC0;	/* accent grave */
constexpr uint8	 SIK_Command	= 0xD8;
constexpr uint8	 SIK_LCommand	= 0xD9;
constexpr uint8	 SIK_RCommand	= 0xDA;
constexpr uint8	 SIK_LBRACKET	= 0xDB;
constexpr uint8	 SIK_YEN		= 0xDC;   /*JIS*/
constexpr uint8	 SIK_BACKSLASH	= 0xDC;	/*US*/
constexpr uint8	 SIK_RBRACKET	= 0xDD;
constexpr uint8	 SIK_CARET		= 0xDE;   /*JIS*/
constexpr uint8	 SIK_APOSTROPHE	= 0xDE;	/*US*/
constexpr uint8	 SIK_AUNDERSCORE	= 0xE2;




#if 0

#define SIK_EQUALS          0x0D
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

#endif // 0
