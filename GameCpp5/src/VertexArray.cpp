// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts)
	,mNumIndices(numIndices)
{
	// Create vertex array
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// Create vertex buffer
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	//numVerts * num * sizeof~ / num: 頂点一つあたりの要素数の合計
	glBufferData(GL_ARRAY_BUFFER, numVerts * 8 * sizeof(float), verts, GL_STATIC_DRAW);

	// Create index buffer
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// Specify the vertex attributes
	// (For now, assume one vertex format)
	// Position is 3 floats starting at offset 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);

	//uv, １番目の属性，頂点サイズは各属性の要素の合計値, 
	// オフセットは０番目の属性が三要素なので3
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
		reinterpret_cast<void*>(sizeof(float) * 3));

	//頂点カラー, ２番目の属性
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
		reinterpret_cast<void*>(sizeof(float) * 5));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}
