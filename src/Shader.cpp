#include "Shader.h"
#include <iostream>
#include <fstream>

static std::string LoadShader(const std::string& filename);
enum{VertexShader,FragmentShader};

Shader::Shader(const std::string& filename)
{
    this->programm = glCreateProgram();
    this->shaders[VertexShader] = CreateShader(LoadShader(filename+".vertexS"),GL_VERTEX_SHADER);
    this->shaders[FragmentShader] = CreateShader(LoadShader(filename+".fragmentS"),GL_FRAGMENT_SHADER);

    for(int i=0;i<this->NUM_SHADERS;i++)
    {
        glAttachShader(this->programm,this->shaders[i]);
    }

    glBindAttribLocation(this->programm,0,"position");

    glLinkProgram(this->programm);
    CheckShaderError(this->programm,GL_LINK_STATUS,true,"Error: Shaderprogramm failed to link: ");

    glValidateProgram(this->programm);
    CheckShaderError(this->programm,GL_VALIDATE_STATUS,true,"Error: Shaderprogramm failed to validate: ");

}

void Shader::Bind()
{
	glUseProgram(this->programm);
}

Shader::~Shader()
{
    for(int i=0;i<this->NUM_SHADERS;i++)
    {
        glDetachShader(this->programm,this->shaders[i]);
        glDeleteShader(this->shaders[i]);
    }

    glDeleteProgram(this->programm);
}


static std::string LoadShader(const std::string& filename)
{
    std::ifstream file;
    file.open((filename).c_str());
    std::string output;
    std::string line;
    if(file.is_open())
    {
        while(file.good())
        {
            getline(file,line);
            output.append(line+"\n");
        }
    }
    else
    {
        std::cerr <<"Unable to load shader file "<<filename<<std::endl;
    }
    return output;
}


void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint Shader::CreateShader(const std::string& text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if(shader == 0)
		std::cerr << "Error compiling shader type " << type << std::endl;

    const GLchar* shaderSourceStrings[1];
    shaderSourceStrings[0] = text.c_str();
    GLint lengths[1];
    lengths[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, lengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

    return shader;
}

