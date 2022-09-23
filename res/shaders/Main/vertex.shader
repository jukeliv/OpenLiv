layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 uPVM;
uniform vec2 uScale = vec2(1.0f, 1.0f);

void main()
{
	gl_Position = uPVM * position * vec4(uScale, 1.0f, 1.0f);
	v_TexCoord = texCoord;
}