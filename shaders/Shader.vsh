attribute vec4 position;
attribute vec3 normal;
attribute vec2 texcoord0;
attribute vec4 vertexColor;

//material
uniform bool hasVertexColor;
uniform bool hasTexture;

//transform
uniform mat4 wvp;

varying vec4 colorVarying;

void main(){
    gl_Position = wvp * position;
	
	vec4 c = vec4(normal,1.0);
	c = ( c + vec4(1.0) )/vec4(2.0);
	if(hasVertexColor)
		colorVarying = c;//vertexColor;
}
