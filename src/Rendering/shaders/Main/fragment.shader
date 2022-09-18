layout(location = 0) out vec4 color;

uniform vec3 uColor;
vec4 fixedColor(vec3 c) {
	return vec4(c.r * c.r, c.g * c.g, c.b * c.b, 1.0);
}

void main()
{
	color = fixedColor(uColor.xyz);
}