layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
uniform sampler2D uTexture;
uniform vec4 uValue;
uniform float uAlpha;
void main()
{
	vec4 texColor = texture(uTexture, v_TexCoord);
	color = texColor * uValue * vec4(1.0f, 1.0f, 1.0f, uAlpha);
}