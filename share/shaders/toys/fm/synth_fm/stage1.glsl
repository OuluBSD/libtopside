vec2 mainSound( float time )
{
    float f = 220.0;
                  
    float im = 20.0 + 18.0*sin(0.21*6.2831*time);
    float y = sin( 6.2831*f*time + im*sin(0.25*6.2831*f*time) );
        
    y *= exp(-2.0*fract(8.0*time));
    
    return vec2(y);
}