#pragma once
#include "GameObject.h"

class Texture2D;
class ColorBlock :public GameObject
{
public:
	ColorBlock(int blockId);
	~ColorBlock() override;
protected:
	void Initialize() override;
private:
	int m_BlockId;
};

