#pragma once

#include "Simulation.hpp"

#include "SFML/Graphics/RenderWindow.hpp"

#include "Camera.hpp"

struct TimeSteps;

inline Camera MainCamera;

class Application {
public:
	Application();
	~Application();

	static Application* Instance;

	void Run();
	void Shutdown();

private:
	sf::RenderWindow m_window;

	Simulation* m_simulation = nullptr;

	sf::Clock m_deltaClock;

	static float m_deltaTime;

	bool m_running = true;

	void Update();
	void Render();

	void CreateCamera();
	void UpdateCamera();
	void UpdateCameraScale(float delta);

	void CreateWindow();
	void InitRenderer();
	void HandleEvents();

	friend struct TimeSteps;
};
