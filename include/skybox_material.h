/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#ifndef __SKYBOX_MATERIAL_H__
#define __SKYBOX_MATERIAL_H__ 1

#include "Core/program.h"
#include "Core/texture.h"

class SkyboxMaterial : public Program {
public:
  SkyboxMaterial();
  ~SkyboxMaterial();

  virtual void EnableProgram() override;
  
  Texture diffuse;

private:
  int texture_pos_;
};


#endif //__SKYBOX_MATERIAL_H__

