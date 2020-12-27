/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#include "terrain_material.h"
#include "glad/gl.h"
TerrainMaterial::TerrainMaterial(){
  Program::Program();
  snow_pos_ = -1;
  sand_pos_ = -1;
  rock_pos_ = -1;
  height_pos[0] = -1;
  height_pos[1] = -1;
}

TerrainMaterial::~TerrainMaterial(){

}

void TerrainMaterial::EnableProgram(){
  Program::EnableProgram();
  
  if (snow_pos_ < 0) {
    snow_pos_ = glGetUniformLocation(program_id_, "snow");
  }
  if (sand_pos_ < 0) {
    sand_pos_ = glGetUniformLocation(program_id_, "sand");
  }
  if (height_pos[0] < 0) {
    height_pos[0] = glGetUniformLocation(program_id_, "min_step");
  }
  if (height_pos[1] < 0) {
    height_pos[1] = glGetUniformLocation(program_id_, "max_step");
  }

  if (snow.initialized_) {
    glActiveTexture(GL_TEXTURE0);
    snow.Bind();
    glUniform1i(snow_pos_, 0);
  }
  if (sand.initialized_) {
    glActiveTexture(GL_TEXTURE1);
    sand.Bind();
    glUniform1i(sand_pos_, 1);
  }

  glUniform1f(height_pos[0], switch_heights[0]);
  glUniform1f(height_pos[1],switch_heights[1]);

  //if (rock.initialized_) {
  //  glActiveTexture(GL_TEXTURE2);
  //  rock.Bind();
  //  glUniform1i(rock_pos_, 2);
  //}
}
