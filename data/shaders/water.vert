#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_proj;
uniform sampler2D combined_map;
uniform sampler2D combined_map_detail;
uniform float time;

out vec2 uv;
out vec3 w_pos;
out vec3 normal_;

void main(){
  vec4 world_pos = m_model * vec4(aPos,1.0);
  world_pos.y += texture(combined_map,aUV + time*0.01).w * 0.1;
  world_pos.y += texture(combined_map_detail,vec2(aUV.x,aUV.y - time*0.01)).w*0.1;

  w_pos = world_pos.xyz;
  uv = aUV;
  normal_ = aNormal;
  gl_Position = (m_proj * m_view) *  world_pos;
  

}






