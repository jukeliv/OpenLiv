
layout(location = 0) out vec4 color;

uniform vec3 uColor;
vec4 fixedColor(float r, float g, float b) {
	return vec4(r * r, g * g, b * b, 1.0);
}
void main()
{
	color = fixedColor(uColor.x, uColor.y, uColor.z);
}