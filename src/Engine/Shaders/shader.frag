#version 330

in vec3 normal;
in vec2 uv;
in vec3 fragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform sampler2D tex;

out vec4 color;

void main() {
      vec4 mainTexture = texture(tex, uv);
      
      float ambientStrength = 0.2;
      vec3 ambient = lightColor * ambientStrength;
      
      // diffuse term
      vec3 lightDir = normalize(lightPos - fragPos);
      float diffuseFactor = max(dot(normal, lightDir), 0.0);
      vec3 diffuse = diffuseFactor * lightColor;

      color = mainTexture * vec4(ambient + diffuse, 1.0);
}