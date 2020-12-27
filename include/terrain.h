/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#ifndef __TERRAIN_H__
#define __TERRAIN_H__ 1

#include "scoped_array.h"
#include "Core/buffer.h"

#include "glm/glm.hpp"

class Terrain {
public:
  Terrain();
  ~Terrain();

  void CreateTerrain(int side_size, glm::u32vec2 seedpos, unsigned int base_seed);
  void CreateTerrainNoise(int x, int y, int size, float definition);

  void InitPerlinSeed(int seed);

  unsigned int getVertexSize();
  unsigned int getIndexSize();
  sVertex* getVertices();
  unsigned int* getIndices();

  int octaves_;
  float amplitude_increase_;
  float freq_increase_;
  float base_amplitude_;
  float base_frequency_;
private:
  scoped_array<sVertex> vertices_;
  scoped_array<unsigned int> indices_;
  int side_size_;

  int numStripsRequired;
  int verticesPerStrip;
  glm::u32vec2 seedpos_;


  void DiamondStep(float* heightmap, int x, int y, int step_size, float RAND, unsigned int currentseedpos);
  void SquareStep(float* heightmap, int x, int y, int step_size, float RAND, unsigned int currentseedpos);

  float getNoise2D(float x, float y);

  float getHeight2D(float basex, float basey, float x, float y, float definition);
};


#endif //__TERRAIN_H__

