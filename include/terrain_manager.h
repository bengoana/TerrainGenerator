/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#ifndef __TERRAIN_MANAGER_H__
#define __TERRAIN_MANAGER_H__ 1

#include "glm/glm.hpp"

#include "Core/node.h"
#include "terrain.h"
#include "terrain_material.h"
#include "grass_material.h"
#include "water_material.h"
#include "Core/texture.h"
#include "water.h"
#include "Core/buffer.h"

const int kAvailableTerrains = 8;
const int kRenderedTerrains = 4;

struct sTerrain {
  bool active;
  Buffer vertices;
  Buffer indices;
};

class TerrainManager {
public:
  TerrainManager();
  ~TerrainManager();

  void Init(Node* parent_node, float* camera_pos);

  void Update();

  int chunk_size_;
  float definition_;
  int seed_;
  float scale_;
  Texture* skybox;
private:
  Texture terrain_diffuse_;
  Texture terrain_sand_;
  Texture terrain_rock_;
  TerrainMaterial main_mat_;
  GrassMaterial grass_mat_;
  WaterMaterial water_mat_;

  Node terrain_nodes_[kRenderedTerrains];
  Node grass_nodes_[kRenderedTerrains];
  Node water_nodes_[kRenderedTerrains];
  sTerrain terrains[kRenderedTerrains];
  sTerrain waters[kRenderedTerrains];
  Terrain terrain;
  Water water;
  Node* parent_node_;
  float* camera_pos_; //is vec3 - use x,z
  glm::ivec2 terrain_pos_;
};

#endif //__TERRAIN_MANAGER_H__