#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

//#include "painter.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Ping pong";

void logSDLError(std::ostream& os, const std::string& msg, bool fatal = false);
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);

int main(int argc, char* argv[])
{
	srand(time(0));
	SDL_Window* window;
	SDL_Renderer* renderer;
	//SDL_Texture* texture = NULL;
	initSDL(window, renderer);

	//SDL_Texture* background = loadTexture("C:/Users/Minh Thang Bui/Pictures/wallpaper/10-15-Day.jpg", renderer);
	//SDL_RenderCopy(renderer, background, NULL, NULL);

	//Painter painter(window, renderer);
	//int figNumber = argc > 1 ? atoi(argv[1]) : 17;
	//switch (figNumber)
	//{
	///* Square */
	//case 0:
	//	painter.setColor(WHITE_COLOR);
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		painter.moveForward(100);
	//		painter.turnRight(90);
	//	}
	//	break;
	//}
	// use SDL_Renderer
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
	SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
	SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
	SDL_Rect filled_rect;
	filled_rect.x = SCREEN_WIDTH - 400;
	filled_rect.y = SCREEN_HEIGHT - 150;
	filled_rect.w = 320;
	filled_rect.h = 100;
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
	SDL_RenderFillRect(renderer, &filled_rect);

	// run at home
	SDL_RenderPresent(renderer);
	// run at school (using virtual machine)
	// SDL_UpdateWindowSurface(window);

	waitUntilKeyPressed();

	//SDL_DestroyTexture(texture);
	//texture = NULL;
	//SDL_DestroyTexture(background);
	//background = NULL;
	//
	quitSDL(window, renderer);
	return 0;
}

// SDL_Texture* loadTexture(string path, SDL_Renderer* renderer)
// {
// 	SDL_Texture* newTexture = nullptr;
// 	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
// 	if (loadedSurface == nullptr)
// 		cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
// 	else {
// 		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
// 		if (newTexture == nullptr)
// 			cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
// 		SDL_FreeSurface(loadedSurface);
// 	}
// 	return newTexture;
// }

void logSDLError(std::ostream& os, const std::string& msg, bool fatal)
{
	os << msg << "Error: " << SDL_GetError() << std::endl;
	if (fatal) {
		SDL_Quit();
		exit(1);
	}
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		logSDLError(std::cout, "SDL_Init", true);

	window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	//window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
	
	if (window == nullptr)
		logSDLError(std::cout, "CreateWindow", true);

	// run at home
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// run at school (using virtual machine)
	//renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

	if (renderer == nullptr)
		logSDLError(std::cout, "CreateRenderer", true);
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
	SDL_Event e;
	while (true) {
		if (SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
			return;
		SDL_Delay(100);
	}
}

//float generateRandomNumber()
//{
//	return (float)rand() / RAND_MAX;
//}
//
//void randomWalk(Painter* painter)
//{
//	const int STEPS = 10;
//	const float MAX_LENGTH = 100;
//	for (int i = 0; i < STEPS; i++) {
//		float length = generateRandomNumber() * MAX_LENGTH;
//		painter->moveForward(length);
//		float angle = generateRandomNumber() * 360;
//		painter->turnLeft(angle);
//	}
//}
//
//const SDL_Color PALETTE[] = {
//	SDL_Color({66, 30, 15})
//};
//const int PALETTE_COUNT = sizeof(PALETTE) / sizeof(SDL_Color);