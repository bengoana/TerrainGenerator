/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#include "Core/texture.h"
#include "glad/gl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(){
  texture_id_ = 0;
  wrap_ = kRepeat;
  filter_ = kLinear;
  initialized_ = false;
}

Texture::~Texture(){

}

static unsigned int TranslateWrapping(Texture::eWrap wrapping) {
  switch (wrapping) {
  case Texture::eWrap::kRepeat: return GL_REPEAT;  break;
  case Texture::eWrap::kClamp: return GL_CLAMP_TO_BORDER; break;
  default: return GL_NONE; break;
  }
}

static unsigned int TranslateFilter(Texture::eFilter filter) {
  switch (filter) {
  case Texture::eFilter::kNearest: return GL_NEAREST; break;
  case Texture::eFilter::kLinear: return GL_LINEAR; break;
  default: return GL_NONE; break;
  }
}

void Texture::LoadTexture(const char* filepath){
  int x, y, n;
  unsigned char* img = stbi_load(filepath, &x, &y, &n, 4);
  if (img == nullptr) return;
  n = 4;
  
  type_ = k2D;


  glGenTextures(1, &texture_id_);

  Bind();


  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TranslateWrapping(wrap_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TranslateWrapping(wrap_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TranslateFilter(filter_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TranslateFilter(filter_));
  float color[4] = { 1.0f,1.0f,1.0f,1.0f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0,
    GL_RGBA, GL_UNSIGNED_BYTE, img);

  stbi_image_free(img);
  initialized_ = true;
}

void Texture::LoadTextureCube(std::vector<const char*> filename){
  type_ = kCube;

  int x, y, n;

  unsigned char* imgs[6];

  imgs[0] = stbi_load(filename[0], &x, &y, &n, 4);
  imgs[1] = stbi_load(filename[1], &x, &y, &n, 4);
  imgs[2] = stbi_load(filename[2], &x, &y, &n, 4);
  imgs[3] = stbi_load(filename[3], &x, &y, &n, 4);
  imgs[4] = stbi_load(filename[4], &x, &y, &n, 4);
  imgs[5] = stbi_load(filename[5], &x, &y, &n, 4);

  for (int i = 0; i < 6; ++i) {
    assert(imgs[i] != nullptr && "Invalid filename");
  }
  n = 4;

  Bind();

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, TranslateFilter(filter_));
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, TranslateFilter(filter_));

  for (int i = 0; i < 6; ++i) {
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, x, y, 0,
      GL_RGBA, GL_UNSIGNED_BYTE, imgs[i]);
  }


  for (int i = 0; i < 6; ++i) {
    stbi_image_free(imgs[i]);
  }
  initialized_ = true;
}

void Texture::LoadFromMemory(void* src, int width, int height){
  type_ = k2D;

  glGenTextures(1, &texture_id_);

  Bind();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TranslateWrapping(wrap_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TranslateWrapping(wrap_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TranslateFilter(filter_));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TranslateFilter(filter_));
  float color[4] = { 1.0f,1.0f,1.0f,1.0f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
    GL_RGBA, GL_FLOAT, src);

  initialized_ = true;
}

void Texture::Bind(){
  switch (type_) {
    case Texture::k2D: glBindTexture(GL_TEXTURE_2D, texture_id_); break;
    case Texture::kCube: glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id_); break;
  }
}

unsigned int Texture::getId(){
  return texture_id_;
}

