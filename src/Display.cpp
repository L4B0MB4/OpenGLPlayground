#include <iostream>
#include "Display.h"
#include <GL/glew.h>
#define COLOR_VALUE 8

Display::Display(int width, int height, const std::string& title)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,COLOR_VALUE);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,COLOR_VALUE);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,COLOR_VALUE);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,COLOR_VALUE);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,COLOR_VALUE * 4);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    this->glContext =SDL_GL_CreateContext(this->window);

    GLenum status = glewInit();
    if(status !=GLEW_OK)
    {
        std::cerr<<"Glew failed to initialize"<<std::endl;
    }

}

bool Display::isClosed()
{
    return this->closed;
}

void Display::UpdateWindow()
{
    SDL_GL_SwapWindow(this->window);

    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            this->closed =true;
        }
    }
}

Display::~Display()
{
    //dtor
    SDL_GL_DeleteContext(this->glContext);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    std::cout<<"dtor\n";
}
