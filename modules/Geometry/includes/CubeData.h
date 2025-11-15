#pragma once

class CubeData {
public:
	//vertex data for cube side length 1
	float cubeVertices[24] = {
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f
	};

	int cubeIndices[36]{
		0, 4, 5,
		0, 1, 5,
		3, 2, 6,
		3, 7, 6,
		0, 2, 6,
		0, 4, 6,
		1, 3, 7,
		1, 5, 7,
		0, 1, 3,
		0, 2, 3,
		4, 5, 7,
		4, 6, 7
	};

};