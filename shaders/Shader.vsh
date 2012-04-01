attribute highp vec4 position;
attribute mediump vec3 normal;
attribute mediump vec2 texcoord0;
attribute lowp vec4 vertexColor;

//material
uniform bool hasVertexColor;
uniform bool hasTexture;

//transform
uniform highp mat4 wvp;
uniform highp mat4 wvit;

varying lowp vec4 colorVarying;
varying mediump vec2 texCoordVarying;
varying mediump float varDot;

void main(){
    gl_Position = wvp * position;
	vec4 _normal = vec4( normal, 0.0);
	_normal = wvit * _normal;
	vec3 lightDir = normalize( vec3( -3.0,1.0,1.0) - position.xyz );
	_normal.xyz = normalize(_normal.xyz);
	varDot = max(dot( _normal.xyz, lightDir ), 0.0);
	if( hasVertexColor )
		colorVarying = vertexColor;
	texCoordVarying = texcoord0;
}
