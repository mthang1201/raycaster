#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include <vector>

#include "renderWindow.hpp"
#include "raycaster.hpp"

int worldMap[MAP_WIDTH][MAP_HEIGHT] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

Raycaster::Raycaster(int p_w, int p_h) : SCREEN_WIDTH(p_w), SCREEN_HEIGHT(p_h)
{
    float posX = 22, posY = 12;      // x and y start position
    float dirX = -1, dirY = 0;       // initial direction vector
    float planeX = 0, planeY = 0.66; // the 2d raycaster version of camera plane
    performDDA();
}

void Raycaster::performDDA(int x)
{
    // calculate ray position and direction
    float cameraX = 2 * x / float(SCREEN_WIDTH) - 1; // x-coordinate in camera space
    float rayDirX = dirX + planeX * cameraX;
    float rayDirY = dirY + planeY * cameraX;

    // which box of the map we're in
    int mapX = int(posX);
    int mapY = int(posY);

    // length of ray from current position to next x or y-side
    float sideDistX;
    float sideDistY;

    // length of ray from one x or y-side to next x or y-side
    float deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
    float deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
    float perpWallDist;

    // what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;

    int hit = 0; // was there a wall hit?
    int side;    // was a NS or a EW wall hit?

    // calculate step and initial sideDist
    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }
    // perform DDA
    while (hit == 0)
    {
        // jump to next map square, either in x-direction, or in y-direction
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        // Check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0)
            hit = 1;
    }
    // Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
    if (side == 0)
        perpWallDist = (sideDistX - deltaDistX);
    else
        perpWallDist = (sideDistY - deltaDistY);

    // Calculate height of line to draw on screen
    int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

    // calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
    if (drawStart < 0)
        drawStart = 0;
    int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
    if (drawEnd >= SCREEN_HEIGHT)
        drawEnd = SCREEN_HEIGHT - 1;
}

void Raycaster::chooseWallColor(SDL_Color p_color)
{
    SDL_Color color;
    switch (worldMap[mapX][mapY])
    {
    case 1:
        color = {66, 30, 15};
        break; // red
    case 2:
        color = {25, 7, 26};
        break; // green
    case 3:
        color = {9, 1, 47};
        break; // blue
    case 4:
        color = {4, 4, 73};
        break; // white
    default:
        color = {0, 7, 100};
        break; // yellow
    }
}
