/*---------------------------------------------------------------------
Copyright (c) 2020 Pablo Bengoa (bengoana)
https://github.com/bengoana

This software is released under the MIT license.

This program is a college project uploaded for showcase purposes.
---------------------------------------------------------------------*/

#include "terrain.h"

Terrain::Terrain(){
	side_size_ = 0;
	seedpos_ = {0,0};
	octaves_ = 4.0f;
	amplitude_increase_ = 0.4f;
	freq_increase_ = 2.3f;
	base_amplitude_ = 20.0f;
	base_frequency_ = 1.0f;
}

Terrain::~Terrain(){
}

const int kSampleSize = 1024;

static struct BaseNoiseData {
	int table[kSampleSize * 2];
	bool created = false;
} NoiseData;

static const float MAX_RAND = 6.0f;

static float Rand() {
	return rand() / (RAND_MAX + 1.0f);
}

static float RandRange(float min, float max, unsigned int seed) {
	srand(seed);
	return min + (max - min) * Rand();
}

static glm::vec2 GetConstantVector(int v) {
	//v is the value from the permutation table
	int h = v & 3;
	if (h == 0)
		return glm::vec2(1.0, 1.0);
	else if (h == 1)
		return glm::vec2(-1.0, 1.0);
	else if (h == 2)
		return glm::vec2(-1.0, -1.0);
	else
		return glm::vec2(1.0, -1.0);
}

static float Fade(float t) {
	return ((6.0f * t - 15.0f) * t + 10.0f) * t * t * t;
}

static float Lerp(float t, float a1, float a2) {
	return a1 + t * (a2 - a1);
}

void Terrain::DiamondStep(float* heightmap, int x, int y, int step_size, float RAND, unsigned int currentseedpos) {
	float h1 = heightmap[y * side_size_ + x];
	float h2 = heightmap[y * side_size_ + (x + step_size)];
	float h3 = heightmap[(y+step_size) * side_size_ + x];
	float h4 = heightmap[(y + step_size) * side_size_ + (x + step_size)];

	float avg = (h1 + h2 + h3 + h4) * 0.25; // *1/4
	unsigned int seedpos = (y + step_size / 2) * side_size_ + (x + step_size / 2) + currentseedpos;
	heightmap[(y + step_size/2) * side_size_ + (x + step_size/2)] = avg; //+rand
}

void Terrain::SquareStep(float* heightmap, int x, int y, int step_size, float RAND, unsigned int currentseedpos) {
	float h1 = heightmap[y * side_size_ + x];
	float h2 = heightmap[y * side_size_ + (x + step_size)];
	float h3 = heightmap[(y + step_size) * side_size_ + x];
	float h4 = heightmap[(y + step_size) * side_size_ + (x + step_size)];

	float center = heightmap[(y + step_size / 2) * side_size_ + (x + step_size / 2)];

	float center_extra = 0.0f;
	float extra_division = 0.0f;
	//Check top extra
	if ((y - step_size / 2) > 0) {
		center_extra = heightmap[(y - step_size / 2) * side_size_ + (x + step_size / 2)];
		extra_division = 0.08333333f;
	}

	float avgtop = (h1 + h2 + center + center_extra) * (0.33333333f - extra_division); // * 1/3

	//Check right extra
	if ((x + step_size / 2 + step_size) < side_size_) {
		center_extra = heightmap[(y + step_size / 2) * side_size_ + (x + step_size / 2 + step_size)];
		extra_division = 0.08333333f;
	} else {
		center_extra = 0.0;
		extra_division = 0.0f;
	}
	
	float avgrgt = (h2 + h4 + center + center_extra) * (0.33333333f - extra_division);
	
	//Check left extra
	if ((x - step_size / 2) > 0) {
		center_extra = heightmap[(y + step_size / 2) * side_size_ + (x - step_size / 2)];
		extra_division = 0.08333333f;
	}
	else {
		center_extra = 0.0;
		extra_division = 0.0f;
	}
	
	float avglft = (h1 + h3 + center + center_extra) * (0.33333333f - extra_division);
	
	//Check bottom extra
	if ((y + step_size / 2 + step_size) < side_size_) {
		center_extra = heightmap[(y + step_size / 2 + step_size) * side_size_ + (x + step_size / 2)];
		extra_division = 0.08333333f;
	}
	else {
		center_extra = 0.0;
		extra_division = 0.0f;
	}

	float avgbtm = (h3 + h4 + center + center_extra) * (0.33333333f - extra_division);

	unsigned int seedpos = y * side_size_ + (x + step_size / 2) + currentseedpos;
	heightmap[y * side_size_ + (x + step_size / 2)] = avgtop;
	
	seedpos = (y + step_size / 2) * side_size_ + (x + step_size) + currentseedpos;
	heightmap[(y + step_size / 2) * side_size_ + (x + step_size)] = avgrgt;
	
	seedpos = (y + step_size / 2) * side_size_ + x + currentseedpos;
	heightmap[(y + step_size / 2) * side_size_ + x] = avglft;
	
	seedpos = (y + step_size) * side_size_ + (x + step_size / 2) + currentseedpos;
	heightmap[(y + step_size) * side_size_ + (x + step_size / 2)] = avgbtm;

}

float Terrain::getNoise2D(float x, float y)
{
	//Suppose x, y and z are the float input
	int X = (int)floor(x) & 255;
	int Y = (int)floor(y) & 255;
	float xf = x - floor(x);
	float yf = y - floor(y);

	glm::vec2 topRight = glm::vec2(xf - 1.0, yf - 1.0);
	glm::vec2 topLeft = glm::vec2(xf, yf - 1.0);
	glm::vec2 bottomRight = glm::vec2(xf - 1.0, yf);
	glm::vec2 bottomLeft = glm::vec2(xf, yf);


	int valueTopRight = NoiseData.table[(NoiseData.table[(X + 1)] + Y + 1)];
	int valueTopLeft = NoiseData.table[(NoiseData.table[(X)] + Y + 1)];
	int valueBottomRight = NoiseData.table[(NoiseData.table[(X + 1)] + Y)];
	int valueBottomLeft = NoiseData.table[(NoiseData.table[(X)] + Y)];

	float dotTopRight = glm::dot(topRight, GetConstantVector(valueTopRight));
	float dotTopLeft = glm::dot(topLeft, GetConstantVector(valueTopLeft));
	float dotBottomRight = glm::dot(bottomRight, GetConstantVector(valueBottomRight));
	float dotBottomLeft = glm::dot(bottomLeft, GetConstantVector(valueBottomLeft));


	float u = Fade(xf);
	float v = Fade(yf);
	float result = Lerp(u,
		Lerp(v, dotBottomLeft, dotTopLeft),
		Lerp(v, dotBottomRight, dotTopRight)
	);

	return result;
}

float Terrain::getHeight2D(float basex, float basey, float x, float y, float definition)
{
	float total_height_ = 0.0f;
	float amplitude_ = base_amplitude_;
	float frequency_ = base_frequency_;
	for (int k = 0; k < octaves_; ++k) {
		total_height_ += getNoise2D((basex + x) * definition * frequency_, (basey + y) * definition * frequency_) * amplitude_;
		amplitude_ *= amplitude_increase_;
		frequency_ *= freq_increase_;
	}
	return total_height_;
}

void Terrain::CreateTerrain(int side_size, glm::u32vec2 seedpos, unsigned int base_seed){
	seedpos_ = seedpos + base_seed;
	scoped_array<float> height_data_;
	height_data_.alloc(side_size * side_size);
	vertices_.alloc(side_size * side_size);
	
	side_size_ = side_size;
	numStripsRequired = side_size_ - 1;
	verticesPerStrip = 2 * side_size_;

	indices_.alloc(numStripsRequired * numStripsRequired * 6);
	// Initialise terrain - set values in the height map to 0
	for (int x = 0; x < side_size_ * side_size_; x++){
		height_data_[x] = 0.0f;
	}
	//set seed for current chunk
	unsigned int current_seed_pos = seedpos_.y * side_size_ + seedpos_.x;

	float RAND = MAX_RAND;
	height_data_[0] = RandRange(-RAND , RAND, current_seed_pos );
	height_data_[side_size_ - 1] = RandRange(-RAND, RAND, current_seed_pos + side_size_ - 1);
	height_data_[(side_size_ - 1) * side_size_] = RandRange(-RAND, RAND, (side_size_ - 1) * side_size_ + current_seed_pos);
	height_data_[(side_size_ - 1) * side_size_ + (side_size_-1)] = RandRange(-RAND, RAND, (side_size_ - 1) * side_size_ + (side_size_ - 1) + current_seed_pos);

	unsigned int step_size = side_size_ - 1;
	RAND *= 0.5f;


	while (step_size > 1) {
		for (int y = 0; y < side_size_ - 1; y += step_size){
			for (int x = 0; x < side_size_ - 1; x += step_size) {
				DiamondStep(height_data_.get(), x, y, step_size, RAND, current_seed_pos);
			}
		}
		for (int y = 0; y < side_size_ - 1; y += step_size) {
			for (int x = 0; x < side_size_ - 1; x += step_size) {
				SquareStep(height_data_.get(), x, y, step_size, RAND, current_seed_pos);
			}
		}

		step_size /= 2;
		RAND *= 0.4f;
	}



	// Intialise vertex array
	int i = 0;

	for (int z = 0; z < side_size_; z++)
	{
		for (int x = 0; x < side_size_; x++)
		{
			// Set the coords (1st 4 elements) and a default colour of black (2nd 4 elements) 
			vertices_[i] = { { (float)x, height_data_[x * side_size_ + z], (float)z}, { (float)x / (float)side_size_, (float)z / (float)side_size_, 0.0} };
			i++;
		}
	}

	// Now build the index data 
	i = 0;
	for (int z = 0; z < side_size_ - 1; z++) {
		for (int x = 0; x < side_size - 1; x++) {
			indices_[i] = z * side_size_ + x;
			indices_[i+1] = (z+1) * side_size_ + (x+1);
			indices_[i+2] = z * side_size_ + (x+1);

			indices_[i + 3] = (z + 1) * side_size_ + x;
			indices_[i + 4] = (z + 1) * side_size_ + (x + 1);
			indices_[i + 5] = z * side_size_ + (x);
			i += 6;
		}
	}

}

void Terrain::CreateTerrainNoise(int x, int y, int side_size, float definition){
	scoped_array<float> height_data_;
	height_data_.alloc(side_size * side_size);
	vertices_.alloc(side_size * side_size);

	side_size_ = side_size;
	numStripsRequired = side_size_ - 1;
	verticesPerStrip = 2 * side_size_;

	indices_.alloc(numStripsRequired * numStripsRequired * 6);
	// Initialise terrain - set values in the height map to 0
	for (int x = 0; x < side_size_ * side_size_; x++) {
		height_data_[x] = 0.0f;
	}

	for (int i = 0; i < side_size_; ++i) {
		for (int j = 0; j < side_size_; j++) {
			//multiple passes for Fractal Brownian Motion
			
			height_data_[i * side_size_ + j] = getHeight2D(x,y,j,i,definition);

			//float total_height_ = 0.0f;
			//float amplitude_ = base_amplitude_;
			//float frequency_ = base_frequency_;
			//for (int k = 0; k < octaves_; ++k) {
			//	total_height_ += getNoise2D((x + j) * definition * frequency_, (y + i) * definition * frequency_) * amplitude_;
			//	amplitude_ *= amplitude_increase_;
			//	frequency_ *= freq_increase_;
			//}
			//height_data_[i * side_size_ + j] = total_height_;
		}
	}

	// Intialise vertex array
	int i = 0;

	for (int z = 0; z < side_size_; z++)
	{
		for (int j = 0; j < side_size_; j++)
		{
			
			
			float hL = getHeight2D(x, y, z - 1, j, definition);
			float hR = getHeight2D(x, y, z + 1, j, definition);
			float hD = getHeight2D(x, y, z, j - 1, definition);
			float hU = getHeight2D(x, y, z, j  + 1, definition);

			glm::vec3 normal = {0.0f,0.0f,0.0f};
			normal.x = hL - hR;
			normal.y = hD - hU;
			normal.z = 2.0f;
			
			normal = glm::normalize(normal);

			float uv_multiplier = (1.0f / (float)side_size_) * 2.0f;

			vertices_[i] = { { (float)j, height_data_[j * side_size_ + z], (float)z}, normal,{x*uv_multiplier + z * uv_multiplier,y * uv_multiplier + j * uv_multiplier } };
			i++;
		}
	}

	// Now build the index data 
	i = 0;
	for (int z = 0; z < side_size_ - 1; z++) {
		for (int x = 0; x < side_size - 1; x++) {
			indices_[i] = z * side_size_ + x;
			indices_[i + 1] = (z + 1) * side_size_ + (x + 1);
			indices_[i + 2] = z * side_size_ + (x + 1);

			indices_[i + 3] = (z + 1) * side_size_ + x;
			indices_[i + 4] = (z + 1) * side_size_ + (x + 1);
			indices_[i + 5] = z * side_size_ + (x);
			i += 6;
		}
	}

}

void Terrain::InitPerlinSeed(int seed){
	srand(seed);
	if (!NoiseData.created) {
		for (int i = 0; i < kSampleSize; ++i) {
			NoiseData.table[i] = i;
		}
		
		//shuffle
		for (int i = kSampleSize - 1; i > 1; i--) {
			int index = rand() % (i - 1);
			int temp = NoiseData.table[i];

			NoiseData.table[i] = NoiseData.table[index];
			NoiseData.table[index] = temp;
		}

		for (int i = kSampleSize; i < kSampleSize * 2; ++i) {
			NoiseData.table[i] = NoiseData.table[i - kSampleSize];
		}
		NoiseData.created = true;
	}
}

unsigned int Terrain::getVertexSize(){
	return vertices_.sizeInBytes();
}

unsigned int Terrain::getIndexSize(){
	return indices_.sizeInBytes();
}

sVertex* Terrain::getVertices(){

	return vertices_.get();
}

unsigned int* Terrain::getIndices(){
	return indices_.get();
}

