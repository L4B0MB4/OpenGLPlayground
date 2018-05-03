#include <iostream>
#include <GL/glew.h>
#include "Display.h"
#include "Shader.h"

int main(char argc, char** argv)
{
    std::cout << argv[0] << std::endl;
    Display d(1280,800,"Hello World");
    /*Vertex vertices[] =
	{
		Vertex(glm::vec3(-0.5, -0.5, 0)),
		Vertex(glm::vec3(0, 0.5, 0)),
		Vertex(glm::vec3(0.5, -0.5, 0))
    }

    Mesh mesh(vertices,sizeof(vertices)/sizeof(vertices[0]));*/

    Shader shader("./res/BasicShader");
    while(!d.isClosed())
    {
        glClearColor(0.0f,0.5f,0.3f,1.0f);
        shader.Bind();
        //mesh.Draw();
        d.UpdateWindow();
    }

    return 0;
}
