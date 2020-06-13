#pragma once


	class ButtonCommand
	{
	public:
		virtual ~ButtonCommand() = default;
		virtual void execute(float elapsedSec) = 0;
	};

	class AxisCommand
	{
	public:
		virtual ~AxisCommand() = default;
		virtual void execute(float elapsedSec, float axisValue) = 0;
	};

