/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#include "grass_material.h"
#include "glad/gl.h"

#include "Core/renderer.h"

GrassMaterial::GrassMaterial(){
  Program::Program();
  time_pos_ = -1;
}

GrassMaterial::~GrassMaterial(){

}

void GrassMaterial::EnableProgram(){
  Program::EnableProgram();


  if (time_pos_ < 0) {
    time_pos_ = glGetUniformLocation(program_id_, "time");
  }

  float time = (float)((double)Time::CurrentTime() * 0.005);

  glUniform1f(time_pos_, time);
}
