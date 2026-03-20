#ifndef RENDER_H
#define RENDER_H

#include <iostream>

class Renderer{};

void prepareOpenGLRender(const float* vertices,
	const std::size_t vertices_size,
	const int* indicies,
	const std::size_t indicies_size
);

void render();
void printMaxVertAttribs();

#endif
