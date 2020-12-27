/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/
#include "..\include\terrain_manager.h"

TerrainManager::TerrainManager(){
  seed_ = 545;
  chunk_size_ = 128;
  definition_ = 0.01;
  scale_ = 0.25f;
}

TerrainManager::~TerrainManager(){

}

void TerrainManager::Init(Node* parent_node, float* camera_pos) {
  camera_pos_ = camera_pos;
  parent_node_ = parent_node;

  main_mat_.LoadShaders("../../../data/shaders/terrain.vert", "../../../data/shaders/terrain.frag");

  terrain_diffuse_.LoadTexture("../../../data/textures/snow.jpg");
  terrain_sand_.LoadTexture("../../../data/textures/sand.jpg");
  terrain_rock_.LoadTexture("../../../data/textures/rock.jpg");

  main_mat_.snow = terrain_diffuse_;
  main_mat_.sand = terrain_sand_;
  main_mat_.rock = terrain_rock_;
  main_mat_.switch_heights[0] = -0.5;
  main_mat_.switch_heights[1] = -4.0;

  grass_mat_.LoadShaders("../../../data/shaders/grass.vert", "../../../data/shaders/grass.frag", "../../../data/shaders/grass.geom");

  water.InitPerlinSeed(8947);
  water.CreateWaterPlane(64, 64, 512, 0.05f);
  water.CreateWaterMaps();

  water_mat_.LoadShaders("../../../data/shaders/water.vert", "../../../data/shaders/water.frag");
  water_mat_.combined_map = water.getCombinedMap();
  water_mat_.combined_map_detail_ = water.getCombinedMap();
  water_mat_.cubemap_ = *skybox;

  terrain_pos_ = {(int)camera_pos_[0] - chunk_size_, (int)camera_pos_[2] - chunk_size_};

  terrain.InitPerlinSeed(seed_);
  for (int i = 0; i < kRenderedTerrains; ++i) {
    terrains[i].active = false;
    terrains[i].vertices.initBuffer(Buffer::EBufferType::vertex, true);
    terrains[i].indices.initBuffer(Buffer::EBufferType::index, true);
    waters[i].active = false;
    waters[i].vertices.initBuffer(Buffer::EBufferType::vertex, true);
    waters[i].indices.initBuffer(Buffer::EBufferType::index, true);
    waters[i].vertices.updateData(water.getVertices(), water.getVertexSize());
    waters[i].indices.updateData(water.getIndices(), water.getIndexSize());
  }

  for (int i = 0; i < kRenderedTerrains; ++i) {
    terrain_nodes_[i].Init(&main_mat_, nullptr, nullptr);
    grass_nodes_[i].Init(&grass_mat_, nullptr, nullptr);
    water_nodes_[i].Init(&water_mat_, nullptr, nullptr);
    grass_nodes_[i].draw_mode_ = 2;
    parent_node_->AddChild(&terrain_nodes_[i]);
    parent_node_->AddChild(&grass_nodes_[i]);
    parent_node_->AddChild(&water_nodes_[i]);

  }
  int count = 0;
  for (int i = 0; i < (kRenderedTerrains / 2); ++i) {
    for (int j = 0; j < (kRenderedTerrains / 2); ++j) {
      //Generate base terrains - under 0 there is a cut in the perlin noise (maybe a bug in the implementation)
      terrain.CreateTerrainNoise(terrain_pos_.x + j * (chunk_size_-1) + 4096,
        terrain_pos_.y + i * (chunk_size_ - 1) + 4096,
        chunk_size_,definition_);
      terrains[count].vertices.updateData(terrain.getVertices(),terrain.getVertexSize());
      terrains[count].indices.updateData(terrain.getIndices(), terrain.getIndexSize());
      terrains[count].active = true;
      terrain_nodes_[i*(kRenderedTerrains/2) + j].setBuffers(&terrains[count].vertices, &terrains[count].indices);
      float pos[3] = {i * (chunk_size_-1) + terrain_pos_.x, 0.0f, j *(chunk_size_-1) + terrain_pos_.y };
      float scale[3] = { scale_,scale_ ,scale_ };
      terrain_nodes_[i * (kRenderedTerrains / 2) + j].setPosition(pos);
      //terrain_nodes_[i * (kRenderedTerrains / 2) + j].setScale(scale);

      grass_nodes_[i * (kRenderedTerrains / 2) + j].setBuffers(&terrains[count].vertices, &terrains[count].indices);
      grass_nodes_[i * (kRenderedTerrains / 2) + j].setPosition(pos);
      float waterscale[3] = {0.25,0.25,0.25};
      
      pos[1] = -2.0;
      water_nodes_[i * (kRenderedTerrains / 2) + j].setBuffers(&waters[count].vertices, &waters[count].indices);
      water_nodes_[i * (kRenderedTerrains / 2) + j].setPosition(pos);
      water_nodes_[i * (kRenderedTerrains / 2) + j].setScale(waterscale);

      count++;
    }
  }
}

void TerrainManager::Update() {
  int rel_cam_pos[2] = { (int)camera_pos_[0] - chunk_size_ , (int)camera_pos_[2] - chunk_size_ };
  int half_chunk = chunk_size_ >> 1;
  bool needs_update = false;
  int oldx = 0;
  int newx = 0;
  int updatey_ = 0;
  if (terrain_pos_.y - rel_cam_pos[0] > half_chunk) {
    needs_update = true;
    terrain_pos_.y -= chunk_size_;
    oldx = 1;
    newx = 0;
  }
  if (rel_cam_pos[0] - terrain_pos_.y > half_chunk) {
    needs_update = true;
    terrain_pos_.y += chunk_size_;
    oldx = 0;
    newx = 1;
  }
  if (terrain_pos_.x - rel_cam_pos[1] > half_chunk) {
    needs_update = true;
    terrain_pos_.x -= chunk_size_;
    updatey_ = 2;
  }
  if (rel_cam_pos[1] - terrain_pos_.x > half_chunk) {
    needs_update = true;
    terrain_pos_.x += chunk_size_;
    updatey_ = 2;
  }

  if (needs_update) {
    int count = 0;
    for (int i = 0; i < (kRenderedTerrains / 2); ++i) {
      for (int j = 0; j < (kRenderedTerrains / 2); ++j) {
        //Generate base terrains - under 0 there is a cut in the perlin noise (maybe a bug in the implementation)
        terrain.CreateTerrainNoise(terrain_pos_.x + j * (chunk_size_ - 1) + 4096,
          terrain_pos_.y + i * (chunk_size_ - 1) + 4096,
          chunk_size_, definition_);
        terrains[count].vertices.updateData(terrain.getVertices(), terrain.getVertexSize());
        terrains[count].indices.updateData(terrain.getIndices(), terrain.getIndexSize());
        terrains[count].active = true;
        terrain_nodes_[i * (kRenderedTerrains / 2) + j].setBuffers(&terrains[count].vertices, &terrains[count].indices);
        float pos[3] = { i * (chunk_size_ - 1) + terrain_pos_.y, 0.0f, j * (chunk_size_ - 1) + terrain_pos_.x };
        float scale[3] = { scale_,scale_ ,scale_ };
        terrain_nodes_[i * (kRenderedTerrains / 2) + j].setPosition(pos);

        grass_nodes_[i * (kRenderedTerrains / 2) + j].setBuffers(&terrains[count].vertices, &terrains[count].indices);
        grass_nodes_[i * (kRenderedTerrains / 2) + j].setPosition(pos);
        float waterscale[3] = { 0.25,0.25,0.25 };

        pos[1] = -2.0;
        water_nodes_[i * (kRenderedTerrains / 2) + j].setPosition(pos);
        water_nodes_[i * (kRenderedTerrains / 2) + j].setScale(waterscale);

        count++;
      }
    }
  }
}





