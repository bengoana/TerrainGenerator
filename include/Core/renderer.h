/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#ifndef __RENDERER_H__
#define __RENDERER_H__ 1

#include "Core/node.h"
#include "glm/glm.hpp"

#include "glad/gl.h"
#include "glfw/glfw3.h"


class Renderer {
public:
  Renderer();
  ~Renderer();
  //!Receives a parent node and a camera node and renders the whole hierarchy from the perspective of the camera
  void RenderHierarchy(Node* root, Node* camera);
  //!Sets the screens clear color
  void setClearColor(float* color);

private:
  //!Renders one node (called recursively)
  void RenderNode(Node* node, glm::mat4 view, glm::mat4 proj);
};

class Input {
public:
  Input();
  ~Input();
  //!Returns true if the key is pressed
  static bool IsKeyPressed(char key, GLFWwindow* window);
  //!Returns a vector with the delta translation of the mouse
  static glm::vec2 MouseDelta(GLFWwindow* window);

private:
};

class Time {
public:
  Time();
  ~Time();
  //!Returns the current time
  static unsigned int CurrentTime();
};



#endif //__RENDERER_H__