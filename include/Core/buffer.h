/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/


#ifndef __BUFFER_H__
#define __BUFFER_H__ 1

#include "scoped_array.h"
#include "glm/glm.hpp"

struct sVertex {
  glm::vec3 pos;
  glm::vec3 normal;
  glm::vec2 uv;
};

class Buffer {
public:
  enum EBufferType {
    vertex,
    index
  };


  Buffer();
  ~Buffer();
  //Use only on startup since it takes long
  bool LoadObj(const char* filepath);

  bool initBuffer(EBufferType type, bool updatable);
  bool updateData(const void* src, unsigned int size);

  unsigned int getSize() { return size_; }

  void BindBuffer();

private:
  unsigned int buffer_id_;
  bool generated_;
  EBufferType type_;
  bool updatable_;
  unsigned int size_;
};


#endif //__BUFFER_H__