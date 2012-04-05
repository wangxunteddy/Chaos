//material
uniform bool hasVertexColor;

varying lowp vec4 colorVarying;

void main(){
	mediump vec4 color = vec4(1.0);
	if(hasVertexColor){
		color *= colorVarying;
	}
    gl_FragColor = color;
}
