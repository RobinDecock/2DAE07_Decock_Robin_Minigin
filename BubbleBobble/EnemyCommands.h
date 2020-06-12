#pragma once
class Maita;
class BaseEnemy;
#include "Command.h"
namespace EC
{
	class MoveHorizontal : public AxisCommand
	{
	public:
		MoveHorizontal(BaseEnemy* enemy) :m_pEnemy(enemy) {}
		void execute(float elapsedSec, float axisValue) override;
	private:
		BaseEnemy* m_pEnemy = nullptr;
	};
	class Jump : public ButtonCommand
	{
	public:
		Jump(BaseEnemy* enemy) :m_pEnemy(enemy) {}
		void execute(float elapsedSec) override;
	private:
		BaseEnemy* m_pEnemy = nullptr;
	};
	class Shoot : public ButtonCommand
	{
	public:
		Shoot(Maita* enemy) :m_pEnemy(enemy) {}
		void execute(float elapsedSec) override;
	private:
		Maita* m_pEnemy = nullptr;
	};

	class GoDown :public AxisCommand
	{
	public:
		GoDown(BaseEnemy* enemy) :m_pEnemy(enemy) {}
		void execute(float elapsedSec, float axisValue) override;
	private:
		BaseEnemy* m_pEnemy = nullptr;
	};

}
