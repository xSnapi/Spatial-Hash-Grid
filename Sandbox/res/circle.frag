#version 330

precision lowp float;

layout(location = 0) out vec4 o_color;

in vec2 i_texCoord;
in vec4 i_color;

void main() {
	vec2 uv = i_texCoord * 2.0 - 1.0;

	float circle = length(uv);	
	
	circle = smoothstep(0.0, 0.095, 1.0 - circle);

    o_color = vec4(i_color.rgb, circle);
}
