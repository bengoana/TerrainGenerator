/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#ifndef __TERRAIN_MATERIAL_H__
#define __TERRAIN_MATERIAL_H__ 1

#include "Core/program.h"
#include "Core/texture.h"

class TerrainMaterial : public Program {
public:
  TerrainMaterial();
  ~TerrainMaterial();

  virtual void EnableProgram() override;

  Texture snow;
  Texture sand;
  Texture rock;

  float switch_heights[2]; //min,max

private:
  //In future textures and more uniforms
  int snow_pos_;
  int sand_pos_;
  int rock_pos_;
  int height_pos[2];
};


#endif //__TERRAIN_MATERIAL_H__
