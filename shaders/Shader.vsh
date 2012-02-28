#define TEXTURE_MAX 2
attribute vec4 position;
attribute vec4 vertexColor;
attribute mat4 texCoord;

varying vec4 colorVarying;
varying vec2 texCoordVarying[TEXTURE_MAX];

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 wvp;

uniform bool hasVertexColor;	
uniform bool hasTexture;		
uniform lowp int textureCount;		//max support 2 right now

uniform mediump float translate;

void main(){
    gl_Position = position;// * wvp;
	gl_Position.y += cos(translate);
	
	if(hasVertexColor)
	    colorVarying = vertexColor;
	
	if(hasTexture){
		for(int i=0;i<textureCount;i++){
			texCoordVarying[i] = vec2(texCoord[i][0],texCoord[i][1]);
		}
	}
}
