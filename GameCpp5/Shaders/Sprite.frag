// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330

// Tex coord input from vertex shader
in vec2 fragTexCoord;
in vec3 vertColor;

// This is used for the texture sampling
uniform sampler2D uTexture;

void main()
{
	// Sample color from texture
	vec4 color = texture(uTexture, fragTexCoord);

	vec3 _color;
	_color.r = (color.r + vertColor.r) / 2.f;
	_color.g = (color.g + vertColor.g) / 2.f;
	_color.b = (color.b + vertColor.b) / 2.f;

	//透明度はテクスチャのものを使用する
	//アルファブレンディングを意図通りに動作させるため
	gl_FragColor = vec4(_color, color.a);
}
