#shader vertex
#version 330 core

layout (location = 0) in vec4 position; // the position vector has attribute position 0
layout (location = 1) in vec4 in_color;

// layout (location = 0) in vec4 position;

uniform mat4 projection_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);
// uniform vec2 mouse = vec2(0.0, 0.0);

out vec4 vertex_color;

void main()
{
    gl_Position = projection_matrix * vw_matrix * ml_matrix * position;
    vertex_color = in_color;
};

#shader fragment
#version 330 core

out vec4 fragment_color;

in vec4 vertex_color;

void main()
{
    fragment_color = vertex_color; 
};

