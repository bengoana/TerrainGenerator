/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/


#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext/matrix_transform.hpp"

#include "Core/renderer.h"
#include "Core/program.h"
#include "Core/buffer.h"

#include <chrono>

static std::chrono::steady_clock::time_point start_time_;
static glm::vec2 last_mouse_pos;

Renderer::Renderer(){
  start_time_ = std::chrono::steady_clock::now();
}

Renderer::~Renderer(){

}

void Renderer::RenderHierarchy(Node* root, Node* camera){
  for (int i = 0; i < root->numChildren(); i++) {
    Node* child = root->getChild(i);
    child->_updateDirVectors();
    child->world_m_ = root->world_m_ * child->local_m_;

    RenderHierarchy(child, camera);
  }
  camera->_updateDirVectors();
  glm::vec3 pos = { camera->position_.x,camera->position_.y,camera->position_.z };
  const float* frwd = camera->getForward();
  glm::vec3 forward = { frwd[0],frwd[1] ,frwd[2] };

  const float* up_tr = camera->getUp();
  glm::vec3 up = { up_tr[0],up_tr[1] ,up_tr[2] };

  glm::mat4 view_ = glm::lookAt(pos, pos + forward, up);

  glm::mat4 projection_ = glm::perspective(70.0f, 1.77777f,
   1.0f, 1000.0f);

  if(root->isInitialized()) 
    RenderNode(root, view_, projection_);

}

void Renderer::setClearColor(float* color){
  glClearColor(color[0], color[1], color[2], color[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderNode(Node* node, glm::mat4 view, glm::mat4 proj){
  
  node->getProgram()->SetCamera(view, proj);
  node->getProgram()->SetModel(node->world_m_);

  node->getProgram()->EnableProgram();


  node->getVertex()->BindBuffer();
  node->getIndex()->BindBuffer();

  node->RenderNode();

}

Input::Input(){
  last_mouse_pos = {0.0f,0.0f};
}

Input::~Input(){
}

bool Input::IsKeyPressed(char key, GLFWwindow* window){
  return glfwGetKey(window, key);
}

glm::vec2 Input::MouseDelta(GLFWwindow* window){
  double x, y;
  glfwGetCursorPos(window, (double*)&x, (double*)&y);
  

  glm::vec2 delta = glm::vec2(x,y) - last_mouse_pos;
  last_mouse_pos = {x,y};
  return delta;
}

Time::Time(){
}

Time::~Time(){
}

unsigned int Time::CurrentTime(){
  return std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::steady_clock::now() - start_time_).count();
}
