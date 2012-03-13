attribute vec4 position;
attribute vec4 vertexColor;

//material
uniform bool hasVertexColor;

//transform
uniform mat4 wvp;

varying vec4 colorVarying;

void main(){
    gl_Position = wvp * position;
	
	if(hasVertexColor)
		colorVarying = vertexColor;
}
