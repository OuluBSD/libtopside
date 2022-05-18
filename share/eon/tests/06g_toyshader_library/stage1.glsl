// Common 
// Dimensions, character codes, font definition

// Dimensions
const ivec2 kScreenChars		= ivec2(40,25);
const ivec2 kSmallCharPixels	= ivec2(5,9);
const ivec2 kCharPixels			= ivec2(12,20);
const ivec2 kScreenResolution	= ivec2(480,500);
const vec2  kScreenRatio		= vec2(4, 3);

const ivec2 kCharTextureDim		= ivec2(16,6);
const ivec2 kCharTexturePixels	= kCharPixels + 2;

// Character Codes
const int 
_SP = 32,

_EXCLAMATION = 33,
_QUOTE = 34,
_POUND = 35,
_DOLLAR = 36,
_PERCENT = 37,
_AMPERSAND = 38,
_APOSTROPHE = 39,
_LPAREN = 40,
_RPAREN = 41,
_ASTERISK = 42,
_PLUS = 43,
_COMMA = 44,
_MINUS = 45,
_PERIOD = 46,
_FORWARDSLASH = 47,
    
_0 = 48, _1 = 49, _2 = 50, _3 = 51, _4 = 52, _5 = 53, _6 = 54, _7 = 55, _8 = 56, _9 = 57,
    
_COLON = 58,
_SEMICOLON = 59,
_LESSTHAN = 60,
_EQUALS = 61,
_GREATERTHAN = 62,
_QUESTIONMARK = 63,
_AT = 64,
    
_A =  65, _B =  66, _C =  67, _D =  68, _E =  69, _F =  70, _G =  71,
_H =  72, _I =  73, _J =  74, _K =  75, _L =  76, _M =  77, _N =  78,
_O =  79, _P =  80, _Q =  81, _R =  82, _S =  83, _T =  84, _U =  85,
_V =  86, _W =  87, _X =  88, _Y =  89, _Z =  90,

_LEFTARROW = 91,
_HALF = 92,
_RIGHTARROW = 93,
_UPARROW = 94,
_HASH = 95,
_DASH = 96,
    
_a =  97, _b =  98, _c =  99, _d = 100, _e = 101, _f = 102, _g = 103,
_h = 104, _i = 105, _j = 106, _k = 107, _l = 108, _m = 109, _n = 110,
_o = 111, _p = 112, _q = 113, _r = 114, _s = 115, _t = 116, _u = 117, 
_v = 118, _w = 119, _x = 120, _y = 121, _z = 122,
    
_QUARTER = 123,
_DOUBLEBAR = 124,
_THREEQUARTERS = 125,
_DIVIDE = 126,
_BLOCK = 127;    

const int 
CTRL_NUL = 128,
CTRL_ALPHANUMERIC_RED = 129,
CTRL_ALPHANUMERIC_GREEN = 130,
CTRL_ALPHANUMERIC_YELLOW = 131,
CTRL_ALPHANUMERIC_BLUE = 132,
CTRL_ALPHANUMERIC_MAGENTA = 133,
CTRL_ALPHANUMERIC_CYAN = 134,
CTRL_ALPHANUMERIC_WHITE = 135,
CTRL_FLASH = 136,
CTRL_STEADY = 137,
CTRL_END_BOX = 138, 			// unsupported
CTRL_START_BOX = 139, 			// unsupported
CTRL_NORMAL_HEIGHT = 140,
CTRL_DOUBLE_HEIGHT = 141,
CTRL_S0 = 142, 					// ??
CTRL_S1 = 143, 					// ??
CTRL_DLE = 144, 				// ??
CTRL_GFX_RED = 145,
CTRL_GFX_GREEN = 146,
CTRL_GFX_YELLOW = 147,
CTRL_GFX_BLUE = 148,
CTRL_GFX_MAGENTA = 149,
CTRL_GFX_CYAN = 150,
CTRL_GFX_WHITE = 151,
CTRL_CONCEAL = 152,
CTRL_CONTIGUOUS_GFX = 153,
CTRL_SEPARATED_GFX = 154,
CTRL_ESC = 155, 				// unused
CTRL_BLACK_BACKGROUND = 156,
CTRL_NEW_BACKGROUND = 157,
CTRL_HOLD_GFX = 158,
CTRL_RELEASE_GFX = 159;


// Colors

const int 
	COLOR_BLACK 	= 0,
    COLOR_RED 		= 1,
    COLOR_GREEN 	= 2,
    COLOR_YELLOW 	= 3,
    COLOR_BLUE 		= 4,
    COLOR_MAGENTA 	= 5,
    COLOR_CYAN 		= 6,
    COLOR_WHITE 	= 7;

const vec3 kColors[] = vec3[] ( vec3(0), vec3(1,0,0), vec3(0,1,0), vec3(1,1,0), vec3(0,0,1), vec3(1,0,1), vec3(0,1,1), vec3(1,1,1) );

const int
    NORMAL_HEIGHT = 0,
    DOUBLE_HEIGHT_TOP = 1,
    DOUBLE_HEIGHT_BOTTOM = 2;

const int
    GFX_ALPHANUMERIC = 0,
    GFX_CONTINUOUS = 1,
    GFX_SEPARATED = 2;

// SAA5050 font (starting from char 32)

const uint charSet5x9[] = uint[]( 0x0u,0x0u,0x421084u,0x1u,0x14au,0x0u,0xc4238a4cu,0x7u,0xab4716aeu,0x3u,0x32222263u,0x6u,0x935114a2u,0x5u,0x84u,0x0u,0x8210888u,0x2u,0x88842082u,0x0u,0x2ae23aa4u,0x1u,0x84f9080u,0x0u,0x8000000u,0x11u,0x70000u,0x0u,0x0u,0x1u,0x2222200u,0x0u,0x1518c544u,0x1u,0x884210c4u,0x3u,0xc226422eu,0x7u,0xa306221fu,0x3u,0x11f4a988u,0x2u,0xa3083c3fu,0x3u,0xa317844cu,0x3u,0x8422221fu,0x0u,0xa317462eu,0x3u,0x910f462eu,0x1u,0x1000u,0x1u,0x8001000u,0x11u,0x8208888u,0x2u,0x1f07c00u,0x0u,0x88882082u,0x0u,0x42222eu,0x1u,0x83daf62eu,0x3u,0x63f8c544u,0x4u,0xe317c62fu,0x3u,0xa210862eu,0x3u,0xe318c62fu,0x3u,0xc217843fu,0x7u,0x4217843fu,0x0u,0xa390862eu,0x3u,0x631fc631u,0x4u,0x8842108eu,0x3u,0xa3084210u,0x3u,0x52519531u,0x4u,0xc2108421u,0x7u,0x631ad771u,0x4u,0x639ace31u,0x4u,0xa318c62eu,0x3u,0x4217c62fu,0x0u,0x9358c62eu,0x5u,0x5257c62fu,0x4u,0xa307062eu,0x3u,0x842109fu,0x1u,0xa318c631u,0x3u,0x8a54631u,0x1u,0xab5ac631u,0x2u,0x62a22a31u,0x4u,0x8422a31u,0x1u,0xc222221fu,0x7u,0x82f8880u,0x0u,0x20d08421u,0x1c22u,0x88fa080u,0x0u,0x84ab880u,0x0u,0x95f57d4au,0x2u,0xf8000u,0x0u,0xa3e83800u,0x7u,0xe318bc21u,0x3u,0x8210f800u,0x7u,0xa318fa10u,0x7u,0x83f8b800u,0x3u,0x8471088u,0x1u,0xa318f800u,0xe87u,0x6318bc21u,0x4u,0x88421804u,0x3u,0x8421004u,0x221u,0x94654842u,0x4u,0x88421086u,0x3u,0x6b5aac00u,0x5u,0x6318bc00u,0x4u,0xa318b800u,0x3u,0xe318bc00u,0x10bu,0xa318f800u,0x1087u,0x84236800u,0x0u,0xe0e0f800u,0x3u,0x8423884u,0x2u,0xa318c400u,0x7u,0x14a8c400u,0x1u,0xab58c400u,0x2u,0x54454400u,0x4u,0xa318c400u,0xe87u,0xc4447c00u,0x7u,0x31210842u,0x10e5u,0x94a5294au,0x52u,0x31320c83u,0x10e5u,0x80f8080u,0x0u,0xffffffffu,0x7u );
const uint charSet12x20[] = uint[]( 0x0u,0x0u,0x0u,0x0u,0x0u,0x0u,0x0u,0x0u,0xc0000000u,0xc00c00u,0xc00c00cu,0xc00c00c0u,0xc00u,0xc00c000u,0x0u,0x0u,0x30000000u,0x3303303u,0x33u,0x0u,0x0u,0x0u,0x0u,0x0u,0xc0000000u,0xe707e03u,0x30030c3u,0x300fc0fcu,0x300300u,0xffcffc03u,0x0u,0x0u,0xf0000000u,0xcedc7f83u,0xdc0ccccu,0xc07f03f8u,0xcccccc0eu,0x3f07f8edu,0x0u,0x0u,0x3c000000u,0xcc3c03c0u,0x380700e3u,0x700e01c0u,0xcf1c0380u,0xf00f00f0u,0x0u,0x0u,0x30000000u,0xc0fc0780u,0xfc0cc0cu,0xfc078078u,0xc78cfcccu,0xcf0ff879u,0x0u,0x0u,0xc0000000u,0xc00c00u,0xcu,0x0u,0x0u,0x0u,0x0u,0x0u,0x0u,0x1c03803u,0x300700eu,0x30030030u,0xe00700u,0x3003801cu,0x0u,0x0u,0x30000000u,0xe00700u,0x3003801cu,0x300300u,0x1c03803u,0x300700eu,0x0u,0x0u,0xc0000000u,0xcccc0c00u,0x3f07f8edu,0xf00c00c0u,0xcedc7f83u,0xc00c0ccu,0x0u,0x0u,0x0u,0xc00000u,0xc00c00cu,0xc0ffcffcu,0xc00c00u,0xcu,0x0u,0x0u,0x0u,0x0u,0x0u,0x0u,0xc00000u,0xe00c00cu,0x30070u,0x0u,0x0u,0x0u,0x0u,0x3f03f0u,0x0u,0x0u,0x0u,0x0u,0x0u,0x0u,0x0u,0x0u,0x0u,0xc00c000u,0x0u,0x0u,0x0u,0xc000000u,0x380700e0u,0x700e01c0u,0xc01c0380u,0x0u,0x0u,0x0u,0xc0000000u,0x83f01e00u,0xc0ce1c73u,0xcc0cc0cu,0x738e1ccu,0xc01e03fu,0x0u,0x0u,0xc0000000u,0xf00c00u,0xc00c00fu,0xc00c00c0u,0xc00c00u,0x3f03f00cu,0x0u,0x0u,0xf0000000u,0xce1c7f83u,0xe00c00c0u,0x703e07c0u,0xc01c0380u,0xffcffc00u,0x0u,0x0u,0xfc000000u,0xc00ffcfu,0x300700e0u,0x7c03c0u,0xcc0cc00eu,0x3f07f8e1u,0x0u,0x0u,0x0u,0x3c03003u,0x3383703eu,0xfc30c31cu,0x300ffcfu,0x30030030u,0x0u,0x0u,0xfc000000u,0xc00cffcfu,0x7fc3fc00u,0xc00e00u,0xcc0cc00cu,0x3f07f8e1u,0x0u,0x0u,0xc0000000u,0x80703e03u,0xc01c03u,0xc7fc3fcu,0xcc0cc0ceu,0x3f07f8e1u,0x0u,0x0u,0xfc000000u,0xc00ffcfu,0x380700e0u,0x700e01c0u,0x300300u,0x3003003u,0x0u,0x0u,0xf0000000u,0xce1c7f83u,0xe1cc0cc0u,0x1c7f87f8u,0xcc0cc0ceu,0x3f07f8e1u,0x0u,0x0u,0xf0000000u,0xce1c7f83u,0xc1cc0cc0u,0xff0ff8u,0x700e00cu,0xf01f038u,0x0u,0x0u,0x0u,0x0u,0xc00c000u,0x0u,0x0u,0xc00c000u,0x0u,0x0u,0x0u,0x0u,0xc00c000u,0x0u,0xc00000u,0xe00c00cu,0x30070u,0x0u,0x0u,0x1c03803u,0x380700eu,0x3801c01cu,0xe00700u,0x3003801cu,0x0u,0x0u,0x0u,0x0u,0xffcffc00u,0xfc000000u,0xffcfu,0x0u,0x0u,0x0u,0x30000000u,0xe00700u,0x7003801cu,0xe00e00u,0x1c03807u,0x300700eu,0x0u,0x0u,0xf0000000u,0xce1c7f83u,0x380700e0u,0xc00c01c0u,0xc00u,0xc00c000u,0x0u,0x0u,0xf0000000u,0xce1c7f83u,0xfccfccc0u,0xccccccccu,0xc00cfccfu,0x3f03f801u,0x0u,0x0u,0xc0000000u,0x83f01e00u,0xc0ce1c73u,0xfcc0cc0cu,0xcc0cffcfu,0xc0cc0cc0u,0x0u,0x0u,0xfc000000u,0xce0c7fc3u,0xe0cc0cc0u,0xc7fc7fcu,0xcc0cc0ceu,0x3fc7fce0u,0x0u,0x0u,0xf0000000u,0xce1c7f83u,0xc00cc0u,0xc00c00cu,0xcc0c00c0u,0x3f07f8e1u,0x0u,0x0u,0xfc000000u,0xce0c7fc3u,0xc0cc0cc0u,0xcc0cc0cu,0xcc0cc0ccu,0x3fc7fce0u,0x0u,0x0u,0xfc000000u,0xc00cffcfu,0xc00c00u,0xc3fc3fcu,0xc00c00c0u,0xffcffc00u,0x0u,0x0u,0xfc000000u,0xc00cffcfu,0xc00c00u,0xc3fc3fcu,0xc00c00c0u,0xc00c00u,0x0u,0x0u,0xf0000000u,0xce1c7f83u,0xc00cc0u,0xc00c00cu,0xcc0cf0cfu,0x3f07f8e1u,0x0u,0x0u,0xc000000u,0xcc0cc0ccu,0xc0cc0cc0u,0xcffcffcu,0xcc0cc0ccu,0xc0cc0cc0u,0x0u,0x0u,0xf0000000u,0xc03f03u,0xc00c00cu,0xc00c00c0u,0xc00c00u,0x3f03f00cu,0x0u,0x0u,0x0u,0xc00c00cu,0xc00c00c0u,0xc00c00u,0xcc0cc00cu,0x3f07f8e1u,0x0u,0x0u,0xc000000u,0xc70ce0ccu,0xec1cc38u,0xec07c07cu,0xc38c1cc0u,0xc0ce0c70u,0x0u,0x0u,0xc000000u,0xc00c00c0u,0xc00c00u,0xc00c00cu,0xc00c00c0u,0xffcffc00u,0x0u,0x0u,0xc000000u,0xcf3cc0ccu,0xcccdecffu,0xcccccccu,0xcc0cc0ccu,0xc0cc0cc0u,0x0u,0x0u,0xc000000u,0xcc0cc0ccu,0xc7cc3cc0u,0x8cdcccecu,0xcc0cf0cfu,0xc0cc0cc0u,0x0u,0x0u,0xf0000000u,0xce1c7f83u,0xc0cc0cc0u,0xcc0cc0cu,0xcc0cc0ccu,0x3f07f8e1u,0x0u,0x0u,0xfc000000u,0xce0c7fc3u,0xe0cc0cc0u,0xc3fc7fcu,0xc00c00c0u,0xc00c00u,0x0u,0x0u,0xf0000000u,0xce1c7f83u,0xc0cc0cc0u,0xccc0cc0cu,0xc78cfcccu,0xcf0ff879u,0x0u,0x0u,0xfc000000u,0xce0c7fc3u,0xe0cc0cc0u,0xcc3fc7fcu,0xc38c1cc0u,0xc0ce0c70u,0x0u,0x0u,0xf0000000u,0xce1c7f83u,0x1c00cc0u,0x7f03f8u,0xcc0cc00eu,0x3f07f8e1u,0x0u,0x0u,0xfc000000u,0xc0ffcfu,0xc00c00cu,0xc00c00c0u,0xc00c00u,0xc00c00cu,0x0u,0x0u,0xc000000u,0xcc0cc0ccu,0xc0cc0cc0u,0xcc0cc0cu,0xcc0cc0ccu,0x3f07f8e1u,0x0u,0x0u,0xc000000u,0xcc0cc0ccu,0xe1cc0cc0u,0x30330738u,0x1e03f03u,0xc00c00cu,0x0u,0x0u,0xc000000u,0xcc0cc0ccu,0xc0cc0cc0u,0xccccccccu,0xccccccccu,0x3307f8ffu,0x0u,0x0u,0xc000000u,0xcc0cc0ccu,0x3f0738e1u,0xf01e01e0u,0xce1c7383u,0xc0cc0cc0u,0x0u,0x0u,0xc000000u,0xcc0cc0ccu,0x3f0738e1u,0xc00c01e0u,0xc00c00u,0xc00c00cu,0x0u,0x0u,0xfc000000u,0xc00ffcfu,0x380700e0u,0x700e01c0u,0xc01c0380u,0xffcffc00u,0x0u,0x0u,0x0u,0xc00000u,0x300700eu,0x30ffcffcu,0xe00700u,0xcu,0x0u,0x0u,0xc000000u,0xc00c00c0u,0xc00c00u,0xcc00c00cu,0xe007cc3u,0x380700e0u,0xc00c01c0u,0xfc0fu,0x0u,0xc00000u,0x3003801cu,0xffcffcu,0x1c03803u,0xcu,0x0u,0x0u,0x0u,0xc00000u,0x7f83f00cu,0xc0cccedcu,0xc00c00u,0xcu,0x0u,0x0u,0x30000000u,0x3303303u,0xffcffc33u,0xfc330330u,0x330ffcfu,0x33033033u,0x0u,0x0u,0x0u,0x0u,0x0u,0xffcffcu,0x0u,0x0u,0x0u,0x0u,0x0u,0x0u,0x7f03f000u,0xf0c00e00u,0xcc1cff8fu,0xff0ff8c1u,0x0u,0x0u,0xc000000u,0xc00c00c0u,0x7fc3fc00u,0xcc0ce0cu,0xcc0cc0ccu,0x3fc7fce0u,0x0u,0x0u,0x0u,0x0u,0xff8ff000u,0xc00c01cu,0xc00c00c0u,0xff0ff801u,0x0u,0x0u,0x0u,0xc00c00cu,0xff8ff0c0u,0xcc0cc1cu,0xcc0cc0ccu,0xff0ff8c1u,0x0u,0x0u,0x0u,0x0u,0x7f83f000u,0xfcc0ce1cu,0xc00cffcfu,0x3f03f801u,0x0u,0x0u,0x0u,0x1c03803u,0xc00c00cu,0xc03f03f0u,0xc00c00u,0xc00c00cu,0x0u,0x0u,0x0u,0x0u,0xff8ff000u,0xcc0cc1cu,0xcc0cc0ccu,0xff0ff8c1u,0xf0e00c00u,0x3f07u,0xc000000u,0xc00c00c0u,0x7fc3fc00u,0xcc0ce0cu,0xcc0cc0ccu,0xc0cc0cc0u,0x0u,0x0u,0xc0000000u,0xc00u,0xf00f000u,0xc00c00c0u,0xc00c00u,0x3f03f00cu,0x0u,0x0u,0xc0000000u,0xc00u,0xc00c000u,0xc00c00c0u,0xc00c00u,0xc00c00cu,0x700e00c0u,0x300u,0x30000000u,0x300300u,0xe30c3003u,0xf03b0730u,0x3b01f01u,0xc30e3073u,0x0u,0x0u,0xf0000000u,0xc00f00u,0xc00c00cu,0xc00c00c0u,0xc00c00u,0x3f03f00cu,0x0u,0x0u,0x0u,0x0u,0x7fc33c00u,0xcccccfecu,0xccccccccu,0xccccccccu,0x0u,0x0u,0x0u,0x0u,0x7fc3fc00u,0xcc0ce0cu,0xcc0cc0ccu,0xc0cc0cc0u,0x0u,0x0u,0x0u,0x0u,0x7f83f000u,0xcc0ce1cu,0xcc0cc0ccu,0x3f07f8e1u,0x0u,0x0u,0x0u,0x0u,0x7fc3fc00u,0xcc0ce0cu,0xcc0cc0ccu,0x3fc7fce0u,0xc00c00cu,0xc0u,0x0u,0x0u,0xff8ff000u,0xcc0cc1cu,0xcc0cc0ccu,0xff0ff8c1u,0xc00c00u,0xc00cu,0x0u,0x0u,0xfb0f3000u,0x300f01f0u,0x300300u,0x3003003u,0x0u,0x0u,0x0u,0x0u,0xff8ff000u,0xf801c01cu,0xe007f03u,0x3fc7fce0u,0x0u,0x0u,0xc0000000u,0xc00c00u,0x3f03f00cu,0xc00c00c0u,0xc00c00u,0x3003801cu,0x0u,0x0u,0x0u,0x0u,0xc0cc0c00u,0xcc0cc0cu,0xcc0cc0ccu,0xff0ff8c1u,0x0u,0x0u,0x0u,0x0u,0xc0cc0c00u,0x38e1cc0cu,0x3303307u,0xc01e03fu,0x0u,0x0u,0x0u,0x0u,0xc0cc0c00u,0xccc0cc0cu,0xccccccccu,0x3307f8ffu,0x0u,0x0u,0x0u,0x0u,0xe1cc0c00u,0xe03f0738u,0x83f01e01u,0xc0ce1c73u,0x0u,0x0u,0x0u,0x0u,0xc0cc0c00u,0xcc0cc0cu,0xcc0cc0ccu,0xff0ff8c1u,0xf0e00c00u,0x3f07u,0x0u,0x0u,0xffcffc00u,0xc0380300u,0x700e01u,0xffcffc03u,0x0u,0x0u,0x30000000u,0x300300u,0x3003003u,0x30030030u,0xf00c30cu,0xcc0dc0f8u,0xfc0fc0u,0xc00cu,0x30000000u,0x3303303u,0x33033033u,0x30330330u,0x3303303u,0x33033033u,0x330330u,0x0u,0x3c000000u,0xe007c0u,0x7c07c0eu,0x7c0e00e0u,0xf00c3ccu,0xcc0dc0f8u,0xfc0fc0u,0xc00cu,0x0u,0xc00000u,0xcu,0xffcffcu,0xc00000u,0xcu,0x0u,0x0u,0xfc000000u,0xcffcffcfu,0xffcffcffu,0xfcffcffcu,0xcffcffcfu,0xffcffcffu,0x0u,0x0u );

bool CharBitmap5x9( int chr, ivec2 iPos )
{
    if ( chr < 32 || chr > (32+95) )        
        return false;
    if ( iPos.x < 0 || iPos.y < 0  || iPos.x >= 5 || iPos.y >= 9 ) 
        return false;

    int bitIndex = iPos.x + iPos.y * 5;
    int dataIndex = (chr - 32) * 2;    
    if ( bitIndex >= 32 )
    {        
        dataIndex += 1;
        bitIndex -= 32;
    }

    return ((charSet5x9[dataIndex] >> bitIndex) & 0x1u) != 0u;    
}

bool CharBitmap12x20( int chr, ivec2 iPos )
{
    if ( chr < 32 || iPos.x < 0 || iPos.y < 0 || chr > (32+95) || iPos.x >= 12 || iPos.y >= 20 ) 
        return false;

#if 0
	// Why is this slower?!
    int bitIndex = iPos.x + iPos.y * 12;
    int dataIndex = (chr - 32) * 8;
    dataIndex += bitIndex >> 5;/// 32;
    bitIndex = bitIndex & 31;//% 32;
    
    return ((charSet12x20[dataIndex] >> uint(bitIndex)) & 0x1u) != 0u;    
    
#else            
    
    ivec2 iSmallPos = iPos / 2;
    
    iSmallPos -= 1;

    ivec2 iMod = iPos % 2;

    ivec2 vDiag = ivec2( -1 + iMod.x * 2, -1 + iMod.y * 2 );
    ivec4 vCoords = ivec4( iSmallPos, iSmallPos + vDiag );

    bool d   = CharBitmap5x9( chr, vCoords.xy );
    bool d1  = CharBitmap5x9( chr, vCoords.zy );
    bool d2  = CharBitmap5x9( chr, vCoords.xw );
    bool dd  = CharBitmap5x9( chr, vCoords.zw );
	d = d || d1 && d2 && !dd;
    return d;
    
#endif    
}



// This produces fairly ugly results
// Maybe look at http://bjh21.me.uk/bedstead/bedstead.c for improvements
bool CharHiRes( int charIndex, vec2 vCharUV )
{
    if ( charIndex < 32 || charIndex > (32+95) )
    {
        return false;
    }
    
    vec2 vPos = vCharUV.xy * vec2(12,20) - 2.0;
    vec2 iPos = floor(vPos / 2.0);
    vec2 fPos = fract(vPos / 2.0);
    
    bool c = CharBitmap5x9( charIndex, ivec2( iPos ) );
    
    {
        bool w = CharBitmap5x9( charIndex, ivec2( iPos ) + ivec2(-1,0) );
        bool e = CharBitmap5x9( charIndex, ivec2( iPos ) + ivec2( 1,0) );
        bool n = CharBitmap5x9( charIndex, ivec2( iPos ) + ivec2(0,-1) );
        bool s = CharBitmap5x9( charIndex, ivec2( iPos ) + ivec2(0, 1) );
        
        bool nw = CharBitmap5x9( charIndex, ivec2( iPos ) + ivec2(-1,-1) );
        bool ne = CharBitmap5x9( charIndex, ivec2( iPos ) + ivec2( 1,-1) );
        bool sw = CharBitmap5x9( charIndex, ivec2( iPos ) + ivec2(-1, 1) );
        bool se = CharBitmap5x9( charIndex, ivec2( iPos ) + ivec2( 1, 1) );
        
        if ( w && n && !nw )
        {
            if ( fPos.x + fPos.y < 1.0 )
            {
                c = true;
            }
        }
        if ( e && s && !se )
        {
            if ( fPos.x + fPos.y > 1.0 )
            {
                c = true;
            }
        }
        
        if ( e && n && !ne )
        {
            if ( fPos.x + (1.0 - fPos.y) > 1.0 )
            {
                c = true;
            }
        }        

        if ( (w && s) && !sw )
        {
            if ( (1.0 - fPos.x) + fPos.y > 1.0 )
            {
                c = true;
            }
        }        
    }
    
    return c;
}

//
//  _  __          _                         _ 
// | |/ /___ _   _| |__   ___   __ _ _ __ __| |
// | ' // _ \ | | | '_ \ / _ \ / _` | '__/ _` |
// | . \  __/ |_| | |_) | (_) | (_| | | | (_| |
// |_|\_\___|\__, |_.__/ \___/ \__,_|_|  \__,_|
//           |___/                             
//

const int KEY_SPACE = 32;
const int KEY_LEFT  = 37;
const int KEY_UP    = 38;
const int KEY_RIGHT = 39;
const int KEY_DOWN  = 40;
const int KEY_A     = 65;
const int KEY_B     = 66;
const int KEY_C     = 67;
const int KEY_D     = 68;
const int KEY_E     = 69;
const int KEY_F     = 70;
const int KEY_G     = 71;
const int KEY_H     = 72;
const int KEY_I     = 73;
const int KEY_J     = 74;
const int KEY_K     = 75;
const int KEY_L     = 76;
const int KEY_M     = 77;
const int KEY_N     = 78;
const int KEY_O     = 79;
const int KEY_P     = 80;
const int KEY_Q     = 81;
const int KEY_R     = 82;
const int KEY_S     = 83;
const int KEY_T     = 84;
const int KEY_U     = 85;
const int KEY_V     = 86;
const int KEY_W     = 87;
const int KEY_X     = 88;
const int KEY_Y     = 89;
const int KEY_Z     = 90;
const int KEY_COMMA = 188;
const int KEY_PER   = 190;

const int KEY_0 = 	48;
const int KEY_1 = 	49;
const int KEY_2 = 	50;
const int KEY_3 = 	51;
const int KEY_ENTER = 13;
const int KEY_SHIFT = 16;
const int KEY_CTRL  = 17;
const int KEY_ALT   = 18;
const int KEY_TAB	= 9;

bool Key_IsPressed( sampler2D samp, int key)
{
    return texelFetch( samp, ivec2(key, 0), 0 ).x > 0.0;    
}

bool Key_Typematic( sampler2D samp, int key)
{
    return texelFetch( samp, ivec2(key, 1), 0 ).x > 0.0;    
}

bool Key_IsToggled(sampler2D samp, int key)
{
    return texelFetch( samp, ivec2(key, 2), 0 ).x > 0.0;    
}


int Teletext_FormatDate( int x, vec4 vDate )
{
    int day = int(floor(vDate.z));
    int month = int(floor(vDate.y));

    int daySeconds = int(floor(vDate.w));
    int seconds = daySeconds % 60;
    int minute = (daySeconds / (60)) % 60;
    int hour = (daySeconds / (60*60)) % 24;
        
    int monthText[] = int[] ( 
        _J, _a, _n, 
        _F, _e, _b, 
        _M, _a, _r, 
        _A, _p, _r, 
        _M, _a, _y,
        _J, _u, _n,
        _J, _u, _l,
        _A, _u, _g,
        _S, _e, _p,
        _O, _c, _t,
        _N, _o, _v,
        _D, _e, _c );
    
    int monthChar = x;
    if ( monthChar >=0 && monthChar < 3 )
    {
    	return monthText[ monthChar + month * 3 ];
    }
    
    if ( x == 4 )
    {
    	return  _0 + (day / 10 ); 
    }
    if ( x == 5 )
    {
    	return  _0 + (day % 10 ); 
    }
    if ( x == 6 ) 
    {
        return CTRL_ALPHANUMERIC_YELLOW;
    }
    
    if ( x == 7 )
    {
    	return  _0 + (hour / 10 ); 
    }
    if ( x == 8 )
    {
    	return  _0 + (hour % 10 ); 
    }
    if ( x == 9 )
    {
    	return _COLON; 
    }
    if ( x == 10 )
    {
    	return  _0 + (minute / 10 ); 
    }
    if ( x == 11 )
    {
    	return  _0 + (minute % 10 ); 
    }
    if ( x == 12 )
    {
        return _COLON;
    }
    if ( x == 13 )
    {
    	return  _0 + (seconds / 10 ); 
    }
    if ( x == 14 )
    {
    	return  _0 + (seconds % 10 ); 
    }
    
    return _SP;
}