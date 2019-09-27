#include "Game.h"
#include "Renderer.h"
#include "Window.h"
#include "Timer.h"
#include "Keyboard.h"
#include "Player.h"
#include "World.h"
#include "Camera.h"


void Game_Start(void)
{
	Camera_Create();
	World_Create();
	Player_Create();
}

void Game_Exit(void)
{
	Player_Destroy();
	World_Destroy();
}

void Game_Update(void)
{
	//posX += velX * (float)dt;
	//posY += velY * (float)dt;
	//
	//if (posX > (window_width - boxSizeW) || posX < 0)
	//{
	//	velX = -velX;
	//}
	//if (posY > (window_height - boxSizeH) || posY < 0)
	//{
	//	velY = -velY;
	//}		

	Camera_Update();
	Player_Update();
}

void Game_Render(void)
{
	World_Render();
	Player_Render();
}