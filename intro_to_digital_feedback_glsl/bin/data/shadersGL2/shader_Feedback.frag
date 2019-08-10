#version 120

//tex0 will always be the first texture that you bind to the gpu
uniform sampler2DRect tex0;

uniform vec2 feedback_Displace;

//mixxx is a variable from the oF side of things that we are using to control the implicit convolution.  the word 'mix' is reserved for a function that performs linear interpolation in glsl so i added some xxxes.
uniform float mixxx;

//texCoordVarying is declared over in the vertex shader, this is the x y coordinate of which pixel the gpu is drawing on the screen.  this varies per frame so thats why this datatype is called varying. generally speaking variables defined within the shaders are varying because they change with each pixel and variables definied within oF (or whatever wrapper yr using to send info to shaders) will be uniform because they are the same for each pixel but can change on a frame by frame basis
varying vec2 texCoordVarying;





void main()
{
	vec4 color = vec4(0,0,0,0);
    
    
    //lets grab the color from the feedback texture
    //texture2DRect is a function that takes two arguments, a texture and a vec2 and then returns the pixel information from the texture at the (x,y) location given by the vec2 components in the form (red, green, blue, alpha) where each value is normalized between 0 and 1.
    
    //we want to grab the color from the current location first
    vec4 tex0_color=texture2DRect(tex0, texCoordVarying);
    
    
    //and then grab a color from a displaced location so that we can perform an implicit convolution
    vec4 feedback_color=texture2DRect(tex0, texCoordVarying+feedback_Displace);
    
    //and we will need to also change some aspects of the values of the pixels to get color based feedback as well!
    //feedback_color.g=1.1*tex0_color.g;
    //feedback_color.g=fract(tex0_color.g);
    
    
    //just mixxing the displaced channel into the frame
    color=mixxx*feedback_color;
    
    ///or try mixxxitwithitself!
    color=mix(tex0_color,feedback_color,mixxx);
    
    gl_FragColor = color;

}
