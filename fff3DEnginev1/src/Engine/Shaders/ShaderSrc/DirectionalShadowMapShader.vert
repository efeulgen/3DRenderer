
#version 330

layout (location = 0) in vec3 pos;

uniform mat4 model_mat;
uniform mat4 directional_light_transform;

void main()
{
	gl_Position = directional_light_transform * model_mat * vec4(pos, 1.0);
}
