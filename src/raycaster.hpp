#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include <vector>

#include "renderWindow.hpp"

class Raycaster
{
public:
    Raycaster(int p_w, int p_h);
    void init();
    void performDDA(int x);
    void chooseWallColor(SDL_Color p_color);

private:
    float posX, posY;
    float dirX, dirY;
    float planeX, planeY;
    float mapX, mapY;
    int SCREEN_WIDTH, SCREEN_HEIGHT;
}