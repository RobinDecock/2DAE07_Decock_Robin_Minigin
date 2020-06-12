#pragma once
#include <thread>
#include <vector>

class b2World;

struct Rectf;
class Camera;
class GameObject;
class Renderer;
class b2DebugDraw;
class b2CContactListener;

struct b2World_ext
{
	b2World *world = nullptr;
	bool isLocked = true;
};


class GameScene
{
public:
	GameScene();

	void RootInitialize();
	void RootDraw()const ;

	void ThreadUpdate(float elapsedSec);
	void ThreadUpdatePhysics(float elapsedSec);
	
	void RootUpdate(float elapsedSec);

	void Add(GameObject* obj);
	void Remove(GameObject* gameObject);
	

	virtual ~GameScene();
	Camera* GetCamera() { return m_pActiveCam; }
	void SetCamera(Camera * cam);
	b2World_ext GetPhysicsProxy() { return m_pPhysicsProxy; }
	b2DebugDraw *GetDebugDraw() const{ return m_B2DebugDraw; }

	void RayCast(b2RayCastCallback* callback, const b2Vec2& point1, const b2Vec2& point2);
	//CollisionManager& GetCollisionManager() { return collisionManager; }
	//TextureManager* GetTextureManager() { return textureManager; }
protected:

	//* Virtual Functions *//
	virtual void Initialize() = 0;
	virtual void Update(float elapsedSec) {}
	virtual void PhysicsUpdate(float elapsedSec) {}
	virtual void Draw()const {}
	//*                   *//

	bool m_IsInitialized = false;
	b2DebugDraw *m_B2DebugDraw;
	b2CContactListener *m_pContactListener;
	b2World_ext m_pPhysicsProxy;
	int idCount = 0;
	std::vector<GameObject*> m_pGameObjects{};

	std::vector<GameObject*> m_pToAdd{};
	std::vector<GameObject*> m_pToDelete{};
	Camera* m_pActiveCam = nullptr;

	GameObject* FPSMonitor = nullptr;

	std::thread physicsThread;
	std::thread updateThread;
};
