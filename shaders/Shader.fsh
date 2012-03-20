#define TEXTURE_MAX 2
//material
uniform bool hasVertexColor;
uniform bool hasTexture;
uniform lowp float alpha;

uniform sampler2D diffuseTexture;

varying mediump vec4 colorVarying;
varying mediump vec2 texCoordVarying[TEXTURE_MAX];

void main(){
	mediump vec4 color = vec4(1.0,1.0,1.0,1.0);
	
	if( hasVertexColor ){
		color *= colorVarying;
	}
	
	if( hasTexture ){
		color *= texture2D( diffuseTexture, texCoordVarying[0].st, 0.0 );
	}

	color.a *= alpha;
    gl_FragColor = color;
}
