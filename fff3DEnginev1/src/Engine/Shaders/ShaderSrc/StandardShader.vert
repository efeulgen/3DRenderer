
#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;

out vec3 normal;
out vec2 uv;
out vec3 fragPos;
out vec3 viewPos;
out vec4 directionalLightSpacePos; // for shadows

uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;
uniform mat4 directionalLightTransform; // for shadows

void main() {
      gl_Position = projection_mat * view_mat * model_mat * vec4(pos, 1.0);

      normal = normalize(mat3(transpose(inverse(model_mat))) * in_normal);
      uv = in_uv;
      fragPos = vec3(model_mat * vec4(pos, 1.0));
      viewPos = vec3(view_mat * vec4(0, 0, 0, 1));
      directionalLightSpacePos = directionalLightTransform * model_mat * vec4(pos, 1.0);
}
