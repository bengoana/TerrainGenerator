/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#ifndef __GRASS_MATERIAL_H__
#define __GRASS_MATERIAL_H__ 1

#include "Core/program.h"
#include "Core/texture.h"

class GrassMaterial : public Program {
public:
  GrassMaterial();
  ~GrassMaterial();

  virtual void EnableProgram() override;

private:
  int time_pos_;
};


#endif //__GRASS_MATERIAL_H__
