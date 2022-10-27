#include "Shader.h"

Shader::Shader(const std::string &filepath)
    : m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = this->ParseShader(filepath);
    this->m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() { GLCALL(glDeleteProgram(this->m_RendererID)); }

ShaderProgramSource Shader::ParseShader(const std::string &filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                // set mode to vertex
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                // set mode to fragment
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

// source must exist at this point
// type: unsigned int corresponds to GLenum denoting shader type
unsigned int Shader::CompileShader(unsigned int type,
                                   const std::string &source)
{
    GLCALL(unsigned int id = glCreateShader(type));
    const char *src = source.c_str();
    GLCALL(glShaderSource(id, 1, &src, nullptr));
    GLCALL(glCompileShader(id));

    int result;
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE)
    {
        int length;
        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length * sizeof(char));
        GLCALL(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile"
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << std::endl;
        std::cout << message << std::endl;

        GLCALL(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader,
                                  const std::string &fragmentShader)
{
    GLCALL(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCALL(glAttachShader(program, vs));
    GLCALL(glAttachShader(program, fs));
    GLCALL(glLinkProgram(program));
    GLCALL(glValidateProgram(program));

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));

    return program;
}

void Shader::Bind() const { GLCALL(glUseProgram(this->m_RendererID)); }

void Shader::Unbind() const { GLCALL(glUseProgram(0)); }

void Shader::setBool(const std::string &name, bool value) const
{
    GLCALL(glUniform1i(glGetUniformLocation(this->m_RendererID, name.c_str()),
                       (int)value))
}
void Shader::setInt(const std::string &name, int value) const
{
    GLCALL(glUniform1i(glGetUniformLocation(this->m_RendererID, name.c_str()),
                       value))
}
void Shader::setFloat(const std::string &name, float value) const
{
    GLCALL(glUniform1f(glGetUniformLocation(this->m_RendererID, name.c_str()),
                       value))
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2,
                          float v3)
{
    GLCALL(glUniform4f(this->GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4(const std::string &name, Math::Mat4 &matrix)
{
    // GLCALL(glUniformMatrix4fv(this->GetUniformLocation(name), 1, GL_FALSE, matrix.elements));
    GLCALL(glUniformMatrix4fv(glGetUniformLocation(this->m_RendererID, name.c_str()), 1, GL_FALSE, matrix.elements));
}

int Shader::GetUniformLocation(const std::string &name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end() && m_UniformLocationCache[name] != -1)
        return m_UniformLocationCache[name];
    GLCALL(int location = glGetUniformLocation(this->m_RendererID, name.c_str()));
    m_UniformLocationCache[name] = location;
    // uniform location can be -1 if we create it and haven't used it
    if (location == -1)
    {
        std::cout << "Warning: uniform '" << name << "' doesn't exist" << std::endl;
    }

    // location can be cached
    return location;
}

void Shader::SetUniformVec2(const std::string &name, Math::Vec2 &vector)
{
	GLCALL(glUniform2f(glGetUniformLocation(this->m_RendererID, name.c_str()), vector.x, vector.y)); 
}
