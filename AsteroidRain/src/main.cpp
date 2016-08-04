// Asteroid Rain Game as defined by Mediatonic
// Using the SFML C++ library
// All other files in this project are written by Nikolay Panayotov
// 2016

#include <windows.h>
#include "app.h"

// application entry point
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	App game_app;
	game_app.Run();
}