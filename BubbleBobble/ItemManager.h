#pragma once
#include <vector>

#include "Singleton.h"
class GameScene;

class BaseItem;

class ItemManager final : public Singleton<ItemManager>
{
public:
	ItemManager(GameScene* scene);
	void AddItem(BaseItem* item);

	void RemoveItem(BaseItem* item);

	void Clear();
private:
	GameScene* m_pGameScene = nullptr;
	std::vector<BaseItem*> m_pItems;
};

