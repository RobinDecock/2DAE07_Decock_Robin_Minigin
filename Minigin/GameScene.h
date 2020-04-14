#pragma once
#include <vector>
class b2World;

struct Rectf;
class Camera;
class GameObject;
class Renderer;

class GameScene
{
public:
	GameScene();

	void RootInitialize();
	void RootDraw();
	void RootUpdate(float elapsedSec);

	void Add(GameObject* obj);
	void Remove(GameObject* gameObject, bool deleteObj = true);


	virtual ~GameScene();
	Camera* GetCamera() { return m_pActiveCam; }
	b2World *GetColWorld() {return m_pColWorld;	}
	//CollisionManager& GetCollisionManager() { return collisionManager; }
	//TextureManager* GetTextureManager() { return textureManager; }
protected:

	//* Virtual Functions *//
	virtual void Initialize() = 0;
	virtual void LateInitialize() = 0;
	virtual void Update(float elapsedSec) = 0;
	virtual void Draw() const = 0;
	//*                   *//


	
	b2World * m_pColWorld = nullptr;
	int idCount = 0;
	std::vector<GameObject*> m_pGameObjects;
	Camera* m_pActiveCam = nullptr;
};
