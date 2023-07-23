#version 330

in vec3 normal;
in vec2 uv;
in vec3 fragPos;
in vec3 viewPos;

out vec4 color;
uniform sampler2D tex;

// ********************************************************************************************************************************************
// *************** material properties ********************************************************************************************************

struct Material{
      float metallic;
      float roughness;
      float specular;
};

// ********************************************************************************************************************************************
// *************** lights *********************************************************************************************************************

const int MAX_POINT_LIGHTS = 20;
const int MAX_SPOT_LIGHTS = 20;
// const int MAX_AREA_LIGHTS = 20; TODO : implement later

struct DirectionalLight{
      vec3 DL_direction;
      vec3 DL_color;
      float DL_intensity;
      float ambientStrength;
};

struct PointLight{
      vec3 PL_position;
      vec3 PL_color;
      vec3 PL_intensity; // TODO : implement
};

struct SpotLight{
      vec3 SL_position;
      vec3 SL_color;
      vec3 SL_intensity; // TODO : implement
      vec3 SL_direction;
      float SL_edge;
};

// struct AreaLight{}; TODO : implement later

uniform Material mat;

uniform DirectionalLight directionalLight;

uniform int pointLightCount;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform int spotLightCount;
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

// uniform int areaLightCount; TODO : implement
// uniform AreaLight areaLights[MAX_AREA_LIGHTS]; TODO : implement


// ********************************************************************************************************************************************

vec3 CalculateDirectionalLight()
{
      // ambient term of directional light
      vec3 ambient = directionalLight.DL_color * directionalLight.ambientStrength;

      // diffuse term of directional light
      float diffuseFactor = max(dot(normal, directionalLight.DL_direction), 0.0);
      vec3 diffuse = diffuseFactor * directionalLight.DL_color * directionalLight.DL_intensity;

      return diffuse + ambient;
}

vec3 CalculatePointLights()
{
      vec3 outColor = vec3(0.0, 0.0, 0.0);
      for (int i = 0; i < pointLightCount; i++)
      {
            // diffuse term of point  light
            vec3 lightDir = normalize(fragPos - pointLights[i].PL_position);
            float diffuseFactor = max(dot(normal, lightDir), 0.0);
            vec3 diffuse = diffuseFactor * pointLights[i].PL_color;

            // specular term of point light
            vec3  specular = vec3(0, 0, 0);
            if (diffuseFactor > 0.0) 
            {
                  vec3 viewVector = normalize(viewPos - fragPos);
                  vec3 reflectionVector = normalize(reflect(lightDir, normal));
                  float specularFactor = pow(dot(viewVector, reflectionVector), mat.roughness);
                  specular = specularFactor * mat.specular * pointLights[i].PL_color;
            }
            outColor += (diffuse + specular);
      }
      return outColor;
}

vec3 CalculateSpotLights()
{
      vec3 outColor = vec3(0.0, 0.0, 0.0);
      for (int i = 0; i < spotLightCount; i++)
      {
            vec3 diffuse = vec3(0, 0, 0);
            vec3  specular = vec3(0, 0, 0);
            vec3 lightDir = normalize(fragPos - spotLights[i].SL_position);
            float spotEffectArea = dot(lightDir, spotLights[i].SL_direction);
            if (spotEffectArea > spotLights[i].SL_edge)
            {
                  // diffuse term of spot  light
                  float diffuseFactor = max(dot(normal, lightDir), 0.0);
                  diffuse = diffuseFactor * spotLights[i].SL_color;
                  
                  // specular term of spot light
                  if (diffuseFactor > 0.0) 
                  {
                        vec3 viewVector = normalize(viewPos - fragPos);
                        vec3 reflectionVector = normalize(reflect(lightDir, normal));
                        float specularFactor = pow(dot(viewVector, reflectionVector), mat.roughness);
                        specular = specularFactor * mat.specular * spotLights[i].SL_color;
                  }
            }
            outColor += (diffuse + specular);
      }
      return outColor;
}

// vec3 CalculateAreaLights(); TODO : implement

// ********************************************************************************************************************************************
// *************** main ***********************************************************************************************************************

void main() {
      vec4 mainTexture = texture(tex, uv);
      
      color = mainTexture * vec4(CalculateDirectionalLight() + CalculatePointLights(), 1.0);
}