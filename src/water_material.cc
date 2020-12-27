/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/
#include "water_material.h"
#include "glad/gl.h"
#include "Core/renderer.h"

WaterMaterial::WaterMaterial(){
  map_pos_ = -1;
  map_pos_detail_ = -1;
  time_pos_ = -1;
  cam_pos_ = -1;
  cubemap_pos_ = -1;
}

WaterMaterial::~WaterMaterial(){

}

void WaterMaterial::EnableProgram(){
  Program::EnableProgram();

  if (map_pos_ < 0) {
    map_pos_ = glGetUniformLocation(program_id_, "combined_map");
  }
  if (map_pos_detail_ < 0) {
    map_pos_detail_ = glGetUniformLocation(program_id_, "combined_map_detail");
  }
  if (time_pos_ < 0) {
    time_pos_ = glGetUniformLocation(program_id_, "time");
  }
  if (cam_pos_ < 0) {
    cam_pos_ = glGetUniformLocation(program_id_, "cam_pos");
  }
  if (cubemap_pos_< 0) {
    cubemap_pos_ = glGetUniformLocation(program_id_, "sky");
  }



  if (combined_map.initialized_) {
    glActiveTexture(GL_TEXTURE0);
    combined_map.Bind();
    glUniform1i(map_pos_, 0);
  }
  if (combined_map_detail_.initialized_) {
    glActiveTexture(GL_TEXTURE1);
    combined_map_detail_.Bind();
    glUniform1i(map_pos_detail_, 1);
  }
  if (cubemap_.initialized_) {
    glActiveTexture(GL_TEXTURE2);
    cubemap_.Bind();
    glUniform1i(cubemap_pos_, 2);
  }

  float time = (float)((double)Time::CurrentTime() * 0.001);

  glUniform1f(time_pos_, time);

  glm::mat4 inverse = glm::inverse(view_);

  float cam_pos[] = {inverse[3][0],inverse[3][1] ,inverse[3][2] };

  glUniform3fv(cam_pos_, 1, cam_pos);
}
