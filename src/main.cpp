#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include <vector>

#include "renderWindow.hpp"
#include "utils.hpp"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

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

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "HEY... SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("Raycaster", SCREEN_WIDTH, SCREEN_HEIGHT);

    float posX = 22, posY = 12;      // x and y start position
    float dirX = -1, dirY = 0;       // initial direction vector
    float planeX = 0, planeY = 0.66; // the 2d raycaster version of camera plane

    std::cout << window.getRefreshRate() << std::endl;

    SDL_Texture *grassTexture = window.loadTexture("../res/gfx/ground_grass_1.png");

    bool gameRunning = true;

    SDL_Event event;

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();

    while (gameRunning)
    {
        int startTicks = SDL_GetTicks();
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;
        accumulator += frameTime;

        window.clearWithBgColor();

        while (accumulator >= timeStep)
        {
            for (int x = 0; x < SCREEN_WIDTH; x++)
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

                // choose wall color
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

                // give x and y sides different brightness
                if (side == 1)
                {
                    color.r = color.r / 2;
                    color.g = color.g / 2;
                    color.b = color.b / 2;
                }

                // draw the pixels of the stripe as a vertical line
                window.setColor(color);
                window.drawLine(x, drawStart, x, drawEnd);
            }

            // speed modifiers
            float moveSpeed = frameTime * 5.0; // the constant value is in squares/second
            float rotSpeed = frameTime * 3.0;  // the constant value is in radians/second

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    gameRunning = false;
                else if (event.type == SDL_KEYDOWN)
                {
                    // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        gameRunning = false;

                    if (event.key.keysym.sym == SDLK_UP)
                    {
                        if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false)
                            posX += dirX * moveSpeed;
                        if (worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false)
                            posY += dirY * moveSpeed;
                    }

                    if (event.key.keysym.sym == SDLK_DOWN)
                    {
                        if (worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false)
                            posX -= dirX * moveSpeed;
                        if (worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false)
                            posY -= dirY * moveSpeed;
                    }

                    if (event.key.keysym.sym == SDLK_RIGHT)
                    {
                        // both camera direction and camera plane must be rotated
                        float oldDirX = dirX;
                        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
                        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
                        float oldPlaneX = planeX;
                        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
                        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
                    }

                    if (event.key.keysym.sym == SDLK_LEFT)
                    {
                        // both camera direction and camera plane must be rotated
                        float oldDirX = dirX;
                        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
                        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
                        float oldPlaneX = planeX;
                        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
                        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
                    }
                }
            }

            accumulator -= timeStep;
        }

        const float alpha = accumulator / timeStep;

        window.display();

        int frameTicks = SDL_GetTicks() - startTicks;

        if (frameTicks < 1000 / window.getRefreshRate())
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
    }
    window.cleanUp();
    SDL_Quit();

    return 0;
}
