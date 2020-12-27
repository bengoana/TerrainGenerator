/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#include "Core/buffer.h"
#include "glad/gl.h"

Buffer::Buffer(){
  buffer_id_ = 0;
  generated_ = false;
  size_ = 0;
}

Buffer::~Buffer(){

}

bool Buffer::LoadObj(const char* filepath){
  //Later
  return false;
}

bool Buffer::initBuffer(EBufferType type, bool updatable){
  if (!generated_) {
    glGenBuffers(1, &buffer_id_);
  }

  type_ = type;
  updatable_ = updatable;
  return true;
}

bool Buffer::updateData(const void* src, unsigned int size){
  
  int value = 0;
  switch (type_) {
  case vertex:
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &value);
    if (value == 0) {
      if(updatable_)
        glBufferData(GL_ARRAY_BUFFER, size, src, GL_DYNAMIC_DRAW);
      else
        glBufferData(GL_ARRAY_BUFFER, size, src, GL_STATIC_DRAW);
    }
    else
      glBufferSubData(GL_ARRAY_BUFFER, 0, size, src);

    break;
  case index:
    value = 0;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_);
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &value);
    if (value == 0)
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, src, GL_STATIC_DRAW);
    else
      glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, src);

    break;
  }

  size_ = size;
  return false;
}

void Buffer::BindBuffer(){
  switch (type_) {
  case vertex:
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
    break;
  case index:
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_);
    break;
  }
}
