#pragma once


	class ButtonCommand
	{
	public:
		virtual ~ButtonCommand() = default;
		virtual void Execute(float elapsedSec) = 0;
	};

	class AxisCommand
	{
	public:
		virtual ~AxisCommand() = default;
		virtual void Execute(float elapsedSec, float axisValue) = 0;
	};

