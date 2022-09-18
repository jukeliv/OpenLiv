layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
uniform sampler2D uTexture;

void main()
{
	vec4 texColor = texture(uTexture, v_TexCoord);
	color = texColor;
}