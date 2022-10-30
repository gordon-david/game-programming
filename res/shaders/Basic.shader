#shader vertex
#version 330 core

layout (location = 0) in vec4 aPosition; // the position vector has attribute position 0
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 projection_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);
uniform vec2 mouse = vec2(0.0, 0.0);
uniform vec2 light_pos = vec2(0.0, 0.0);

out vec4 vertex_color;
out vec4 pos;
out vec4 m_pos;
out vec2 TexCoord;
void main()
{
    gl_Position = projection_matrix * vw_matrix * ml_matrix * aPosition;
    vertex_color = aColor;
    pos = aPosition;
    m_pos = ml_matrix * aPosition;
    TexCoord = aTexCoord;
};

#shader fragment
#version 330 core

out vec4 fragment_color;

uniform vec2 light_pos;
uniform sampler2D Texture;

in vec4 vertex_color;
in vec4 pos;
in vec4 m_pos;
in vec2 TexCoord;


void main()
{
    float intensity = 1.0 / length(m_pos.xy - light_pos) ;
    fragment_color = texture(Texture, TexCoord) * intensity;
//  fragment_color = vertex_color * intensity; 
};

