#version 330 core
layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 vertex_texture;

out vec2 textCoord;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main()
{
   textCoord = vertex_texture;
   gl_Position = projectionMatrix * modelMatrix * vec4(vertex_position, 0.0, 1.0);
}
