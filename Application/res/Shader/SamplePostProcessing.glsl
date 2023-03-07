#Vertex
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texcoord;

out vec2 uv;

void main()
{
	uv = texcoord;
	gl_Position = vec4(position.x, position.y, 0.0, 1.0);
};

#Fragment
in vec2 uv;
uniform sampler2D MainTexture;
out vec4 color;
void main()
{
	color = texture(MainTexture, uv);
}