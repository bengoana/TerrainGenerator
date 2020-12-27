/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#include <stdio.h>
#include <string>
#include <vector>

#include "glad/gl.h"
#include "glfw/glfw3.h"

#include "Core/program.h"
#include "Core/buffer.h"
#include "Core/node.h"
#include "Core/renderer.h"
#include "terrain.h"
#include "terrain_material.h"
#include "skybox.h"
#include "skybox_material.h"
#include "water.h"
#include "water_material.h"
#include "grass_material.h"

#include "terrain_manager.h"

struct WindowData {
	//const bgfx::ViewId kClearView = 0;
	int width_;
	int height_;
	GLFWwindow* window_;
	float delta_time_;
} WData;

Buffer vertex_buffer_;
Buffer index_buffer_;
Buffer vertex_buffer2_;
Buffer index_buffer2_;

Node root;
Node camera;
Renderer render_;

TerrainMaterial terrain_mat_;
Texture terrain_diffuse_;
Texture terrain_sand_;
Texture terrain_rock_;
Buffer vertex_buffers_[25];
Buffer index_buffers_[25];
Node terrain_nodes[25];
Terrain terrains[25];

Water water_;
WaterMaterial water_material_;
Node water_node_[25];
Buffer water_vbuffer_;
Buffer water_ibuffer_;

GrassMaterial grass_material_;
Node grass_node_[25];
Buffer grass_vertex_[25];
Buffer grass_index_[25];

SkyBox skybox;
SkyboxMaterial skybox_mat_;
Node skybox_node_;

TerrainManager tr_manager_;

float pos[2] = { 0.0f,0.0f };


void CameraMovement(GLFWwindow* window) {
	if (Input::IsKeyPressed('D', window)) {
		camera.position_.x += camera.getRight()[0] * 0.1f;
		camera.position_.y += camera.getRight()[1] * 0.1f;
		camera.position_.z += camera.getRight()[1] * 0.1f;
	}
	if (Input::IsKeyPressed('A', window)) {
		camera.position_.x -= camera.getRight()[0] * 0.1f;
		camera.position_.y -= camera.getRight()[1] * 0.1f;
		camera.position_.z -= camera.getRight()[1] * 0.1f;
	}
	if (Input::IsKeyPressed('W', window)) {
		camera.position_.x += camera.getForward()[0] * 0.6f;
		camera.position_.y += camera.getForward()[1] * 0.6f;
		camera.position_.z += camera.getForward()[2] * 0.6f;
	}
	if (Input::IsKeyPressed('S', window)) {
		camera.position_.x -= camera.getForward()[0] * 0.1f;
		camera.position_.y -= camera.getForward()[1] * 0.1f;
		camera.position_.z -= camera.getForward()[2] * 0.1f;
	}
	if (Input::IsKeyPressed('Q', window)) {
		camera.position_.y += 0.1f;
	}
	if (Input::IsKeyPressed('E', window)) {
		camera.position_.y -= 0.1f;
	}

	glm::vec2 deltamouse = Input::MouseDelta(window);
	camera.rotation_.y -= deltamouse.x * 0.005f;
	camera.rotation_.x += deltamouse.y * 0.005f;


}

void Prepare() {
	/*terrain_mat_.LoadShaders("../../../data/shaders/terrain.vert", "../../../data/shaders/terrain.frag");

	terrain_diffuse_.LoadTexture("../../../data/textures/snow.jpg");
	terrain_sand_.LoadTexture("../../../data/textures/sand.jpg");
	terrain_rock_.LoadTexture("../../../data/textures/rock.jpg");

	terrain_mat_.snow = terrain_diffuse_;
	terrain_mat_.sand = terrain_sand_;
	terrain_mat_.rock = terrain_rock_;
	terrain_mat_.switch_heights[0] = -1.5;
	terrain_mat_.switch_heights[1] = -3.0;*/

	camera.rotation_.y = 3.1415f;

	//grass_material_.LoadShaders("../../../data/shaders/grass.vert", "../../../data/shaders/grass.frag", "../../../data/shaders/grass.geom");

	//water_.InitPerlinSeed(8947);
	//water_.CreateWaterPlane(64, 64, 256, 0.05f);
	//water_.CreateWaterMaps();
	//
	//water_material_.LoadShaders("../../../data/shaders/water.vert", "../../../data/shaders/water.frag");
	//
	//water_material_.combined_map = water_.getCombinedMap();
	//water_material_.combined_map_detail_ = water_.getCombinedMap();
	//
	//water_vbuffer_.initBuffer(Buffer::EBufferType::vertex, true);
	//water_vbuffer_.updateData(water_.getVertices(), water_.getVertexSize());
	//
	//water_ibuffer_.initBuffer(Buffer::EBufferType::index, true);
	//water_ibuffer_.updateData(water_.getIndices(), water_.getIndexSize());


	//float scale[] = { 0.25f,0.25f,0.25f };
	//for (int i = 0; i < 2; ++i) {
	//	for (int j = 0; j < 2; j++) {
	//		//Terrains
	//		terrains[i * 5 + j].InitPerlinSeed(655449);
	//		terrains[i * 5 + j].CreateTerrainNoise(j * 127 + 64, i * 127 + 64, 128, 0.01f);
	//		//Buffers
	//		vertex_buffers_[i * 5 + j].initBuffer(Buffer::EBufferType::vertex, true);
	//		vertex_buffers_[i * 5 + j].updateData(terrains[i * 5 + j].getVertices(), terrains[i * 5 + j].getVertexSize());
	//
	//		index_buffers_[i * 5 + j].initBuffer(Buffer::EBufferType::index, true);
	//		index_buffers_[i * 5 + j].updateData(terrains[i * 5 + j].getIndices(), terrains[i * 5 + j].getIndexSize());
	//
	//		float pos[] = { i * 127.0f * 0.25f,-1.5f,j * 127.0f * 0.25f - 5.0f };
	//
	//		//Nodes
	//		terrain_nodes[i * 5 + j].Init(&terrain_mat_, &vertex_buffers_[i * 5 + j], &index_buffers_[i * 5 + j]);
	//		terrain_nodes[i * 5 + j].setPosition(pos);
	//		terrain_nodes[i * 5 + j].setScale(scale);
	//
	//		root.AddChild(&terrain_nodes[i * 5 + j]);
	//
	//		grass_node_[i * 5 + j].Init(&grass_material_, &vertex_buffers_[i * 5 + j], &index_buffers_[i * 5 + j]);
	//		grass_node_[i * 5 + j].setScale(scale);
	//		grass_node_[i * 5 + j].setPosition(pos);
	//		grass_node_[i * 5 + j].draw_mode_ = 2;
	//		root.AddChild(&grass_node_[i * 5 + j]);
	//
	//		float waterpos[] = { i * 127.0f * 0.25f,-2.0f,j * 127.0f * 0.25f - 5.0f };
	//		float waterscale[3];
	//		waterscale[0] = 0.125f;
	//		waterscale[1] = 0.125f;
	//		waterscale[2] = 0.125f;
	//
	//		water_node_[i*5+j].Init(&water_material_, &water_vbuffer_, &water_ibuffer_);
	//		water_node_[i*5+j].setPosition(waterpos);
	//		water_node_[i*5+j].setScale(waterscale);
	//		root.AddChild(&water_node_[i * 5 + j]);
	//
	//
	//	}
	//}

	//SKYBOX
	skybox.Init();

	skybox_mat_.LoadShaders("../../../data/shaders/skybox.vert", "../../../data/shaders/skybox.frag");

	std::vector<const char*> faces = {
	"../../../data/textures/skybox/right.jpg",
	"../../../data/textures/skybox/left.jpg",
	"../../../data/textures/skybox/top.jpg",
	"../../../data/textures/skybox/bottom.jpg",
	"../../../data/textures/skybox/front.jpg",
	"../../../data/textures/skybox/back.jpg",
	};
	skybox_mat_.diffuse.LoadTextureCube(faces);

	tr_manager_.skybox = &skybox_mat_.diffuse;

	skybox_node_.Init(&skybox_mat_, skybox.getVertices(), skybox.getIndices());
	skybox_node_.is_skybox_ = true;

	root.AddChild(&skybox_node_);

	//TERRAIN MANAGER

	tr_manager_.Init(&root,&camera.position_[0]);
}

void Update() {

	printf("Cam pos: %f, %f\n", camera.position_.x, camera.position_.z);
	tr_manager_.Update();
}

int main() {
	if (!glfwInit())
		return 1;

	WData.width_ = 1280;
	WData.height_ = 720;



	WData.window_ = glfwCreateWindow(WData.width_, WData.height_, "Terrain", NULL, NULL);

	if (!WData.window_)
	{
		glfwTerminate();
		return 1;
	}
	glfwSetWindowAttrib(WData.window_, GLFW_RESIZABLE, GLFW_FALSE);
	glfwSetWindowAttrib(WData.window_, GLFW_FLOATING, GLFW_FALSE);


	// Make the window's context current 
	glfwMakeContextCurrent(WData.window_);

	// Load OpenGL Functions
	gladLoadGL(glfwGetProcAddress);

	Prepare();

	while (!glfwWindowShouldClose(WData.window_)) {
		glfwPollEvents();		
		CameraMovement(WData.window_);
		glCullFace(GL_FRONT);
		glEnable(GL_DEPTH_TEST);
		float clear_color[] = { 0.2f,0.2f,0.2f,1.0f };

		Update();
		render_.setClearColor(clear_color);

		root._updateDirVectors();
		root.world_m_ = root.local_m_;
		render_.RenderHierarchy(&root,&camera);
		glfwSwapBuffers(WData.window_);



	}


	glfwTerminate();

	return 0;
}
