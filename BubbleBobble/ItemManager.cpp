#include "ProjectPCH.h"
#include "ItemManager.h"
#include "GameScene.h"
#include "BaseItem.h"
ItemManager::ItemManager(GameScene* scene)
{
	m_pGameScene = scene;
	m_pInstance = this;
}

void ItemManager::AddItem(BaseItem* item)
{
	m_pItems.push_back(item);
}

void ItemManager::RemoveItem(BaseItem* item)
{
	for (unsigned int i = 0; i < m_pItems.size(); i++)
	{
		if (m_pItems[i] == item)
		{
			m_pItems.erase(m_pItems.begin());
			m_pGameScene->Remove(item);
			return;
		}
	}
}

void ItemManager::Clear()
{
	for (unsigned int i = 0; i < m_pItems.size(); i++)
	{
		m_pGameScene->Remove(m_pItems[i]);
	}
	m_pItems.clear();
}
