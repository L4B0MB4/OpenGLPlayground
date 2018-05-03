#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader
{
    public:
        Shader(const std::string& filename);
        virtual ~Shader();
        GLuint CreateShader(const std::string& text, GLenum type);
        void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

        void Bind();

    protected:

    private:
        Shader(const Shader& other);
        Shader& operator=(const Shader& other);

        static const unsigned int NUM_SHADERS =2;
        GLuint programm;
        GLuint shaders[NUM_SHADERS];
};

#endif // SHADER_H
