#pragma once
#include <map>

struct int2
{
	int2(int vx, int vy) : x(vx), y(vy)
	{
	}

	int2() : int2{0, 0}
	{
	}

	int x;
	int y;

	int2 operator+(int2 other)
	{
		return int2(this->x + other.x, this->y + other.y);
	}

	void operator+=(int2 other)
	{
		this->x += other.x;
		this->y += other.y;
	}
};

struct int4
{
	int4() : int4{ 0, 0,0,0 }
	{
	}

	
	int4(int vx, int vy, int vw, int vh) : x(vx), y(vy), w(vw), h(vh)
	{
	}

	int x;
	int y;
	int w;
	int h;
};


struct AnimData
{
	AnimData():RowsCols(), Src()
	{}
	
	int2 RowsCols;
	int4 Src;
};


struct Rectf
{
	Rectf(float vx, float vy, float vw, float vh) : x(vx), y(vy), w(vw), h(vh)
	{
	}

	float x;
	float y;
	float w;
	float h;
};

enum class Direction { Down, Left, Right, Up };


static std::map<Direction, int2> DirectionMap
{
	{Direction::Left, int2(-1, 0)},
	{Direction::Right, int2(1, 0)},
	{Direction::Up, int2(0, -1)},
	{Direction::Down, int2(0, 1)},
};
