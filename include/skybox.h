/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#ifndef __SKYBOX_H__
#define __SKYBOX_H__ 1


#include "Core/Buffer.h"

class SkyBox {
public:

  SkyBox();
  ~SkyBox();

  void Init();

  Buffer* getVertices();
  Buffer* getIndices();

private:
  Buffer vertices_;
  Buffer indices_;
};

#endif //__SKYBOX_H__

