attribute highp vec4 position;
attribute lowp vec4 vertexColor;

//material
uniform bool hasVertexColor;

//transform
uniform highp mat4 wvp;

varying lowp vec4 colorVarying;

void main(){
    gl_Position = wvp * position;
	
	if(hasVertexColor)
		colorVarying = vertexColor;
}
