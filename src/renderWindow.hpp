#pragma once
#include <SDL.h>
#include <SDL_image.h>

class RenderWindow
{
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    void clearWithBgColor();
    void setColor(SDL_Color p_color);
    void drawLine(float p_prevX, float p_prevY, float p_x, float p_y);
    int getRefreshRate();
    
    void cleanUp();
    void clear();
    void render(SDL_Texture* p_tex);
    void display();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};