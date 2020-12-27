/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#ifndef __PROGRAM_H__
#define __PROGRAM_H__ 1

#include "scoped_array.h"
#include "glm/glm.hpp"

class Program {
public:
  Program();
  ~Program();

  bool LoadShaders(const char* vertex, const char* fragment);
  bool LoadShaders(const char* vertex, const char* fragment, const char* geometry);

  //For programs with specific uniforms override func to set them
  virtual void EnableProgram();

  virtual void SetModel(glm::mat4 model);
  virtual void SetCamera(glm::mat4 view, glm::mat4 projection);

  unsigned int get_id();
protected:
  unsigned int program_id_;
  bool generated_;

  glm::mat4 model_;
  glm::mat4 view_;
  glm::mat4 proj_;

  int base_uniforms[3];

};


#endif //__PROGRAM_H__