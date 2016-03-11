uniform sampler2DRect tex0;     // base image to render
uniform sampler2DRect gradient; // color gradient to apply
uniform float gradientWidth;    // gradient width

void main (void){
	
	// Original pixel color
	vec2 pos = gl_TexCoord[0].st;
	vec4 src = texture2DRect(tex0, pos);
	
	// Convert color to grayscale
	float l = 0.2989 * src.r + 0.5870 * src.g + 0.1140 * src.b;
	
	// Pick color in gradient, according to grayscale value
	vec4 map = texture2DRect(gradient, vec2(l * gradientWidth, 5.0) );
	
	// Return this color
	// Keep alpha value from original pixel 
	gl_FragColor = vec4( map.rgb, src.a );
}
