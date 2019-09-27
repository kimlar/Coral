@echo off

cl -O2 -MT main.c Application.c Subsystems.c Timer.c Keyboard.c Mouse.c Window.c Renderer.c Camera.c ImageLoader.c Game.c Player.c World.c Tileset.c Tile.c -Fe"Game.exe" -I"SDL2/include" -I"SDL2_image/include" -link -LIBPATH:"SDL2/lib/x64" -LIBPATH:"SDL2_image/lib/x64" SDL2.lib SDL2main.lib SDL2_image.lib -SUBSYSTEM:CONSOLE
