#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_proj;


out vec3 uv;

void main(){

  uv = aPos;
  vec4 pos = m_proj * m_view * vec4(aPos, 0.0);
  gl_Position = pos.xyww;

}





