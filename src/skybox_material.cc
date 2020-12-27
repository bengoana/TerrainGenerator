/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#include "skybox_material.h"
#include "glad/gl.h"

SkyboxMaterial::SkyboxMaterial(){
  Program::Program();
  texture_pos_ = -1;
}

SkyboxMaterial::~SkyboxMaterial(){

}

void SkyboxMaterial::EnableProgram(){
  Program::EnableProgram();

  if (texture_pos_ < 0) {
    texture_pos_ = glGetUniformLocation(program_id_, "diffuse");
    if (texture_pos_ < 0) return;
  }

  if (diffuse.initialized_) {
    glActiveTexture(GL_TEXTURE0);
    diffuse.Bind();
    glUniform1i(texture_pos_, 0);
  }
}
