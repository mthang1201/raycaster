#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "renderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h) : window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    return texture;
}

void RenderWindow::clearWithBgColor()
{
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 0);
    SDL_RenderClear(renderer);
}

void RenderWindow::setColor(SDL_Color p_color)
{
    SDL_SetRenderDrawColor(renderer, p_color.r, p_color.g, p_color.b, 255);
}

void RenderWindow::drawLine(float p_prevX, float p_prevY, float p_x, float p_y)
{
    SDL_RenderDrawLine(renderer, (int)p_prevX, (int)p_prevY, (int)p_x, (int)p_y);
}

int RenderWindow::getRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(window);

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* p_tex)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 0;
    src.h = 0;
    
    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    dst.w = 0;
    dst.h = 0;
    
    SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}