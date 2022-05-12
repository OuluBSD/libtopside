// Buf B - Interpret the Teletext Data.
// Read the Teletext Character Data from BufA and convert to character values and colors to display

#define iChannelScreenData 	iChannel0
#define iChannelKeyboard	iChannel1

int GetTeletextCode( ivec2 coord )
{
    return int( texelFetch( iChannelScreenData, ivec2( coord ), 0 ).r );
}

struct TeletextState
{
    int chr;    

    int iFgCol;
    int iBgCol;

    int iHeldChar;    
    bool bHeldSeparated;
    
    bool bDoubleHeight;
    bool bFlash;
    bool bGfx;
    bool bConceal;
    bool bSeparatedGfx;
    bool bHoldGfx;
    
    int cmd;
};    
    

TeletextState TeletextState_Default()
{
    TeletextState state;
    
    state.chr = 0x20;
    
    state.iFgCol = 7;
    state.iBgCol = 0;
    
    state.iHeldChar = 0x20;
    state.bHeldSeparated = false;
    
    state.bDoubleHeight = false;
    state.bFlash = false;    
    state.bGfx = false;
    state.bConceal = false;
    state.bSeparatedGfx = false;
    state.bHoldGfx = false;
    
    state.cmd = -1;
    
    return state;
}

bool IsAnyOfRowDoubleHeight( ivec2 coord )
{
    for ( int x = 0; x < kScreenChars.x; x++ )
    {
        int chr = GetTeletextCode( ivec2(x, coord.y) );
        
        if ( chr == CTRL_DOUBLE_HEIGHT )
        {
            return true;
        }
    }
    
    return false;    
}

int GetDoubleHeightType( ivec2 coord )
{
    int count = 0;
    
    for ( int y = coord.y; y >= 0; y-- )
    {
        if ( !IsAnyOfRowDoubleHeight( ivec2( coord.x, y ) ) )
        {
            break;
		}
		
		count++;
    }
    
    if ( count == 0 )
        return NORMAL_HEIGHT;
    
    if ( (count % 2) == 0 )
        return DOUBLE_HEIGHT_BOTTOM;
        
    return DOUBLE_HEIGHT_TOP; 
}

void TeletextState_SetAlphanumericColor( inout TeletextState state, int color )
{
    state.iFgCol = color;
    state.bGfx = false;
    state.bConceal = false;
}

void TeletextState_SetGfxColor( inout TeletextState state, int color )
{
    state.iFgCol = color;
    state.bGfx = true;            
    state.bConceal = false;
}

bool IsControlCharacter( int chr )
{
    if ( chr >= 128 )
        return true;
    
    return false;
}

bool IsBlastThroughCharacter( int chr )
{
	if ( chr >= _AT && chr <= _HASH ) return true;
    
    return false;
}

bool IsHoldCharacter( int chr )
{    
    // The Held Graphics Character is only defined during the Graphics Mode.
    // It is then the most recent character with b6=1 in its character code,
    // providing that there has been no intervening change in either 
    // the Alphanumerics/Graphics or the Normal/Double Height modes.
    if ((chr & (1 << 5)) != 0) return true;
    
    return false;
}

bool Reveal()
{    
    return (iMouse.z > 0.0) || Key_IsPressed( iChannelKeyboard, KEY_SPACE );
}

int TeletextState_GetChar( TeletextState state )
{
    if ( state.bConceal )
    {
        if ( !Reveal() )
        {
        	return _SP;
        }
    }
    
    if ( IsControlCharacter( state.chr ) )
    {
        if ( state.bGfx && state.bHoldGfx )
        {
            return state.iHeldChar;
        }
        else
        {
            return _SP;
        }
    }    
    return state.chr;
}


bool TeletextState_GetSeparatedGfx( TeletextState state )
{
    if ( IsControlCharacter( state.chr ) )
    {
        if ( state.bHoldGfx )
        {
            return state.bHeldSeparated;
        }
        else
        {
            return false;
        }
    }    
    
    return state.bSeparatedGfx;
}

TeletextState GetState( ivec2 coord )
{
    TeletextState state = TeletextState_Default();
    
    for ( int x = 0; x <= coord.x; x++ )
    {
        // Process commands that are deferred until next character
        switch( state.cmd )
        {
            case CTRL_NUL:
            	TeletextState_SetAlphanumericColor( state, COLOR_BLACK );
            break;
            case CTRL_ALPHANUMERIC_RED:
            	TeletextState_SetAlphanumericColor( state, COLOR_RED );
            break;
            case CTRL_ALPHANUMERIC_GREEN:
            	TeletextState_SetAlphanumericColor( state, COLOR_GREEN );
            break;
            case CTRL_ALPHANUMERIC_MAGENTA:
            	TeletextState_SetAlphanumericColor( state, COLOR_MAGENTA );
            break;
            case CTRL_ALPHANUMERIC_BLUE:
            	TeletextState_SetAlphanumericColor( state, COLOR_BLUE );
            break;
            case CTRL_ALPHANUMERIC_YELLOW:
            	TeletextState_SetAlphanumericColor( state, COLOR_YELLOW );
            break;
            case CTRL_ALPHANUMERIC_CYAN:
            	TeletextState_SetAlphanumericColor( state, COLOR_CYAN );
            break;
            case CTRL_ALPHANUMERIC_WHITE:
            	TeletextState_SetAlphanumericColor( state, COLOR_WHITE );
            break;
            
            case CTRL_GFX_RED:
            	TeletextState_SetGfxColor( state, COLOR_RED );
            break;            
            case CTRL_GFX_GREEN:
            	TeletextState_SetGfxColor( state, COLOR_GREEN );
            break;            
            case CTRL_GFX_YELLOW:
            	TeletextState_SetGfxColor( state, COLOR_YELLOW );
            break;            
            case CTRL_GFX_BLUE:
            	TeletextState_SetGfxColor( state, COLOR_BLUE );
            break;            
            case CTRL_GFX_MAGENTA:
            	TeletextState_SetGfxColor( state, COLOR_MAGENTA );
            break;            
            case CTRL_GFX_CYAN:
            	TeletextState_SetGfxColor( state, COLOR_CYAN );
            break;            
            case CTRL_GFX_WHITE:
            	TeletextState_SetGfxColor( state, COLOR_WHITE );
            break;  
            
            case CTRL_RELEASE_GFX:
            	state.bHoldGfx = false;
            break;            
        }

        state.cmd = -1;
        
        state.chr = GetTeletextCode( ivec2(x, coord.y) );
        
        switch( state.chr )
        {
            case CTRL_NUL:
            	state.cmd = CTRL_NUL;
            break;            
            case CTRL_ALPHANUMERIC_RED:
            	state.cmd = CTRL_ALPHANUMERIC_RED;
            break;
            case CTRL_ALPHANUMERIC_GREEN:
            	state.cmd = CTRL_ALPHANUMERIC_GREEN;
            break;
            case CTRL_ALPHANUMERIC_MAGENTA:
            	state.cmd = CTRL_ALPHANUMERIC_MAGENTA;
            break;
            case CTRL_ALPHANUMERIC_BLUE:
            	state.cmd = CTRL_ALPHANUMERIC_BLUE;
            break;
            case CTRL_ALPHANUMERIC_YELLOW:
            	state.cmd = CTRL_ALPHANUMERIC_YELLOW;
            break;
            case CTRL_ALPHANUMERIC_CYAN:
            	state.cmd = CTRL_ALPHANUMERIC_CYAN;
            break;
            case CTRL_ALPHANUMERIC_WHITE:
            	state.cmd = CTRL_ALPHANUMERIC_WHITE;
            break;
            case CTRL_GFX_RED:
            	state.cmd = CTRL_GFX_RED;
            break;            
            case CTRL_GFX_GREEN:
            	state.cmd = CTRL_GFX_GREEN;
            break;            
            case CTRL_GFX_YELLOW:
            	state.cmd = CTRL_GFX_YELLOW;
            break;            
            case CTRL_GFX_BLUE:
            	state.cmd = CTRL_GFX_BLUE;
            break;            
            case CTRL_GFX_MAGENTA:
            	state.cmd = CTRL_GFX_MAGENTA;
            break;            
            case CTRL_GFX_CYAN:
            	state.cmd = CTRL_GFX_CYAN;
            break;            
            case CTRL_GFX_WHITE:
            	state.cmd = CTRL_GFX_WHITE;
            break;            
            
            case CTRL_FLASH:
            	state.bFlash = true;
           	break;
            case CTRL_STEADY:
            	state.bFlash = false;
           	break;
            case CTRL_NORMAL_HEIGHT:
            	state.bDoubleHeight = false;
				state.iHeldChar = 0x20;
            break;
            case CTRL_DOUBLE_HEIGHT:
            	state.bDoubleHeight = true;
				state.iHeldChar = 0x20;
            break;
            case CTRL_NEW_BACKGROUND:
            	state.iBgCol = state.iFgCol;
            break;
            case CTRL_BLACK_BACKGROUND:
            	state.iBgCol = COLOR_BLACK;
            break;
            
            case CTRL_HOLD_GFX:
            	state.bHoldGfx = true;
            break;

            case CTRL_RELEASE_GFX:
            	state.cmd = CTRL_RELEASE_GFX;
            break;
            
            case CTRL_CONTIGUOUS_GFX:
            	state.bSeparatedGfx = false;
            break;

            case CTRL_SEPARATED_GFX:
            	state.bSeparatedGfx = true;
            break;
            
            case CTRL_CONCEAL:
            	state.bConceal = true;
            break;
        }
                
        if ( state.bGfx )
        {
            if ( IsHoldCharacter( state.chr ) )
            {
            	state.iHeldChar = state.chr;
                state.bHeldSeparated = state.bSeparatedGfx;
            }
        }
    }   
    
    return state;
}


ivec4 GetInfo( ivec2 coord )
{    
    int iCol = 7;
    int iBgCol = 0;
    int iDoubleHeight = 0;

    TeletextState state = GetState( coord );
 
    int chr = TeletextState_GetChar( state );
    
    int doubleHeightType = GetDoubleHeightType( coord );
    
    if ( doubleHeightType == DOUBLE_HEIGHT_BOTTOM )
    {
        if ( state.bDoubleHeight )
        {
            iDoubleHeight = DOUBLE_HEIGHT_BOTTOM;
        }
        else
        {
            chr = _SP;
        }
    }
	else
    if ( state.bDoubleHeight )
    {
        iDoubleHeight = DOUBLE_HEIGHT_TOP;
    }
    
    if ( state.bFlash )
    {
        if ( mod( iTime, 2.0 ) < 0.5 )
        {
            chr = _SP;
        }
    }
    
    int gfx = GFX_ALPHANUMERIC;
    if ( state.bGfx )
    {
        if ( TeletextState_GetSeparatedGfx( state ) )
        {
            gfx = GFX_SEPARATED;
        }
        else
        {
            gfx = GFX_CONTINUOUS;
        }
    }
    
    if ( IsBlastThroughCharacter( chr ) ) gfx = 0;
    
    int col = state.iFgCol + (state.iBgCol << 8);
    
    return ivec4( col, gfx, iDoubleHeight, chr );
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    ivec2 iFragCoord = ivec2( fragCoord );
    
    if ( any( greaterThanEqual( iFragCoord, kScreenChars ) ) )
    {
        fragColor = vec4( 0);
        discard;
        return;
    }
    
    ivec4 info = GetInfo( ivec2(iFragCoord) );
    
    fragColor = vec4( info.x, info.y, info.z, info.w );
}
