#define TEXTURE_MAX 2

varying lowp vec4 colorVarying;
varying mediump vec2 texCoordVarying[TEXTURE_MAX];

uniform bool hasVertexColor;
uniform bool hasTexture;
uniform lowp int  textureCount;		//max support 2 right now

uniform sampler2D textures[TEXTURE_MAX];

void main(){
	mediump vec4 color = vec4(1.0);
	
	if(hasVertexColor){
		color *= colorVarying;
	}
	
	if(hasTexture){
		int count = textureCount <= TEXTURE_MAX ? textureCount : TEXTURE_MAX;
		for(int i=0;i<textureCount;i++){
			color *= texture2D(textures[i],texCoordVarying[i]);
		}
	}
	
    gl_FragColor = color;
}
