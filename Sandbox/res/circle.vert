varying vec2 i_texCoord;
varying vec4 i_color;

void main() {
	i_texCoord  = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    i_color     = gl_Color;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
