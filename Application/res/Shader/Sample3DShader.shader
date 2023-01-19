#Vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

out vec2 uv;

void main()
{
	uv = texcoord;
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
};

#Fragment
#version 330 core
in vec2 uv;

uniform sampler2D MainTexture;
uniform sampler2D Overlap;

out vec4 color;
void main()
{
	vec4 base = texture(MainTexture, uv);
	vec4 over = texture(Overlap, uv);
	color = mix(base, over, 0.2);
}