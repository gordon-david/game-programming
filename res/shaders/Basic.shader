#shader vertex
#version 330 core

layout (location = 0) in vec4 position; // the position vector has attribute position 0
layout (location = 1) in vec4 in_color;

uniform mat4 projection_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);
uniform vec2 mouse = vec2(0.0, 0.0);
uniform vec2 light_pos = vec2(0.0, 0.0);

out vec4 vertex_color;
out vec4 pos;
out vec4 m_pos;
void main()
{
    gl_Position = projection_matrix * vw_matrix * ml_matrix * position;
    vertex_color = in_color;
    pos = position;
    m_pos = ml_matrix * position;
};

#shader fragment
#version 330 core

out vec4 fragment_color;

uniform vec2 light_pos;

in vec4 vertex_color;
in vec4 pos;
in vec4 m_pos;

void main()
{
    float intensity = 1.0 / (length(m_pos.xy - light_pos) + 0.005) + 200;
    // float intensity = 1.1;
    fragment_color = vertex_color * intensity; 
};

