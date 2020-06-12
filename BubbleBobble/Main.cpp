// BubbleBobble.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//
#pragma comment(lib,"xinput.lib")
#include <iostream>
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>

#include "BubbleBobble.h"
#include "Minigin.h"

int main(int argc, char* args[])
{
	Minigin engine;

	engine.m_pProject = new BubbleBobble();
	engine.Run();

	return 0;
}
