// Teletext
// @P_Malin
// https://www.shadertoy.com/view/4dVBRD

// Gallery images by @horsenburger - check out the amazing teletext artwork at
// www.horsenburger.com

// Type Number to select Page e.g. 300 (or use up / down arrow for prev / next)
// Space / Mouse Click = Reveal
// M = Mix (change channel 2 in the image shader to video for a more authentic feel)
// Enter = Index (page 100)

// Wait for pages to change



// Image Shader - Render the characters and colors output from Buffer B

#define ENABLE_AA		1
const float AA_Size = 4.0;

#define HIRES_FONT  			0
#define SHOW_GFX_HEX_VALUES 	0

#define USE_FONT_TEXTURE    	0

#define BITMAP_FONT_TEST		0
#define BITMAP_FONT_TEST_CHAR	_AMPERSAND


// http://www.bighole.nl/pub/mirror/homepage.ntlworld.com/kryten_droid/teletext/spec/teletext_spec_1974.htm

#define iChannelCharData 		iChannel0
#define iChannelBackgroundData 	iChannel2
#define iChannelKeyboard		iChannel3

int GetGfxCharIndex( int charIndex )
{
    if ( charIndex >= 16 * 2 && charIndex < 16 * 4 )
        return charIndex - 16 * 2;

    if ( charIndex >= 16 * 6 && charIndex < 16 * 8 )
        return 16 * 2 + charIndex - 16 * 6;

    return 0;
}

float SampleFontCharacter( int charIndex, vec2 vCharUV )
{
#if USE_FONT_TEXTURE    
    vec2 vUV;
    
    vCharUV.x = vCharUV.x * 0.6 + 0.25;
    
    vUV.x = (float(charIndex % 16) + vCharUV.x) / 16.0;
    vUV.y = (float(charIndex / 16) + vCharUV.y) / 16.0;
    
	return clamp( ( 0.503 - texture(iChannel1, vUV).w) * 100.0, 0.0, 1.0 );
#else    
	float fCharData = 0.0;
    ivec2 vCharPixel = ivec2(vCharUV * vec2(kCharPixels) );   

    #if !HIRES_FONT
        bool bCharData = CharBitmap12x20( charIndex, vCharPixel );            
        fCharData = bCharData ? 1.0 : 0.0;
    #else
        bool bCharData = CharHiRes( charIndex, vCharUV );
        fCharData = bCharData ? 1.0 : 0.0;
    #endif
    
    return fCharData;
#endif
}

vec4 TeletextScreen( vec2 vScreenUV )
{      
    ivec2 vCharIndex = ivec2(floor(vScreenUV * vec2(kScreenChars)));

    if ( any( lessThan( vCharIndex, ivec2(0) ) ) )
    {
        return vec4(0);
	}    
    if ( any( greaterThanEqual( vCharIndex, kScreenChars ) ) )
    {
        return vec4(0);
	}
    
    vec4 vCharSample = texelFetch( iChannelCharData, vCharIndex, 0 );
    //vCharSample=vec4(7,GFX_ALPHANUMERIC,NORMAL_HEIGHT,_a);

    int charIndex = int(vCharSample.a);

    vec2 vCharUV = fract( vScreenUV * vec2(kScreenChars) );
    
    // Double height
    switch( int(vCharSample.z) )
    {
        default:
        case NORMAL_HEIGHT:
        break;
        
        case DOUBLE_HEIGHT_TOP:
        	vCharUV.y = vCharUV.y / 2.0;
        break;

        case DOUBLE_HEIGHT_BOTTOM:
        	vCharUV.y = vCharUV.y / 2.0 + 0.5;
        break;
    }
    
    int iFgCol = int(vCharSample.r) & 7;
    int iBgCol = (int(vCharSample.r) >> 8) & 7;
    
    int iGfx = int(vCharSample.g);
    
    vec4 col = vec4( kColors[ iBgCol ], 1.0 );
    if ( iBgCol == 0 )
    {
        col.a = 0.0;
    }

    if ( charIndex >= 0 )
    {
        if ( iGfx == GFX_ALPHANUMERIC )
        {
            float fCharData = SampleFontCharacter( charIndex, vCharUV );
            if ( fCharData > 0.0 )
            {
                vec4 vChCol = vec4( kColors[ iFgCol ], iFgCol == 0 ? 0.0 : 1.0 );
                col = mix( col, vChCol, fCharData );
            }
        }
        else
        {        
            int iGfxCharIndex = GetGfxCharIndex( charIndex );

            ivec2 vGfxCharPixel = ivec2(vCharUV * vec2(kCharPixels) );   

            #if !SHOW_GFX_HEX_VALUES
            ivec2 vGfxPixel = ivec2(vGfxCharPixel.x / 6, vGfxCharPixel.y / 7 );
            
            ivec2 vMosaicPixel = ivec2(vGfxCharPixel.x % 6, vGfxCharPixel.y % 7 );

            bool bGfxPixel = true;
            if ( iGfx == GFX_SEPARATED )
            {
                if ( vMosaicPixel.x > 3 || vMosaicPixel.y > 4 || vMosaicPixel.x < 1 || vMosaicPixel.y < 1 )
                {
                    bGfxPixel = false;
                }
            }
            
            if ( bGfxPixel )
            {
                int iGfxBit = vGfxPixel.x + vGfxPixel.y * 2;

                if ( ((iGfxCharIndex >> iGfxBit) & 1) != 0 )
                {
                    col = vec4( kColors[ iFgCol ], 1.0 );
                    if ( iFgCol == 0 )
                    {
                        col.a = 0.0;
                    }                    
                }
            }

            #else
            // Show hex values
            int ch[] = int[]( _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B, _C, _D, _E, _F );

            int d = 16;

            if ( vGfxCharPixel.y > 10 )
            {
                vGfxCharPixel.y -= 10;
                d = 1;
            }

            charIndex = ch[ (iGfxCharIndex / d) % 16 ];

            vGfxCharPixel.y *= 2;
            bool bCharData = CharBitmap12x20( charIndex, vGfxCharPixel );
            if ( bCharData )
            {
                col = vec4(kColors[ iFgCol ], 1);
            }		
            #endif
        }
    }
    
	return col;
}

vec3 SingleSample( vec2 vCoord )
{
    vec4 col = vec4(0);

    float fScale = float(kScreenResolution.y) / iResolution.y;
    
    float fScaleX = fScale * ( float(kScreenResolution.x) / float(kScreenResolution.y) ) / (kScreenRatio.x / kScreenRatio.y);
    
    vCoord.x -= (iResolution.x - float(kScreenResolution.x) / fScaleX) * 0.5;
    
    vec2 vScreenUV = vCoord * vec2(fScaleX, fScale);
        
    vScreenUV.y = float(kScreenResolution.y) - 1.0 - vScreenUV.y;
    vScreenUV = vScreenUV / vec2(kScreenResolution.xy);
        
    col = TeletextScreen( vScreenUV );
    
    vec2 vBackgroundUV = vScreenUV;
    vBackgroundUV.y = 1.0 - vBackgroundUV.y;
    //vBackgroundUV += vec2(0.05, 0.1) * iTime;
    vec3 vBackground = texture(iChannelBackgroundData, vBackgroundUV ).rgb;
    
	if ( !Key_IsToggled( iChannelKeyboard, KEY_M ) )
    {
    	vBackground = vec3(0.1);
    }
    
    if ( any( lessThan( vBackgroundUV, vec2(0) ) ) ) vBackground = vec3(0);
    if ( any( greaterThanEqual( vBackgroundUV, vec2(1) ) ) ) vBackground = vec3(0);
    
    vec3 vResult = mix( vBackground, col.rgb, col.a );
    
    // Scanlines
    //vResult *= cos( 3.14 + vScreenUV.y * 3.14 * 2.0 * 625.0 ) * 0.1 + 0.9;
    
    return vResult;
}

vec3 BitmapFontTest( vec2 vUV, int testChar )
{
    vec3 col = vec3(0);

#if 1
    vec2 vPixelPos = vUV * vec2(kCharPixels);
    ivec2 iPixelPos = ivec2( vPixelPos );
    iPixelPos.y = 19 - iPixelPos.y;
    bool bResult = CharBitmap12x20( testChar, iPixelPos );
#else
    vec2 vPixelPos = vUV * vec2(kSmallCharPixels);    
    ivec2 iPixelPos = ivec2( vPixelPos );
    iPixelPos.y = 8 - iPixelPos.y;
    bool bResult = CharBitmap5x9( testChar, iPixelPos );
#endif
    
    if ( bResult )
    {
        col = vec3(1);
    }
    else
    {
        col = vec3(0);        
    }
    
    vec2 vSubPixelPos = fract( vPixelPos );
    
    if ( vSubPixelPos.x > 0.9 || vSubPixelPos.x < 0.1)
        col = vec3(0,0,1);
    if ( vSubPixelPos.y > 0.9 || vSubPixelPos.y < 0.1)
        col = vec3(0,0,1);
    
    return col;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 vUV = fragCoord/iResolution.xy;

    vec3 col = vec3(0);

#if ENABLE_AA
    float count = 0.0;
    
    for ( float aaY = 0.; aaY < AA_Size; aaY++ )
    {
        for ( float aaX = 0.; aaX < AA_Size; aaX++ )
        {
            vec3 vSample = SingleSample(fragCoord + vec2(aaX, aaY) / AA_Size );
            col += vSample * vSample;
        	count += 1.0;
        }	
    }
    
    col /= count;
    col = sqrt( col );
#else    
    col = SingleSample(fragCoord + 0.0001);    
#endif    
 
#if BITMAP_FONT_TEST != 0
    col = BitmapFontTest( vUV, BITMAP_FONT_TEST_CHAR );
#endif    
  
    fragColor = vec4(col,1.0);
    
    //fragColor = texelFetch( iChannel1, ivec2(fragCoord) / 3, 0 );    
}