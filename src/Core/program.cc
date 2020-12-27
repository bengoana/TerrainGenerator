/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#include "Core/program.h"
#include <stdio.h>
#include "glad/gl.h"
#include "gl.h"

Program::Program(){
  generated_ = false;
  program_id_ = 0;
  base_uniforms[0] = 0;
  base_uniforms[1] = 0;
  base_uniforms[2] = 0;
}

Program::~Program(){
  if (generated_) glDeleteProgram(program_id_);
}

bool Program::LoadShaders(const char* vertex, const char* fragment){
  FILE* f;
  //VERTEX
  fopen_s(&f, vertex, "rb");
  if (NULL == f) {
    printf("Error opening file\n");
    return false;
  }
  fseek(f, 0, SEEK_END);
  int vertex_size = ftell(f);
  scoped_array<char> vertexarray;
  vertexarray.alloc(vertex_size + 1);
  fseek(f, 0, SEEK_SET);
  fread(vertexarray.get(), sizeof(char), vertex_size + 1, f);
  vertexarray[vertex_size] = '\0';
  char* vertexdata = vertexarray.get();
  unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertexdata, &vertex_size);

  fclose(f);
  
  //VERTEX
  fopen_s(&f, fragment, "rb");
  if (NULL == f) {
    printf("Error opening file\n");
    return false;
  }
  fseek(f, 0, SEEK_END);
  int fragment_size = ftell(f);
  scoped_array<char> fragmentarray;
  fragmentarray.alloc(fragment_size + 1);
  fseek(f, 0, SEEK_SET);
  fread(fragmentarray.get(), sizeof(char), fragment_size + 1, f);
  fragmentarray[fragment_size] = '\0';
  char* fragmentdata = fragmentarray.get();
  unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragmentdata, &fragment_size);

  fclose(f);

  glCompileShader(vertex_shader);

  int success;
  char infoLog[512];
  memset(infoLog,0,512);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
    printf("ERROR shader: %s \n", infoLog);
    return false;
  }

  glCompileShader(fragment_shader);

  memset(infoLog, 0, 512);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
    printf("ERROR shader: %s \n", infoLog);
    return false;
  }

  program_id_ = glCreateProgram();
  glAttachShader(program_id_, vertex_shader);
  glAttachShader(program_id_,fragment_shader);

  glLinkProgram(program_id_);

  glGetProgramiv(program_id_, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program_id_, 512, nullptr, infoLog);
    printf("ERROR program: %s \n", infoLog);
  }


  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  generated_ = true;

  glUseProgram(program_id_);
  base_uniforms[0] = glGetUniformLocation(program_id_, "m_model");
  base_uniforms[1] = glGetUniformLocation(program_id_, "m_view");
  base_uniforms[2] = glGetUniformLocation(program_id_, "m_proj");
  
  printf("end program creation: %d\n", glGetError());

  return true;
}

bool Program::LoadShaders(const char* vertex, const char* fragment, const char* geometry){
  FILE* f;
  //VERTEX
  fopen_s(&f, vertex, "rb");
  if (NULL == f) {
    printf("Error opening file\n");
    return false;
  }
  fseek(f, 0, SEEK_END);
  int vertex_size = ftell(f);
  scoped_array<char> vertexarray;
  vertexarray.alloc(vertex_size + 1);
  fseek(f, 0, SEEK_SET);
  fread(vertexarray.get(), sizeof(char), vertex_size + 1, f);
  vertexarray[vertex_size] = '\0';
  char* vertexdata = vertexarray.get();
  unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertexdata, &vertex_size);

  fclose(f);

  //VERTEX
  fopen_s(&f, fragment, "rb");
  if (NULL == f) {
    printf("Error opening file\n");
    return false;
  }
  fseek(f, 0, SEEK_END);
  int fragment_size = ftell(f);
  scoped_array<char> fragmentarray;
  fragmentarray.alloc(fragment_size + 1);
  fseek(f, 0, SEEK_SET);
  fread(fragmentarray.get(), sizeof(char), fragment_size + 1, f);
  fragmentarray[fragment_size] = '\0';
  char* fragmentdata = fragmentarray.get();
  unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragmentdata, &fragment_size);

  fclose(f);

  //GEOMETRY
  fopen_s(&f, geometry, "rb");
  if (NULL == f) {
    printf("Error opening file\n");
    return false;
  }
  fseek(f, 0, SEEK_END);
  int geometry_size = ftell(f);
  scoped_array<char> geometryarray;
  geometryarray.alloc(geometry_size + 1);
  fseek(f, 0, SEEK_SET);
  fread(geometryarray.get(), sizeof(char), geometry_size + 1, f);
  geometryarray[geometry_size] = '\0';
  char* geometrydata = geometryarray.get();
  unsigned int geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
  glShaderSource(geometry_shader, 1, &geometrydata, &geometry_size);

  fclose(f);

  glCompileShader(vertex_shader);

  int success;
  char infoLog[512];
  memset(infoLog, 0, 512);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
    printf("ERROR vertex shader: %s \n", infoLog);
    return false;
  }

  glCompileShader(fragment_shader);

  memset(infoLog, 0, 512);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
    printf("ERROR fragment shader: %s \n", infoLog);
    return false;
  }

  glCompileShader(geometry_shader);

  memset(infoLog, 0, 512);
  glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(geometry_shader, 512, nullptr, infoLog);
    printf("ERROR geometry shader: %s \n", infoLog);
    return false;
  }

  program_id_ = glCreateProgram();
  glAttachShader(program_id_, vertex_shader);
  glAttachShader(program_id_, fragment_shader);
  glAttachShader(program_id_, geometry_shader);

  glLinkProgram(program_id_);

  glGetProgramiv(program_id_, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program_id_, 512, nullptr, infoLog);
    printf("ERROR program: %s \n", infoLog);
  }


  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  glDeleteShader(geometry_shader);
  generated_ = true;

  glUseProgram(program_id_);
  base_uniforms[0] = glGetUniformLocation(program_id_, "m_model");
  base_uniforms[1] = glGetUniformLocation(program_id_, "m_view");
  base_uniforms[2] = glGetUniformLocation(program_id_, "m_proj");

  printf("end program creation: %d\n", glGetError());

  return true;
}

void Program::EnableProgram(){

  glUseProgram(program_id_);

  if(base_uniforms[0]>=0)
    glUniformMatrix4fv(base_uniforms[0], 1, false, &model_[0][0]);
  if (base_uniforms[1] >= 0)
    glUniformMatrix4fv(base_uniforms[1], 1, false, &view_[0][0]);
  if (base_uniforms[2] >= 0)
    glUniformMatrix4fv(base_uniforms[2], 1, false, &proj_[0][0]);


}

void Program::SetModel(glm::mat4 model){
  model_ = model;
}

void Program::SetCamera(glm::mat4 view, glm::mat4 projection){
  view_ = view;
  proj_ = projection;
}

unsigned int Program::get_id(){
  return program_id_;
}
