#pragma once

class Bub;
#include "Command.h"
namespace PC
{
	class GoDown :public AxisCommand
	{
	public:
		GoDown(Bub* bub) :m_pBub(bub) {}
		void execute(float elapsedSec,float axisValue) override;
	private:
		Bub* m_pBub = nullptr;
	};
	
	class Jump :public ButtonCommand
	{
	public:
		Jump(Bub* bub) :m_pBub(bub) {}
		void execute(float elapsedSec) override;
	private:
		Bub* m_pBub = nullptr;
	};

	

	class MoveHorizontal :public AxisCommand
	{
	public:
		MoveHorizontal(Bub* bub) :m_pBub(bub) {}
		void execute(float elapsedSec, float axisValue) override;

	private:
		Bub* m_pBub = nullptr;
	};

	class ShootBubble :public ButtonCommand
	{
	public:
		ShootBubble(Bub* bub) :m_pBub(bub) {}
		void execute(float elapsedSec) override;

	private:
		Bub* m_pBub = nullptr;
	};
}
