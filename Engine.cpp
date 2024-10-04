#include "Engine.h"


Engine::Engine() {
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	//m_Window.create(VideoMode(resolution.x, resolution.y),"Thomas was late", Style::Fullscreen);

	m_Window.create(VideoMode(resolution.x, resolution.y), "Game", Style::Resize);

	// Initialize the full screen view
	m_MainView.setSize(resolution);
	m_HudView.reset(FloatRect(0, 0, resolution.x, resolution.y));

	// Initialize the split-screen Views
	//отображение левого и правого экрана
	m_LeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
	m_RightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

	//отображение левого и правого задника
	m_BGLeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
	m_BGRightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

	//может ли эта графическая карта использовать шейдеры
	if (!sf::Shader::isAvailable())
	{
		// Time to get a new PC
		m_Window.close();
	}

	m_BackgroundTexture = TextureHolder::GetTexture("graphics/background.png");
	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);


	m_TextureTiles = TextureHolder::GetTexture("graphics/tiles_sheet.png");

}


void Engine::run()
{
	// Timing 
	Clock clock;
	while (m_Window.isOpen())
	{
		Time dt = clock.restart();

		// Update the total game time
		m_GameTimeTotal += dt;

		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		// Call each part of the game loop in turn
		input();
		update(dtAsSeconds);
		draw();
	}
}


