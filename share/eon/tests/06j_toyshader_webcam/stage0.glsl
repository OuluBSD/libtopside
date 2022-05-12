vec4 WebCamPixelAt(vec2 pos) {
    return texture(iChannel0, pos);
}

void mainImage( out vec4 color, in vec2 pos )
{
    int time = int(iTime)%25;

    //Polarisation.
    if (time <= 5) {
        color = WebCamPixelAt(pos/iResolution.xy);
        if (int(pos.x) % 2 == 0) {
            color = WebCamPixelAt(1.-pos/iResolution.xy);
        }
        
    }
    
    //Edge Detection.
    if (time >= 5 && time <= 10) {
    	color =  WebCamPixelAt(pos/iResolution.xy);
   		color = color - WebCamPixelAt((pos+vec2(1., 1.))/iResolution.xy);
    
    }
    
    //Art.
    if (time >= 10 && time <= 12) {
        color =  WebCamPixelAt( pos/iResolution.xy);
        color =  WebCamPixelAt( vec2(color.x, color.y));
    }
    
    if (time > 12 && time <= 15) {
     	color =  WebCamPixelAt( pos/iResolution.xy);
    	color =  WebCamPixelAt( vec2(color.y, color.x));   
    }
    
    //Normal webcam.
    if (time >= 20) { 
    	color =  WebCamPixelAt( pos/iResolution.xy);
    }
    
    //Why so serious?
    if (time > 15 && time <= 20) {
        color =  WebCamPixelAt((pos+sin(pos.x*25.)*4.)/iResolution.xy);
    }
}