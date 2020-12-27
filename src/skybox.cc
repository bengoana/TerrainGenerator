/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/
#include "..\include\skybox.h"

SkyBox::SkyBox(){
}

SkyBox::~SkyBox(){
}

void SkyBox::Init(){
	//cube vertices
//position			color
	sVertex cube_vertices[] =
	{
			{{1.f, 1.f, 1.f		},{	1.0f, 0.0f, 0.0f,	 },{}},//0
			{{-1.f, 1.f, 1.f	},{		0.0f, 1.0f, 0.0f},	 {}},//1
			{{-1.f, 1.f, -1.f	},{	0.0f, 0.0f, 1.0f	 },{}},//2
			{{1.f, 1.f, -1.f	},{		1.0f, 1.0f, 1.0f},	 {}},//3
			{{1.f, -1.f, 1.f	},{		1.0f, 1.0f, 0.0f},	 {}},//4
			{{-1.f, -1.f, 1.f	},{	1.0f, 1.0f, 1.0f	 },{}},//5
			{{-1.f, -1.f, -1.f},{		0.0f, 1.0f, 1.0f},{	}},//6
			{{1.f, -1.f, -1.f	},{	1.0f, 0.0f, 1.0f	 },{}}//7
	};

	unsigned int indices[] =
	{
		0, 1, 3, //top 1
		3, 1, 2, //top 2
		2, 6, 7, //front 1
		7, 3, 2, //front 2
		7, 6, 5, //bottom 1
		5, 4, 7, //bottom 2
		5, 1, 4, //back 1
		4, 1, 0, //back 2
		4, 3, 7, //right 1
		3, 4, 0, //right 2
		5, 6, 2, //left 1
		5, 1, 2  //left 2
	};

	vertices_.initBuffer(Buffer::EBufferType::vertex, false);
	indices_.initBuffer(Buffer::EBufferType::index,false);

	vertices_.updateData(cube_vertices, sizeof(cube_vertices));
	
	indices_.updateData(indices, sizeof(indices));
}

Buffer* SkyBox::getVertices(){
  return &vertices_;
}

Buffer* SkyBox::getIndices(){
  return &indices_;
}
