#version 330 core

layout (location = 0) in vec3 vVertex;
layout (location = 1) in vec2 vt;

// in vec3 vColor;
uniform mat4 vModel;
uniform mat4 vView;
uniform mat4 vProjection;

out vec2 texture_coordinates;;

void main(void) {
	gl_Position = vProjection * vView * vModel * vec4(vVertex, 1.0);
	// fColor = vColor; //Interpolate color
	texture_coordinates = vt;
}
