/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#include "Core/node.h"
#include "glm/glm.hpp"
#include "glm\gtx\transform.hpp"

#include "glad/gl.h"

static bool is_in_vector(std::vector<Node*> vector, Node* temp) {
  for (std::vector<Node*>::iterator i = vector.begin(); i != vector.end(); ++i) {
    if (*i == temp) return true;
  }
  return false;
}

static void delete_from_vector(std::vector<Node*>& vector, Node* node) {
  std::vector<Node*>::iterator todelete;
  bool found = false;
  for (std::vector<Node*>::iterator i = vector.begin(); i != vector.end(); ++i) {
    if (*i == node) {
      todelete = i;
      found = true;
    }
  }
  if (found) vector.erase(todelete);
}

Node::Node(){
  position_ = { 0.0f,0.0f,0.0f };
  scale_ = { 1.0f,1.0f,1.0f };
  rotation_ = { 0.0f,0.0f,0.0f };

  world_m_ = glm::identity<glm::mat4>();
  local_m_ = glm::identity<glm::mat4>();

  forward_ = { 0.0f,0.0f,-1.0f };
  right_ = { 1.0f,0.0f,0.0f };
  up_ = { 0.0f,1.0f,0.0f };

  parent_ = nullptr;
  initialized_ = false;
  is_skybox_ = false;
  draw_mode_ = 0;
}

Node::~Node(){
  children.clear();
}

void Node::Init(Program* program, Buffer *vertices, Buffer *index){
  program_ = program;
  vertices_ = vertices;
  indices_ = index;
  initialized_ = true;
}

void Node::setBuffers(Buffer* vertices, Buffer* index){
  vertices_ = vertices;
  indices_ = index;
}

void Node::setPosition(const float* pos){
  position_.x = pos[0];
  position_.y = pos[1];
  position_.z = pos[2];
}

void Node::setRotation(const float* rot){
  rotation_.x = rot[0];
  rotation_.y = rot[1];
  rotation_.z = rot[2];
}

void Node::setScale(const float* scale){
  scale_.x = scale[0];
  scale_.y = scale[1];
  scale_.z = scale[2];
}

const float* Node::getForward(){
  return &forward_[0];
}

const float* Node::getRight(){
  return &right_[0];
}

const float* Node::getUp(){
  return &up_[0];
}

void Node::_updateDirVectors(){

  //Generate transform matrixes
  glm::mat4 pos_m = glm::translate(position_);
  glm::mat4 scale_m = glm::scale(scale_);

  float x = rotation_.x;
  float y = rotation_.y;
  float z = rotation_.z;

  glm::mat4 rotation_x = glm::rotate(x, glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 rotation_y = glm::rotate(y, glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 rotation_z = glm::rotate(z, glm::vec3(0.0f, 0.0f, 1.0f));

  glm::mat4 rotation_m = (rotation_y * rotation_x) * rotation_z;


  local_m_ = rotation_m * pos_m * scale_m;

  forward_ = glm::vec3(rotation_m * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
  right_ = glm::vec3(rotation_m * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
  forward_ = glm::normalize(forward_);
  right_ = glm::normalize(right_);
  up_ = glm::cross(forward_, right_);
  up_ = glm::normalize(up_);
}

void Node::AddChild(Node* child){
  if (child->parent_ == nullptr) {
    if (!is_in_vector(children, child)) {
      children.push_back(child);
      child->parent_ = this;
    }
  }
}

void Node::RemoveChild(Node* child){
  delete_from_vector(children, child);
}

Node* Node::getChild(int pos){
  if (pos >= children.size()) return nullptr;
  return children[pos];
}

int Node::numChildren(){
  return children.size();
}

bool Node::isInitialized(){
    return initialized_;
}

void Node::RenderNode(){
  //All nodes same layout
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, (void*)12);
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, (void*)24);
  glEnableVertexAttribArray(2);

  unsigned int elements = getIndex()->getSize() >> 2;

  printf("draw elements: %d\n", glGetError());

  if (is_skybox_) {
    glDepthMask(GL_FALSE);
    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  switch (draw_mode_){
  case 0:
    glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, 0);
    break;
  case 1:
    glDrawElements(GL_LINES, elements, GL_UNSIGNED_INT, 0);
    break;
  case 2:
    glDrawElements(GL_POINTS, elements, GL_UNSIGNED_INT, 0);
    break;
  }

  glDepthMask(GL_TRUE);
  glCullFace(GL_BACK);
}
