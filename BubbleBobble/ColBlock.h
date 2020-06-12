#pragma once
#include "GameObject.h"

class Texture2D;
class ColBlock:public GameObject
{
public:
	ColBlock(int blockId);
	~ColBlock() override;
protected:
	void Initialize() override;

private:
	int m_BlockId;
};

