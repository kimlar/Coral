#include "World.h"
#include <stdio.h>
#include <stdlib.h>
#include "Tile.h"
#include "Camera.h"
#include "Tileset.h"

void *WorldMemory;
//u32 WorldData[256][256];

u32 WorldWidth;
u32 WorldHeight;

void World_Create(void)
{
	World_Destroy();

	//World_Load("World1.dat"); // 8x8
	//World_Load("World2.dat"); // 16x16
	//World_Load("World3.dat"); // 32x32
	//World_Load("World4.dat"); // 64x64
	//World_Load("World5.dat"); // 128x128
	//World_Load("World6.dat"); // 256x256
	//World_Load("World6-rnd.dat"); // 256x256 randomized
	World_Load("World-tile-test.dat"); // 256x256
	Tileset_Load("GrassTiles-TempArt.png");
}

void World_Destroy(void)
{
	if (WorldMemory)
	{
		VirtualFree(WorldMemory, 0, MEM_RELEASE);
	}
	Tileset_Unload();
}

void World_Render(void)
{
	u32 *WorldStart = WorldMemory;
	u32 *WorldPtr = WorldMemory;

	//printf("Camera_Y: %d\n", Camera_Y);
	//WorldPtr += (Camera_Y / tile_size)*WorldHeight;
	for (u32 Y = 0; Y < ((Camera_Height / tile_size)+2); ++Y)
	{
		//WorldPtr += (Camera_X / tile_size);
		for (u32 X = 0; X < ((Camera_Width / tile_size)+1); ++X)
		{
			WorldPtr = WorldStart + WorldWidth*(Y + Camera_Y / tile_size) + (X + Camera_X / tile_size);
			//WorldPtr = WorldStart + (X + Camera_X / tile_size);
			//WorldPtr = 0;
			//u32 dataX = X;
			//u32 dataX = X + Camera_X / tile_size;
			//u32 dataY = Y + Camera_Y / tile_size;
			Tile_Render(X * tile_size - Camera_X % tile_size, Y*tile_size - Camera_Y % tile_size, *WorldPtr);
			//WorldPtr++;
			//Tile_Render(X * tile_size - Camera_X % tile_size, Y*tile_size - Camera_Y % tile_size, WorldData[dataY][dataX]);
			//Tile_Render(200 + X*tile_size + Camera_X, Y*tile_size, WorldData[Y][dataX]);
			//printf("%d ", WorldData[Y][X]);
		}
		//printf("\n");		
		//WorldPtr += WorldWidth - (Camera_X / tile_size) - 2;		
		//WorldPtr += WorldWidth;
	}
	//exit(1);


	/*
	//printf("Camera_Y: %d\n", Camera_Y);
	for (u32 Y = 0; Y < ((Camera_Height / tile_size)+2); ++Y)
	{
		for (u32 X = 0; X < ((Camera_Width / tile_size) + 1); ++X)
		{
			//u32 dataX = X;
			u32 dataX = X + Camera_X / tile_size;
			u32 dataY = Y + Camera_Y / tile_size;
			Tile_Render(X * tile_size - Camera_X % tile_size, Y*tile_size - Camera_Y % tile_size, WorldData[dataY][dataX]);
			//Tile_Render(200 + X*tile_size + Camera_X, Y*tile_size, WorldData[Y][dataX]);
			//printf("%d ", WorldData[Y][X]);
		}
		//printf("\n");
	}
	//exit(1);
	*/

	//if (Camera_X < 0)
	//	Camera_X = 0;

	//if (Camera_X < -(WorldWidth + tile_size))
	//	Camera_X = -(WorldWidth + tile_size);
	//if (Camera_X >(WorldWidth - tile_size))
	//	Camera_X = WorldWidth - tile_size;
	/*
	printf("Camera_X: %d\n", Camera_X);
	for (u32 Y = 0; Y < 16; ++Y)
	{
		for (u32 X = 0; X < ((Camera_Width/tile_size)+1); ++X)
		{
			//u32 dataX = X;
			u32 dataX = X + Camera_X / tile_size;
			Tile_Render(X * tile_size - Camera_X % tile_size , Y*tile_size, WorldData[Y][dataX]);
			//Tile_Render(200 + X*tile_size + Camera_X, Y*tile_size, WorldData[Y][dataX]);
			//printf("%d ", WorldData[Y][X]);
		}
		//printf("\n");
	}
	//exit(1);
	*/


	/*
	if (Camera_X < 0.0f)
		Camera_X = 0.0f;
	if (Camera_X > (WorldWidth-16))
		Camera_X = WorldWidth-16;
	printf("camera_x: %f\n", Camera_X);
	for (u32 Y = 0; Y < 16; ++Y)
	{
		for (u32 X = 0; X < 16*tile_size; X+=tile_size)
		{
			u32 dataX = X/tile_size + Camera_X;
			Tile_Render(200+X - Camera_X, Y*tile_size, WorldData[Y][dataX]);
			//printf("%d ", WorldData[Y][X]);
		}
		//printf("\n");
	}
	//exit(1);
	*/

	/*
	for (u32 Y = 0; Y < 4; ++Y)
	{
		for (u32 X = 0; X < 4; ++X)
		{			
			Tile_Render(X*tile_size, Y*tile_size, WorldData[Y][X]);
			//printf("%d ", WorldData[Y][X]);
		}
		//printf("\n");
	}
	//exit(1);
	*/

	/*
	u32 *WorldPtr = WorldMemory;

	for (u32 Y = 0; Y < WorldHeight; Y += tile_size)
	{
		for (u32 X = 0; X < WorldWidth; X += tile_size)
		{
			Tile_Render(Camera_X + X, Y-Camera_Y, *WorldPtr++);
		}
	}
	*/

	/*
	for (u32 Y = 0; Y < WorldHeight; ++Y)
	{
		for (u32 X = 0; X < WorldWidth; ++X)
		{
			Tile_Render(X, Y, *WorldPtr++);
		}
	}
	*/
}

void World_Load(char *file_path)
{
	FILE *filePtr;
	fopen_s(&filePtr ,file_path, "rb");
	if (filePtr == NULL)
	{
		printf("Cannot open file: %s\n", file_path);
		exit(1);
	}

	// Get world width (tiles)
	if (fread(&WorldWidth, sizeof(u32), 1, filePtr) != 1)
	{
		if (feof(filePtr))
		{
			printf("Premature end of file.\n");
			fclose(filePtr);
			exit(1);
		}
		else
		{
			printf("File read error.\n");
			fclose(filePtr);
			exit(1);
		}
	}

	// Get world height (tiles)
	if (fread(&WorldHeight, sizeof(u32), 1, filePtr) != 1)
	{
		if (feof(filePtr))
		{
			printf("Premature end of file.\n");
			fclose(filePtr);
			exit(1);
		}
		else
		{
			printf("File read error.\n");
			fclose(filePtr);
			exit(1);
		}
	}

	//WorldWidth = 4;
	//WorldHeight = 4;

	// Allocate memory for tile data
	u32 tile_count = (WorldWidth * WorldHeight);
	//printf("tile_count: %d\n", tile_count);
	WorldMemory = VirtualAlloc(0, (tile_count * sizeof(u32)), MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
	
	// Tile data
	//if (fread(WorldData, sizeof(u32), tile_count, filePtr) != tile_count)
	if (fread(WorldMemory, sizeof(u32), tile_count, filePtr) != tile_count)
	{
		if (feof(filePtr))
		{
			printf("Premature end of file.\n");
			fclose(filePtr);
			exit(1);
		}
		else
		{
			printf("File read error.\n");
			fclose(filePtr);
			exit(1);
		}
	}
	fclose(filePtr);
}