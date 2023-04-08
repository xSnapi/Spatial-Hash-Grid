#include "Application.hpp"

#include "Renderer.hpp"

#include "SFML/Graphics.hpp"

#include "Global Variables.hpp"

Application* Application::Instance = nullptr;

float Application::m_deltaTime = 0.0f;

Application::Application() {
	Instance = this;

	CreateWindow();
	InitRenderer();
	CreateCamera();

	m_simulation = new Simulation;
}

Application::~Application() {
	delete m_simulation;
}

void Application::Run() {
	while (m_running) {
		HandleEvents();

		Update();

		m_window.setView(MainCamera.GetView());

		Render();

		m_deltaTime = m_deltaClock.restart().asSeconds();
	}
}

void Application::Shutdown() {
	m_running = false;
}

void Application::Update() {
	UpdateCamera();
	m_simulation->Update();
}

void Application::Render() {
	m_window.clear(sf::Color(28, 34, 43, 255));

	m_simulation->Render();

	m_window.display();
}

void Application::CreateWindow() {
	sf::VideoMode mode;

	mode.width  = 1600;
	mode.height = 900;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	m_window.create(mode, "Spatial Hash Grid", sf::Style::Close, settings);
	m_window.setFramerateLimit(144);

	BOUNDS_POSITION = sf::Vector2f(800.0f, 450.0f);
}

void Application::InitRenderer() {
	Renderer.Init(m_window);
}

void Application::HandleEvents() {
	sf::Event e;

	while (m_window.pollEvent(e)) {
		switch (e.type) {
			case sf::Event::Closed:
				Shutdown();
				break;
			case sf::Event::MouseWheelScrolled:
				UpdateCameraScale(e.mouseWheelScroll.delta);
				break;
		}
	}
}

void Application::CreateCamera() {
	MainCamera.Create(WINDOW_SIZE / 2.0f, BOUNDS_SIZE * 2.0f);
}

void Application::UpdateCamera() {
	static sf::Vector2f mousePoint = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		mousePoint = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2f diff(mousePoint - m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));

		sf::Vector2f offset(MainCamera.GetCenter() + diff);

		MainCamera.SetCenter(offset);
	}
}

void Application::UpdateCameraScale(float delta) {
	float scale = delta > 0.0f ? 0.95f : 1.05f;

	MainCamera.OffsetScale(scale);
}
