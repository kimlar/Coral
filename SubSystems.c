#include "Subsystems.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"
#include "Renderer.h"

void Subsystems_Initialize(void)
{
	// Make sure we are shutting
	atexit(Subsystems_Shutdown);

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("ERROR: SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Linear texture filtering not enabled!\n");
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("ERROR: SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		exit(1);
	}

}

void Subsystems_Shutdown(void)
{
	if (renderer)
		Renderer_Destroy();

	if (window)
		Window_Destroy();

	IMG_Quit();
	SDL_Quit();
}