/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#ifndef __TEXTURE_H__
#define __TEXTURE_H__ 1

#include <vector>

class Texture {
public:
  enum eType {
    k2D,
    kCube
  };

  enum eWrap {
    kClamp,
    kRepeat,
  };
  enum eFilter {
    kLinear,
    kNearest
  };



  Texture();
  ~Texture();
  //!Loads texture from a file
  void LoadTexture(const char* filepath);
  //!Loads cubemap from 6 image files (order must be right,left,top,bottom,front,back)
  void LoadTextureCube(std::vector<const char*> filename);
  void LoadFromMemory(void* src, int width, int height);
  //!Creates opengl resources if necessary
  void Bind();

  unsigned int getId();

  bool initialized_;
  eWrap wrap_;
  eFilter filter_;
private:
  unsigned int texture_id_;
  eType type_;
};


#endif //__TEXTURE_H__

