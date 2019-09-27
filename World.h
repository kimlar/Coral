#pragma once
#include <windows.h> // need ?
#include "DataTypes.h"

extern void *WorldMemory;
//extern u32 WorldData[256][256];

extern u32 WorldWidth;
extern u32 WorldHeight;

extern void World_Create(void);
extern void World_Destroy(void);
extern void World_Render(void);

void World_Load(char *file_path);