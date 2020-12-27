/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#include "water.h"

Water::Water(){
  side_size_ = 0;
  seedpos_ = {0,0};
}

Water::~Water(){
}

const int kSampleSize = 512;

static struct BaseNoiseDataWater {
  int table[kSampleSize * 2];
  bool created = false;
} NoiseData;

static const float MAX_RAND = 6.0f;

static float Rand() {
  return rand() / (RAND_MAX + 1.0f);
}

static float RandRange(float min, float max, unsigned int seed) {
  srand(seed);
  return min + (max - min) * Rand();
}

static unsigned int FloatToRGBA(float r, float g, float b, float a) {
  unsigned int out_color_ = 0;
  
  if (r > 1.0f) r = 1.0f;
  if (g > 1.0f) g = 1.0f;
  if (b > 1.0f) b = 1.0f;
  if (a > 1.0f) a = 1.0f;

  out_color_ |= ((int)(r * 255.0f) << 24);
  out_color_ |= ((int)(g * 255.0f) << 16);
  out_color_ |= ((int)(b * 255.0f) << 8);
  out_color_ |= ((int)(a * 255.0f));

  return out_color_;
}

static glm::vec2 GetConstantVector(int v) {
  //v is the value from the permutation table
  int h = v & 3;
  if (h == 0)
    return glm::vec2(1.0, 1.0);
  else if (h == 1)
    return glm::vec2(-1.0, 1.0);
  else if (h == 2)
    return glm::vec2(-1.0, -1.0);
  else
    return glm::vec2(1.0, -1.0);
}

static float Fade(float t) {
  return ((6.0f * t - 15.0f) * t + 10.0f) * t * t * t;
}

static float Lerp(float t, float a1, float a2) {
  return a1 + t * (a2 - a1);
}

float Water::getNoise2D(float x, float y){
  //Suppose x, y and z are the float input
  int X = (int)floor(x) & 255;
  int Y = (int)floor(y) & 255;
  float xf = x - floor(x);
  float yf = y - floor(y);

  glm::vec2 topRight = glm::vec2(xf - 1.0, yf - 1.0);
  glm::vec2 topLeft = glm::vec2(xf, yf - 1.0);
  glm::vec2 bottomRight = glm::vec2(xf - 1.0, yf);
  glm::vec2 bottomLeft = glm::vec2(xf, yf);


  int valueTopRight = NoiseData.table[(NoiseData.table[(X + 1)] + Y + 1)];
  int valueTopLeft = NoiseData.table[(NoiseData.table[(X)] + Y + 1)];
  int valueBottomRight = NoiseData.table[(NoiseData.table[(X + 1)] + Y)];
  int valueBottomLeft = NoiseData.table[(NoiseData.table[(X)] + Y)];

  float dotTopRight = glm::dot(topRight, GetConstantVector(valueTopRight));
  float dotTopLeft = glm::dot(topLeft, GetConstantVector(valueTopLeft));
  float dotBottomRight = glm::dot(bottomRight, GetConstantVector(valueBottomRight));
  float dotBottomLeft = glm::dot(bottomLeft, GetConstantVector(valueBottomLeft));


  float u = Fade(xf);
  float v = Fade(yf);
  float result = Lerp(u,
    Lerp(v, dotBottomLeft, dotTopLeft),
    Lerp(v, dotBottomRight, dotTopRight)
  );

  return result;
}

float Water::getHeight2D(float basex, float basey, float x, float y, float definition){
  float total_height_ = getNoise2D((basex + x) * definition, (basey + y) * definition);

  return total_height_;
}

void Water::CreateWaterPlane(int x, int y, int side_size, float definition){

  side_size_ = side_size;
  numStripsRequired = side_size_ - 1;
  verticesPerStrip = 2 * side_size_;

  vertices_.alloc(side_size * side_size);
  indices_.alloc(numStripsRequired * numStripsRequired * 6);

  seedpos_ = {x,y};
  definition_ = definition;
  // Intialise vertex array
  int i = 0;

  for (int z = 0; z < side_size_; z++){
    for (int j = 0; j < side_size_; j++){
      float uv_multiplier = (1.0f / (float)side_size_);

      vertices_[i] = { { (float)j, 0.0f, (float)z}, {0.0f,1.0f,0.0f},{x * uv_multiplier + z * uv_multiplier,y * uv_multiplier + j * uv_multiplier } };
      i++;
    }
  }

  // Now build the index data 
  i = 0;
  for (int z = 0; z < side_size_ - 1; z++) {
    for (int x = 0; x < side_size - 1; x++) {
      indices_[i] = z * side_size_ + x;
      indices_[i + 1] = (z + 1) * side_size_ + (x + 1);
      indices_[i + 2] = z * side_size_ + (x + 1);

      indices_[i + 3] = (z + 1) * side_size_ + x;
      indices_[i + 4] = (z + 1) * side_size_ + (x + 1);
      indices_[i + 5] = z * side_size_ + (x);
      i += 6;
    }
  }

}

void Water::CreateWaterMaps(){
  scoped_array<float> height_data_;
  int map_size = 4 * side_size_;
  height_data_.alloc(map_size * map_size);

  scoped_array<float> combined_map;

  combined_map.alloc(map_size * map_size * 4);

  /*for (int x = 0; x < map_size * map_size; x++) {
    height_data_[x] = 0.0f;
  }*/

  int k = 0;
  for (int i = 0; i < map_size; ++i) {
    for (int j = 0; j < map_size; j++) {
      height_data_[i * map_size + j] = getHeight2D(seedpos_.x, seedpos_.y, j, i, definition_);
    
      float hL = getHeight2D(seedpos_.x, seedpos_.y, j - 1, i, definition_);
      float hR = getHeight2D(seedpos_.x, seedpos_.y, j + 1, i, definition_);
      float hD = getHeight2D(seedpos_.x, seedpos_.y, j, i - 1, definition_);
      float hU = getHeight2D(seedpos_.x, seedpos_.y, j, i + 1, definition_);

      glm::vec3 normal = { 0.0f,0.0f,0.0f };
      normal.x = hL - hR;
      normal.y = hD - hU;
      normal.z = 1.0f;

      normal = glm::normalize(normal);

      combined_map[k] = normal.x;
      combined_map[k + 1] = normal.y;
      combined_map[k + 2] = normal.z;
      combined_map[k + 3] = height_data_[i * map_size + j];

      k += 4;
    }
  }

  combined_map_.LoadFromMemory(combined_map.get(), map_size, map_size);

  k = 0;
  for (int i = 0; i < map_size; ++i) {
    for (int j = 0; j < map_size; j++) {
      //multiple passes for Fractal Brownian Motion

      height_data_[i * side_size_ + j] = getHeight2D(seedpos_.x, seedpos_.y, j, i, definition_ * 0.1f);
    
      float hL = getHeight2D(seedpos_.x, seedpos_.y, j - 1, i, definition_ * 0.1f);
      float hR = getHeight2D(seedpos_.x, seedpos_.y, j + 1, i, definition_ * 0.1f);
      float hD = getHeight2D(seedpos_.x, seedpos_.y, j, i - 1, definition_ * 0.1f);
      float hU = getHeight2D(seedpos_.x, seedpos_.y, j, i + 1, definition_ * 0.1f);

      glm::vec3 normal = { 0.0f,0.0f,0.0f };
      normal.x = hL - hR;
      normal.y = hD - hU;
      normal.z = 2.0f;

      normal = glm::normalize(normal);

      combined_map[k] = normal.x;
      combined_map[k + 1] = normal.y;
      combined_map[k + 2] = normal.z;
      combined_map[k + 3] = height_data_[i * map_size + j];

      k += 4;
    }
  }
  combined_map_detail_.LoadFromMemory(combined_map.get(), map_size, map_size);
}

void Water::InitPerlinSeed(int seed){
  srand(seed);
  if (!NoiseData.created) {
    for (int i = 0; i < kSampleSize; ++i) {
      NoiseData.table[i] = i;
    }
    
    //shuffle
    for (int i = kSampleSize - 1; i > 1; i--) {
      int index = rand() % (i - 1);
      int temp = NoiseData.table[i];

      NoiseData.table[i] = NoiseData.table[index];
      NoiseData.table[index] = temp;
    }

    for (int i = kSampleSize; i < kSampleSize * 2; ++i) {
      NoiseData.table[i] = NoiseData.table[kSampleSize - i - 1];
    }
    NoiseData.created = true;
  }
}

unsigned int Water::getVertexSize(){
  return vertices_.sizeInBytes();
}

unsigned int Water::getIndexSize(){
  return indices_.sizeInBytes();
}

sVertex* Water::getVertices(){

  return vertices_.get();
}

unsigned int* Water::getIndices(){
  return indices_.get();
}

Texture Water::getCombinedMap()
{
  return combined_map_;
}

Texture Water::getCombinedMapDetail(){
  return combined_map_detail_;
}

