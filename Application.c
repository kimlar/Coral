#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "DataTypes.h"
#include "SubSystems.h"
#include "Window.h"
#include "Renderer.h"
#include "Timer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Game.h"

void RunApplication(void)
{
	Subsystems_Initialize();
	//Window_Create(1280, 720, false);
	Window_Create(1280, 720, true);
	//Window_Create(2560, 1440, false);
	//Window_Create(2560, 1440, true);	
	Timer_Initialize();
	Game_Start();

	double fpsTime = 0.0;
	u32 fpsCount = 0;

	u8 running = 1;
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
				case SDL_QUIT:
				{
					running = 0;
				} break;

				case SDL_WINDOWEVENT:
				{
					Window_Event(&e);
				} break;

				case SDL_KEYDOWN:
				case SDL_KEYUP:
				{
					if (e.key.keysym.mod & KMOD_LALT && e.key.keysym.sym == SDLK_RETURN)
					{
						// TODO(kim): Switch beteen fullscreen and window mode
					}
					Keyboard_Event(&e);
				} break;

				case SDL_MOUSEMOTION:
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEWHEEL:
				{
					Mouse_Event(&e);
				} break;
			}
		}

		Timer_Update();

		fpsTime += dt;
		fpsCount++;
		if (fpsTime >= 1.0)
		{
			fpsTime = 0.0;
			printf("FPS: %d\n", fpsCount);
			//printf("Mouse: x=%d y=%d left=%d middle=%d right=%d wheel=%d\n", mouse_x, mouse_y, mouse_button_left, mouse_button_middle, mouse_button_right, mouse_wheel_y);
			//printf("Keyboard: up=%d down=%d left=%d right=%d\n", IsKeyUp, IsKeyDown, IsKeyLeft, IsKeyRight);
			fpsCount = 0;
		}
		
		Game_Update();

		if (window_minimized)
		{
			SDL_Delay(1);
		}
		else
		{
			Renderer_Begin();
			Game_Render();
			Renderer_End();
		}
	}

	Game_Exit();
	Window_Destroy();
	Subsystems_Shutdown();
}