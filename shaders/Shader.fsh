//material
uniform bool hasVertexColor;
uniform bool hasTexture;
uniform lowp float alpha;

varying mediump vec4 colorVarying;
//varying mediump vec2 texCoordVarying[TEXTURE_MAX];

void main(){
	mediump vec4 color = vec4(1.0,1.0,1.0,1.0);
	
	if(hasVertexColor){
		color *= colorVarying;
	}
	
	if(hasTexture){
//		int count = textureCount <= TEXTURE_MAX ? textureCount : TEXTURE_MAX;
//		for(int i=0;i<textureCount;i++){
//			color *= texture2D(textures[i],texCoordVarying[i]);
//		}
	}

	color.a *= alpha;
    gl_FragColor = color;
}
