/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#ifndef __WATER_MATERIAL_H__
#define __WATER_MATERIAL_H__ 1

#include "Core/program.h"
#include "Core/texture.h"

class WaterMaterial : public Program {
public:
  WaterMaterial();
  ~WaterMaterial();

  virtual void EnableProgram() override;

  Texture combined_map;
  Texture combined_map_detail_;
  Texture cubemap_;

private:
  int map_pos_;
  int map_pos_detail_;
  int cubemap_pos_;
  int time_pos_;
  int cam_pos_;
};

#endif //__WATER_MATERIAL_H__

