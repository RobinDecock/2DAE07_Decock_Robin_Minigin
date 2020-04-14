#pragma once
#include "GameObject.h"
#include "vec2.hpp"
#include "mat4x4.hpp"
#include "GeneralStructs.h"
class Camera :public GameObject
{
public:
	Camera();
	void  Initialize()override;
	void Draw() override;
	glm::mat4 GetViewMatrix()const;
	glm::mat4  GetProjectionMatrix()const;
	glm::vec2 ConvertToWorldSpace(glm::vec2 pos);
	glm::vec2 ConvertToScreenSpace(glm::vec2 pos);
	void SetOrthoSize(int2 size) { ortho = size; }
	int2 GetOrthoSize() { return ortho; }
private:
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	int2 ortho = int2(256, 240);
	int2 windowSize;
};
