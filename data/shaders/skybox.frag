#version 330 core

out vec4 FragColor;
in vec3 uv;

uniform samplerCube diffuse;

void main(){
  FragColor = texture(diffuse, uv);
}
