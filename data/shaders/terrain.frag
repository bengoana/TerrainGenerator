#version 330 core

out vec4 FragColor;
in vec2 uv;
in vec3 normal;
in float height;

uniform sampler2D snow;
uniform sampler2D sand;
uniform sampler2D rock;
uniform float min_step;
uniform float max_step;

vec3 light_dir_ = vec3(-0.5,0.0,-0.5);

void main(){
  vec3 light = vec3(1.0f,1.0f,1.0f) * max(dot(normal, -light_dir_),0.0);

  vec4 rock_amount = texture(snow,uv*5.0) * smoothstep(max_step,max_step + 1.5, height);
  vec4 grass_amount = texture(rock,uv*5.0) * ((smoothstep(max_step,max_step + 1.5,height)-1)*-1) * smoothstep(min_step,min_step + 1.5,height);
  vec4 sand_amount = texture(sand,uv*5.0) * ((smoothstep(min_step,min_step + 1.5,height)-1)*-1);

  FragColor = ((rock_amount+sand_amount + grass_amount)) * vec4(light,1.0) * 0.5 + vec4(0.0,0.0,0.0,1.0);
}
