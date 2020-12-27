/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/


#ifndef __NODE_H__
#define __NODE_H__ 1

#include "Core/program.h"
#include "Core/buffer.h"
#include "glm/glm.hpp"
#include <vector>

class Node {
public:
  Node();
  ~Node();
  
  void Init(Program* program, Buffer *vertices, Buffer *index);

  void setBuffers(Buffer* vertices, Buffer* index);

  void setPosition(const float* pos);
  void setRotation(const float* rot);
  void setScale(const float* scale);

  const float* getForward();
  const float* getRight();
  const float* getUp();

  void _updateDirVectors();

  void AddChild(Node* child);
  void RemoveChild(Node* child);

  Node* getChild(int pos);
  int numChildren();
  bool isInitialized();
  //For specific render logic override func
  virtual void RenderNode();

  Program* getProgram() { return program_; }
  Buffer* getVertex() { return vertices_; }
  Buffer* getIndex() { return indices_; }

  glm::vec3 position_;
  glm::vec3 scale_;
  glm::vec3 rotation_;

  glm::mat4 world_m_;
  glm::mat4 local_m_;
  bool is_skybox_;
  int draw_mode_; //0 triangles, 1 lines, 2 points
private:
  glm::vec3 forward_;
  glm::vec3 right_;
  glm::vec3 up_;

  std::vector<Node*> children;
  
  Node* parent_;

  Program* program_;
  Buffer* vertices_;
  Buffer* indices_;
  bool initialized_;
};



#endif //__NODE_H__