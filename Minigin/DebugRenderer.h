#pragma once
struct Color;
class Camera;
class DebugRenderer
{
public:
	static void DrawLine(glm::vec2 p1, glm::vec2 p2, Color color);

	static void DrawPoint(glm::vec2 pos);
	static void SetCamera(Camera* cam);
private:
	static Camera *m_pCamera;
};

