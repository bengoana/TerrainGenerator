/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#ifndef __WATER_H__
#define __WATER_H__ 1

#include "scoped_array.h"
#include "Core/buffer.h"

#include "glm/glm.hpp"

#include "Core/texture.h"

class Water {
public:
  Water();
  ~Water();

  void CreateWaterPlane(int x, int y, int size, float definition);

  void CreateWaterMaps();


  void InitPerlinSeed(int seed);

  unsigned int getVertexSize();
  unsigned int getIndexSize();
  sVertex* getVertices();
  unsigned int* getIndices();

  Texture getCombinedMap();
  Texture getCombinedMapDetail();

private:
  scoped_array<sVertex> vertices_;
  scoped_array<unsigned int> indices_;
  int side_size_;

  Texture combined_map_;
  Texture combined_map_detail_;

  int numStripsRequired;
  int verticesPerStrip;
  glm::vec2 seedpos_;
  float definition_;

  float getNoise2D(float x, float y);

  float getHeight2D(float basex, float basey, float x, float y, float definition);
};


#endif //__TERRAIN_H__

