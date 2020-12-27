#version 330 core

out vec4 FragColor;

uniform sampler2D combined_map;
uniform sampler2D combined_map_detail;
uniform samplerCube sky;
uniform float time;
uniform vec3 cam_pos;

in vec2 uv;
in vec3 w_pos;
in vec3 normal_;

vec3 light_dir_ = vec3(-0.8,-0.3,-0.8);
void main(){
  light_dir_ = normalize(light_dir_);
  vec3 normal = texture(combined_map,uv + time*0.01).xyz;
  normal += texture(combined_map_detail,vec2(uv.x,uv.y - time*0.01)).xyz;
  normal = normalize(normal);

  vec3 light = vec3(1.0f,1.0f,1.0f)  * max(dot(normal, -light_dir_),0.0) * 0.1f;

  vec3 reflectdir = reflect(-light_dir_,normal.xzy);
  light += max(0,pow(dot(normalize(w_pos - cam_pos),reflectdir),256)) * 0.6;

  FragColor = vec4((texture(sky,normal.xzy) * 0.8 + vec4(light,1.0)).xyz,0.8f);
}
