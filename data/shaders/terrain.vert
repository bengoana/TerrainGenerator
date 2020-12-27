#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_proj;

out vec2 uv;
out vec3 normal;
out float height;

void main(){
  gl_Position = (m_proj * m_view * m_model) * vec4(aPos,1.0);
  uv = aUV;
  normal = (m_model * vec4(aNormal,0.0)).xyz;
  height = (m_model * vec4(aPos,1.0)).y;
}






