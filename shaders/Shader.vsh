#define TEXTURE_MAX 2
attribute vec4 position;
attribute vec4 vertexColor;
attribute mat4 texCoord;

//material
uniform bool hasVertexColor;
uniform bool hasTexture;
uniform lowp int  textureCount;		//max support 2 right now

//transform
uniform mat4 wvp;

varying vec4 colorVarying;
varying vec2 texCoordVarying[TEXTURE_MAX];


void main(){
    gl_Position = wvp * position;
	
	if(hasVertexColor)
	    colorVarying = vertexColor;
	
	if(hasTexture){
		for(int i=0;i<textureCount;i++){
			texCoordVarying[i] = vec2(texCoord[i][0],texCoord[i][1]);
		}
	}
}
