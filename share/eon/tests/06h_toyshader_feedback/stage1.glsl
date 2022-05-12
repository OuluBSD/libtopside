// This array contains the first 128 characters of the 8x12 raster font
// used by Windows as an option for the console font. For Microsoft users,
// this font should look familiar. Each value, when multiplied by 65535,
// contains one sample per bit. So 16 samples per component, 64 samples per
// vec4. A character can be encoded in 1.5 vec4s, but we'll round up to 2
// to make it nicely aligned.
const vec4 arrFontData[256] = vec4[256](
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
    vec4(0.0,0.0,0.0,0.0),vec4(0.0,0.0,0.0,0.0),
	vec4(0.0468757153,0.1176470588,0.0473334859,0.0001831083),
	vec4(0.0470588235,0.0,0.0,0.0),
	vec4(0.3984435798,0.4,0.0005493248,0.0),
	vec4(0.0,0.0,0.0,0.0),
	vec4(0.2109407187,0.4969253071,0.2117647059,0.4969253071),
	vec4(0.2117647059,0.0,0.0,0.0),
	vec4(0.0470588235,0.0126649882,0.1172350652,0.1882352941),
	vec4(0.0473487449,0.0001831083,0.0,0.0),
	vec4(0.0,0.1367208362,0.0945296407,0.0236209659),
	vec4(0.1921873808,0.0,0.0,0.0),
	vec4(0.0546883345,0.1058823529,0.3713130388,0.2010986496),
	vec4(0.4305943389,0.0,0.0,0.0),
	vec4(0.0468757153,0.0470588235,0.0000915541,0.0),
	vec4(0.0,0.0,0.0,0.0),
	vec4(0.1875028611,0.0472419318,0.0235294118,0.0469672694),
	vec4(0.1878690776,0.0,0.0,0.0),
	vec4(0.0234378576,0.0939345388,0.1882352941,0.0944838636),
	vec4(0.0236209659,0.0,0.0,0.0),
	vec4(0.0,0.3984435798,0.9970244907,0.3993591211),
	vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0937514305,0.4925612268,0.0941176471),
	vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),
	vec4(0.1098039216,0.0000915541,0.0,0.0),
	vec4(0.0,0.0,0.4961013199,0.0),
	vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),
	vec4(0.1098039216,0.0,0.0,0.0),
	vec4(0.0,0.3759822995,0.0944838636,0.0236209659),
	vec4(0.0039520867,0.0,0.0,0.0),
	vec4(0.2421911955,0.4507362478,0.4198519875,0.4040436408),
	vec4(0.2437018387,0.0,0.0,0.0),
	vec4(0.0312504768,0.0587777523,0.0470588235,0.0470588235),
	vec4(0.2462806134,0.0,0.0,0.0),
	vec4(0.1171892882,0.2,0.0944838636,0.0236209659),
	vec4(0.2468757153,0.0,0.0,0.0),
	vec4(0.1171892882,0.1882810712,0.110109102,0.1882352941),
	vec4(0.1179674983,0.0,0.0,0.0),
	vec4(0.1875028611,0.2352330816,0.2000457771,0.1894407568),
	vec4(0.4694895857,0.0,0.0,0.0),
	vec4(0.2460975051,0.0117647059,0.1211413748,0.1882352941),
	vec4(0.1179674983,0.0,0.0,0.0),
	vec4(0.109376669,0.0118104829,0.1211413748,0.2),
	vec4(0.1179674983,0.0,0.0,0.0),
	vec4(0.4961013199,0.3882352941,0.1889677272,0.0472419318),
	vec4(0.0470588235,0.0,0.0,0.0),
	vec4(0.1171892882,0.2,0.1179674983,0.2),
	vec4(0.1179674983,0.0,0.0,0.0),
	vec4(0.1171892882,0.2,0.2429694057,0.0941176471),
	vec4(0.0548714427,0.0,0.0,0.0),
	vec4(0.0,0.109376669,0.0004272526,0.109376669),
	vec4(0.0004272526,0.0,0.0,0.0),
	vec4(0.0,0.109376669,0.0004272526,0.109376669),
	vec4(0.0941786831,0.0001831083,0.0,0.0),
	vec4(0.1875028611,0.0472419318,0.0118104829,0.0469672694),
	vec4(0.1878690776,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0019226368,0.0019226368),
	vec4(0.0,0.0,0.0,0.0),
	vec4(0.0234378576,0.0939345388,0.3757381552,0.0944838636),
	vec4(0.0236209659,0.0,0.0,0.0),
	vec4(0.1171892882,0.1882810712,0.0472419318,0.0001831083),
	vec4(0.0470588235,0.0,0.0,0.0),
	vec4(0.2421911955,0.3882352941,0.4823529412,0.0135957885),
	vec4(0.2422369726,0.0,0.0,0.0),
	vec4(0.0468757153,0.1996795605,0.2,0.2001831083),
	vec4(0.2,0.0,0.0,0.0),
	vec4(0.2460975051,0.4,0.2437476158,0.4),
	vec4(0.2476539254,0.0,0.0,0.0),
	vec4(0.2343785763,0.3882810712,0.0117647059,0.386770428),
	vec4(0.2359349966,0.0,0.0,0.0),
	vec4(0.1210955978,0.3992675669,0.4,0.4),
	vec4(0.121919585,0.0,0.0,0.0),
	vec4(0.4961013199,0.0245059892,0.2427710384,0.0240177005),
	vec4(0.4971694514,0.0,0.0,0.0),
	vec4(0.4961013199,0.2749980926,0.2427710384,0.0240177005),
	vec4(0.0586861982,0.0,0.0,0.0),
	vec4(0.2343785763,0.3882810712,0.0117647059,0.3884794385),
	vec4(0.4859388113,0.0,0.0,0.0),
	vec4(0.1992217899,0.2,0.2468757153,0.2),
	vec4(0.2,0.0,0.0,0.0),
	vec4(0.1171892882,0.0470588235,0.0470588235,0.0470588235),
	vec4(0.1173723964,0.0,0.0,0.0),
	vec4(0.4687571527,0.1882352941,0.1882352941,0.2),
	vec4(0.1179674983,0.0,0.0,0.0),
	vec4(0.4023498894,0.2124971389,0.1180132753,0.2117647059),
	vec4(0.4039063096,0.0,0.0,0.0),
	vec4(0.0585946441,0.0235294118,0.0235294118,0.3995117113),
	vec4(0.4976577401,0.0,0.0,0.0),
	vec4(0.3867246509,0.4979171435,0.4199130236,0.3882352941),
	vec4(0.3882352941,0.0,0.0,0.0),
	vec4(0.3867246509,0.4038605325,0.4977950713,0.4511024643),
	vec4(0.3882352941,0.0,0.0,0.0),
	vec4(0.109376669,0.3875486381,0.3882352941,0.3882352941),
	vec4(0.1102006561,0.0,0.0,0.0),
	vec4(0.2460975051,0.4,0.2437476158,0.0235294118),
	vec4(0.0586861982,0.0,0.0,0.0),
	vec4(0.109376669,0.3875486381,0.3882352941,0.482230869),
	vec4(0.1884489204,0.0018310826,0.0,0.0),
	vec4(0.2460975051,0.4,0.2437476158,0.3992675669),
	vec4(0.4039063096,0.0,0.0,0.0),
	vec4(0.1171892882,0.2,0.0547341115,0.1995880064),
	vec4(0.1179674983,0.0,0.0,0.0),
	vec4(0.2460975051,0.0475623713,0.0470588235,0.0470588235),
	vec4(0.1173723964,0.0,0.0,0.0),
	vec4(0.1992217899,0.2,0.2,0.2),
	vec4(0.1179674983,0.0,0.0,0.0),
	vec4(0.1992217899,0.2,0.2,0.2),
	vec4(0.0473334859,0.0,0.0,0.0),
	vec4(0.3867246509,0.3882352941,0.419485771,0.212573434),
	vec4(0.2117647059,0.0,0.0,0.0),
	vec4(0.1992217899,0.2,0.0473334859,0.1996795605),
	vec4(0.2,0.0,0.0,0.0),
	vec4(0.1992217899,0.2,0.1179674983,0.0470588235),
	vec4(0.1173723964,0.0,0.0,0.0),
	vec4(0.4961013199,0.0994125277,0.0472419318,0.2735332265),
	vec4(0.4976119631,0.0,0.0,0.0),
	vec4(0.2343785763,0.0470588235,0.0470588235,0.0470588235),
	vec4(0.2345616846,0.0,0.0,0.0),
	vec4(0.0,0.0117341878,0.0469672694,0.1878690776),
	vec4(0.2514686809,0.0,0.0,0.0),
	vec4(0.2343785763,0.1882352941,0.1882352941,0.1882352941),
	vec4(0.2351110094,0.0,0.0,0.0),
	vec4(0.1094987411,0.3875486381,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0038910506,0.0,0.0),
	vec4(0.0470588235,0.0003662165,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.1879606317,0.2001678492),
	vec4(0.4304722667,0.0,0.0,0.0),
	vec4(0.0273441672,0.0235294118,0.3993896391,0.4),
	vec4(0.232028687,0.0,0.0,0.0),
	vec4(0.0,0.0,0.1996795605,0.0117647059),
	vec4(0.1179674983,0.0,0.0,0.0),
	vec4(0.2187533379,0.1882352941,0.2001678492,0.2),
	vec4(0.4304722667,0.0,0.0,0.0),
	vec4(0.0,0.0,0.1996795605,0.0126802472),
	vec4(0.1179674983,0.0,0.0,0.0),
	vec4(0.109376669,0.0242618448,0.1211871519,0.0235294118),
	vec4(0.0586861982,0.0,0.0,0.0),
	vec4(0.0,0.0,0.2009002823,0.2),
	vec4(0.1884489204,0.1179674983,0.0,0.0),
	vec4(0.0273441672,0.0235294118,0.4305180438,0.4),
	vec4(0.4039063096,0.0,0.0,0.0),
	vec4(0.0937514305,0.0003662165,0.0942092012,0.0941176471),
	vec4(0.4925612268,0.0,0.0,0.0),
	vec4(0.1875028611,0.0007324331,0.1884184024,0.1882352941),
	vec4(0.1999542229,0.1179674983,0.0,0.0),
	vec4(0.0273441672,0.0235294118,0.2124971389,0.2113984894),
	vec4(0.4039063096,0.0,0.0,0.0),
	vec4(0.1171892882,0.0941176471,0.0941176471,0.0941176471),
	vec4(0.4925612268,0.0,0.0,0.0),
	vec4(0.0,0.0,0.4189364462,0.4196078431),
	vec4(0.3883573663,0.0,0.0,0.0),
	vec4(0.0,0.0,0.1996948196,0.2),
	vec4(0.2,0.0,0.0,0.0),
	vec4(0.0,0.0,0.1996795605,0.2),
	vec4(0.1179674983,0.0,0.0,0.0),
	vec4(0.0,0.0,0.3993438621,0.4),
	vec4(0.2437476158,0.0586861982,0.0,0.0),
	vec4(0.0,0.0,0.2009002823,0.2),
	vec4(0.2429694057,0.4694895857,0.0,0.0),
	vec4(0.0,0.0,0.4617837797,0.02511635),
	vec4(0.0586861982,0.0,0.0,0.0),
	vec4(0.0,0.0,0.1996795605,0.0938429847),
	vec4(0.1179674983,0.0,0.0,0.0),
	vec4(0.0,0.0234988937,0.024399176,0.0235294118),
	vec4(0.1102006561,0.0,0.0,0.0),
	vec4(0.0,0.0,0.2,0.2),
	vec4(0.4304722667,0.0,0.0,0.0),
	vec4(0.0,0.0,0.2,0.2),
	vec4(0.0473334859,0.0,0.0,0.0),
	vec4(0.0,0.0,0.3882352941,0.4196078431),
	vec4(0.2117647059,0.0,0.0,0.0),
	vec4(0.0,0.0,0.2124513619,0.1098039216),
	vec4(0.3875486381,0.0,0.0,0.0),
	vec4(0.0,0.0,0.4,0.4),
	vec4(0.1884184024,0.0589608606,0.0,0.0),
	vec4(0.0,0.0,0.1923704891,0.0238040742),
	vec4(0.2466315709,0.0,0.0,0.0),
	vec4(0.2187533379,0.0470588235,0.0118104829,0.0469672694),
	vec4(0.2189364462,0.0,0.0,0.0),
	vec4(0.0937514305,0.0941176471,0.0003662165,0.0941176471),
	vec4(0.0941176471,0.0,0.0,0.0),
	vec4(0.0273441672,0.0470588235,0.1878690776,0.0472419318),
	vec4(0.0275272755,0.0,0.0,0.0),
	vec4(0.8046997787,0.4506141756,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),
	vec4(0.0,0.0,0.0,0.0),
	vec4(0.9961089494,1.0,0.0,0.0)
);

// Maps the key codes on my keyboard (yeah, I don't want to make claims about
// compatibility) to the characters each key represents. When SHIFT is held,
// I just add 256 to the number I grab from the keyboard texture, then use this
// table to look up the resulting character.
// 1 L, 2 U, 3 R, 4 D
#define REMAP_MAX 512
const int remap[REMAP_MAX] = int[REMAP_MAX](
	0x000,0x001,0x002,0x003, 0x004,0x005,0x006,0x007, 0x008,0x009,0x00a,0x00b, 0x00c,0x00d,0x00e,0x00f,
	0x010,0x011,0x012,0x013, 0x014,0x015,0x016,0x017, 0x018,0x019,0x01a,0x01b, 0x01c,0x01d,0x01e,0x01f,
	0x020,0x021,0x022,0x023, 0x024,0x001,0x002,0x003, 0x004,0x029,0x02a,0x02b, 0x02c,0x02d,0x020,0x02f,
	0x030,0x031,0x032,0x033, 0x034,0x035,0x036,0x037, 0x038,0x039,0x03a,0x03b, 0x03c,0x03d,0x03e,0x03f,
    
	0x040,0x061,0x062,0x063, 0x064,0x065,0x066,0x067, 0x068,0x069,0x06a,0x06b, 0x06c,0x06d,0x06e,0x06f,
	0x070,0x071,0x072,0x073, 0x074,0x075,0x076,0x077, 0x078,0x079,0x07a,0x05b, 0x05c,0x05d,0x05e,0x05f,
	0x060,0x061,0x062,0x063, 0x064,0x065,0x066,0x067, 0x068,0x069,0x06a,0x06b, 0x06c,0x06d,0x06e,0x06f,
	0x070,0x071,0x072,0x073, 0x074,0x075,0x076,0x077, 0x078,0x079,0x07a,0x07b, 0x07c,0x07d,0x07e,0x07f,
    
	0x080,0x081,0x082,0x083, 0x084,0x085,0x086,0x087, 0x088,0x089,0x08a,0x08b, 0x08c,0x08d,0x08e,0x08f,
	0x090,0x091,0x092,0x093, 0x094,0x095,0x096,0x097, 0x098,0x099,0x09a,0x09b, 0x09c,0x09d,0x09e,0x09f,
	0x0a0,0x0a1,0x0a2,0x0a3, 0x0a4,0x0a5,0x0a6,0x0a7, 0x0a8,0x0a9,0x0aa,0x0ab, 0x0ac,0x0ad,0x0ae,0x0af,
	0x0b0,0x0b1,0x0b2,0x0b3, 0x0b4,0x0b5,0x0b6,0x0b7, 0x0b8,0x0b9,0x03b,0x03d, 0x02c,0x02d,0x02e,0x02f,
    
	0x060,0x0c1,0x0c2,0x0c3, 0x0c4,0x0c5,0x0c6,0x0c7, 0x0c8,0x0c9,0x0ca,0x0cb, 0x0cc,0x0cd,0x0ce,0x0cf,
	0x0d0,0x0d1,0x0d2,0x0d3, 0x0d4,0x0d5,0x0d6,0x0d7, 0x0d8,0x0d9,0x0da,0x05b, 0x05c,0x05d,0x027,0x0df,
	0x0e0,0x0e1,0x0e2,0x0e3, 0x0e4,0x0e5,0x0e6,0x0e7, 0x0e8,0x0e9,0x0ea,0x0eb, 0x0ec,0x0ed,0x0ee,0x0ef,
	0x0f0,0x0f1,0x0f2,0x0f3, 0x0f4,0x0f5,0x0f6,0x0f7, 0x0f8,0x0f9,0x0fa,0x0fb, 0x0fc,0x0fd,0x0fe,0x0ff,
    
    
	0x000,0x001,0x002,0x003, 0x004,0x005,0x006,0x007, 0x008,0x009,0x00a,0x00b, 0x00c,0x00d,0x00e,0x00f,
	0x010,0x011,0x012,0x013, 0x014,0x015,0x016,0x017, 0x018,0x019,0x01a,0x01b, 0x01c,0x01d,0x01e,0x01f,
	0x020,0x021,0x022,0x023, 0x024,0x001,0x002,0x003, 0x004,0x029,0x02a,0x02b, 0x02c,0x02d,0x020,0x02f,
	0x029,0x021,0x040,0x023, 0x024,0x025,0x05e,0x026, 0x02a,0x028,0x03a,0x03b, 0x03c,0x03d,0x03e,0x03f,
    
	0x040,0x041,0x042,0x043, 0x044,0x045,0x046,0x047, 0x048,0x049,0x04a,0x04b, 0x04c,0x04d,0x04e,0x04f,
	0x050,0x051,0x052,0x053, 0x054,0x055,0x056,0x057, 0x058,0x059,0x05a,0x05b, 0x05c,0x05d,0x05e,0x05f,
	0x060,0x041,0x042,0x043, 0x044,0x045,0x046,0x047, 0x048,0x049,0x04a,0x04b, 0x04c,0x04d,0x04e,0x04f,
	0x050,0x051,0x052,0x053, 0x054,0x055,0x056,0x057, 0x058,0x059,0x05a,0x07b, 0x07c,0x07d,0x07e,0x07f,
    
	0x080,0x081,0x082,0x083, 0x084,0x085,0x086,0x087, 0x088,0x089,0x08a,0x08b, 0x08c,0x08d,0x08e,0x08f,
	0x090,0x091,0x092,0x093, 0x094,0x095,0x096,0x097, 0x098,0x099,0x09a,0x09b, 0x09c,0x09d,0x09e,0x09f,
	0x0a0,0x0a1,0x0a2,0x0a3, 0x0a4,0x0a5,0x0a6,0x0a7, 0x0a8,0x0a9,0x0aa,0x0ab, 0x0ac,0x0ad,0x0ae,0x0af,
	0x0b0,0x0b1,0x0b2,0x0b3, 0x0b4,0x0b5,0x0b6,0x0b7, 0x0b8,0x0b9,0x03a,0x02b, 0x03c,0x05f,0x03e,0x03f,
    
	0x07e,0x0c1,0x0c2,0x0c3, 0x0c4,0x0c5,0x0c6,0x0c7, 0x0c8,0x0c9,0x0ca,0x0cb, 0x0cc,0x0cd,0x0ce,0x0cf,
	0x0d0,0x0d1,0x0d2,0x0d3, 0x0d4,0x0d5,0x0d6,0x0d7, 0x0d8,0x0d9,0x0da,0x07b, 0x07c,0x07d,0x022,0x0df,
	0x0e0,0x0e1,0x0e2,0x0e3, 0x0e4,0x0e5,0x0e6,0x0e7, 0x0e8,0x0e9,0x0ea,0x0eb, 0x0ec,0x0ed,0x0ee,0x0ef,
	0x0f0,0x0f1,0x0f2,0x0f3, 0x0f4,0x0f5,0x0f6,0x0f7, 0x0f8,0x0f9,0x0fa,0x0fb, 0x0fc,0x0fd,0x0fe,0x0ff
);

// Unpack the big ugly lump of vec4s into a 128x96 texture
float sample8x12Tex(vec2 coords)
{
    ivec4 coordsInt = ivec4(coords.xyxy / vec4(10.0, 16.0, 1.0, 1.0));
    coordsInt.zw -= coordsInt.xy * ivec2(10, 16) + ivec2(1, 2);
    
    if (coordsInt.z < 0 || coordsInt.w < 0 || coordsInt.z >= 8 || coordsInt.w >= 12) return 0.0;
    
    int baseOffset = (coordsInt.x << 1) | (coordsInt.y << 5);
    
    vec4 sampleHalf = arrFontData[baseOffset | ((coordsInt.w >> 3) & 1)];
    
    float sampleComp = sampleHalf[(coordsInt.w >> 1) & 3];
    int sampleRawFull = int(sampleComp * 65535.0 + 0.5);
    int bitSelection = ((coordsInt.w & 1) << 3) | (coordsInt.z & 7);
    sampleRawFull >>= bitSelection;
    
    return float(sampleRawFull & 1);
}

// True if compA is in a rectangle centred at compB with size rectSize.
bool inRect(vec2 compA, vec2 compB, vec2 rectSize)
{
    vec2 delta = abs(compA - compB);
    delta += delta - 1.0;
    delta = step(rectSize, delta);
    return delta.x + delta.y < 0.5;
}

// Returns the highest-value key that was pressed ... 8 frames ago ;)
float getTappedLetter()
{
    return texture(iChannel0, vec2(160.5, 8.5) / iResolution.xy).r * 256.0;
}

// Returns the highest-value key that was held ... 8 frames ago >_<
float getHeldLetter()
{
    return texture(iChannel0, vec2(161.5, 8.5) / iResolution.xy).r * 256.0;
}

// 1.0 if ESC is tapped or if starting from scratch, else 0.0
float getReset()
{
    return 1.0 - texture(iChannel0, vec2(2.5, 209.5) / iResolution.xy).r;
}

// Similar to getTappedLetter, but it performs the mapping operations to determine
// which glyph should be displayed.
float getFinalTyped()
{
    int baseLetter = int(getTappedLetter());
    baseLetter |= int(2.0 * texture(iChannel0, vec2(1.5, 209.5) / iResolution.xy).r) << 8;
    
    int mappedLetter = remap[baseLetter];
    return float(mappedLetter) + 0.5;
}

// Returns a value between vec2(0.0, 0.0) and vec2(80.0, 80.0) representing the current
// position of the cursor. x=acrossRow, y=downColumn
vec2 getCursorPos()
{
    float numChars = 80.0 * 80.0;
    float rawPos = 0.5 + texture(iChannel0, vec2(0.5, 209.5) / iResolution.xy).r * numChars;
    
    vec2 result;
    result.y = floor(rawPos / 80.0);
    result.x = rawPos - 80.0 * result.y - 0.5;
    return result;
}

// Moves the cursor position forward when typing, or back when backspacing. Also handles
// tabs and newlines.
float processCursor()
{
    float numChars = 80.0 * 80.0;
    float rawPos = texture(iChannel0, vec2(0.5, 209.5) / iResolution.xy).r * numChars;
    float tappedLetter = getFinalTyped();
    
    if (tappedLetter >= 31.5)
    {
        // Go back if tappedLetter is 0x08: backspace
        rawPos += 1.0;
    }
    
    vec4 specialChars = vec4(8.5, 9.5, 13.5, 3.0);
    specialChars = abs(specialChars - tappedLetter);
    
    // Backspace
    if (specialChars.x < 0.5)
    {
        rawPos -= 1.0;
    }
    
    // Tab
    else if (specialChars.y < 0.5)
    {
        rawPos += 1.0 + fract((83.0 - rawPos) / 4.0) * 4.0;
    }
    
    // Enter
    else if (specialChars.z < 0.5)
    {
        rawPos += 1.0 + fract((159.0 - rawPos) / 80.0) * 80.0;
    }
    
    // Arrows
    else if (specialChars.w < 2.0)
    {
        float d = tappedLetter - 1.5;
        rawPos += (((3.0 - d) * d + 1.0)* d - 3.0 +
            ((6.0 - d)* d - 8.0) * d * 80.0) / 3.0;
    }
    
    rawPos = floor(rawPos + 0.5);
    return max(min(rawPos / numChars, 1.0), 0.0);
}

// Recursively downsample the keyboard texture until we find the highest-index
// key which is being pressed. It's a classic divide-and-conquer approach which
// avoids having to do 256 samples. Maybe I'm a dummy, but this was much faster.
// The only downside is that there is a delay of 8 frames until we finally get
// the key. Since there's a 60fps frame limit, that's at least 0.1333 secs.
// Of course, that's a "feature" to simulate an old-fashioned slow PC ;)
float populatePressedLetter(vec2 fragCoord, vec2 origin, float level)
{
    vec2 uvPixel = 1.0 / iResolution.xy;
    vec2 uvBuffer = (fragCoord - origin) * uvPixel;
    vec2 uvKeyboard = fragCoord - origin;
    uvKeyboard = vec2(uvKeyboard.x / 256.0, level);
    
    float result = 0.0;
    
    if (fragCoord.y < 1.0)
    {
        result = texture(iChannel1, uvKeyboard).r * uvKeyboard.x;
    }
    else
    {
        vec4 uvKeyboardAlt = 
            uvBuffer.xyxy *
            vec4(2.0, 1.0, 2.0, 1.0) +
            vec4(0.0, -uvPixel.y, uvPixel.x, -uvPixel.y);
        uvKeyboardAlt += (origin * uvPixel).xyxy;
        
        float sampleL = texture(iChannel0, uvKeyboardAlt.xy).r;
        float sampleH = texture(iChannel0, uvKeyboardAlt.zw).r;
        
        result = max(sampleL, sampleH);
    }
    
    return result;
}

// Stores typed letters in the screen buffer at the cursor position.
float processBuffer(vec2 uv, vec2 fragCoord)
{
    vec2 bufferUV = fragCoord - vec2(0.5, 128.5);
    
    float result;
    result = texture(iChannel0, uv).r;
    
    vec2 cursorPos = getCursorPos();
    if (inRect(cursorPos, bufferUV, vec2(0.5, 0.5)))
    {
        float chr = getFinalTyped();
        
        if (chr >= 32.0)
        {
    		result = chr / 256.0;
        }
        
        // Type a space (empty) in this position if we're backspacing
        if (texture(iChannel0, vec2(3.5, 209.5) / iResolution.xy).r >= 0.5)
        {
        	result = 0.125;
        }
    }
    
    return result;
}

// populatePressedLetter has an 8-frame delay, so we need to also delay
// shift keys by that same amount. It feels really awkward without this delay matching.
float processShiftLag()
{
    float result = texture(iChannel0, vec2(1.5, 209.5) / iResolution.xy).r;
    
    result += result + texture(iChannel1, vec2(16.5 / 256.0, 0.16667)).r / 256.0;
    
    return fract(result);
}

// populatePressedLetter has an 8-frame delay, so we have to wait until it's done moving
// before we delete the character underneath the caret. So that's 8 frames to detect the
// key, then the next frame moves the caret, THEN we delete. 10 frames, hence 2^10=1024
float processBSLag()
{
    float result = texture(iChannel0, vec2(3.5, 209.5) / iResolution.xy).r;
    
    result += result + texture(iChannel1, vec2(8.5 / 256.0, 0.16667)).r / 1024.0;
    
    return fract(result);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = fragCoord.xy / iResolution.xy;
    
    vec4 resetFragColor = vec4(0.0, 0.0, 0.0, 1.0);
    fragColor = resetFragColor;
    
    // This zone x[0, 160), y[0, 128) contains the font palette
    if (fragCoord.x < 160.0 && fragCoord.y < 128.0)
    {
        resetFragColor.r = sample8x12Tex(fragCoord);
    	fragColor.r = resetFragColor.r;
    }
    
    // This zone x[160, 416), y[0, 8) contains the currently tapped letter.
    // Because of the way the key selection works in this shader, as y->8,
    // This starts to contain reductions of the next zone (held letter).
    else if (inRect(fragCoord, vec2(288.5, 4.5), vec2(256.0, 8.0)))
    {
        fragColor.r = populatePressedLetter(fragCoord, vec2(160.5, 0.5), 0.5);
    }
    
    // Similar to above, but for the held letters. After the first round of
    // reduction, it actually ends up just going into that next zone, so if
    // you're looking for a lazy optimisation, change that 4.5 to 1.0 and
    // that 8.0 to 1.0. But I like it matching, so #dealwithit
    else if (inRect(fragCoord, vec2(544.5, 4.5), vec2(256.0, 8.0)))
    {
        fragColor.r = populatePressedLetter(fragCoord, vec2(416.5, 0.5), 0.16667);
    }
    
    // This zone contains the screen buffer. Every character you type will be
    // shoved in here, kicking and screaming.
    else if (inRect(fragCoord, vec2(40.5, 168.5), vec2(80.0, 80.0)))
    {
        fragColor.r = processBuffer(uv, fragCoord.xy);
    }
    
    // This texel stores the cursor position.
    else if (inRect(fragCoord, vec2(0.5, 209.5), vec2(1.0, 1.0)))
    {
        fragColor.r = processCursor();
    }
    
    // This texel is used to delay the shift key so it's in sync with the other
    // keys, which are delayed by 8 frames as part of the populatePressedLetter's
    // recursive nature.
    else if (inRect(fragCoord, vec2(1.5, 209.5), vec2(1.0, 1.0)))
    {
        fragColor.r = processShiftLag();
    }
    
    // This texel is used to detect fresh starts and/or when you press ESC.
    else if (inRect(fragCoord, vec2(2.5, 209.5), vec2(1.0, 1.0)))
    {
        resetFragColor.r = step(0.5, abs(getTappedLetter() - 27.0));
        fragColor.r = resetFragColor.r;
    }
    
    // This texel is used to delay the backspace key so it's in sync with the other
    // keys, which are delayed by 8 frames as part of the populatePressedLetter's
    // recursive nature.
    else if (inRect(fragCoord, vec2(3.5, 209.5), vec2(1.0, 1.0)))
    {
        fragColor.r = processBSLag();
    }
    
    // Reset when restarting.
    fragColor = mix(fragColor, resetFragColor, getReset());
}
