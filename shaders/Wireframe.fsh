//material
uniform bool hasVertexColor;
uniform lowp float alpha;

varying mediump vec4 colorVarying;

void main(){
	mediump vec4 color = vec4(1.0);
	if(hasVertexColor){
		color *= colorVarying;
	}
	color.a *= alpha;
    gl_FragColor = color;
}
