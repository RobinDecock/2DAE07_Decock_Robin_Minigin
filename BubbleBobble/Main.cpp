// BubbleBobble.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//
#pragma comment(lib,"xinput.lib")

// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "BubbleBobble.h"
#include "Minigin.h"

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[])
{
#pragma warning( pop )

	Minigin engine;
	engine.m_pProject = new BubbleBobble();
	engine.Run();
	return 0;
}