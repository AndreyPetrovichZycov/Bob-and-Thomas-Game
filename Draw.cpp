#include "Engine.h"


void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear(Color::White);

	if (!m_SplitScreen)
	{
		// Switch to background view
		m_Window.setView(m_BGMainView);

		// Draw the background
		m_Window.draw(m_BackgroundSprite);

		// Switch to m_MainView
		m_Window.setView(m_MainView);

		m_Window.draw(m_VALevel, &m_TextureTiles);

		m_Window.draw(m_Thomas.getSprite());
		m_Window.draw(m_Bob.getSprite());

	}
	else
	{
		// Split-screen view is active
		
		// First draw Thomas' side of the screen
		
		// Switch to background view
		m_Window.setView(m_BGLeftView);
		// Draw the background
		m_Window.draw(m_BackgroundSprite);
		// Switch to m_LeftView
		m_Window.setView(m_LeftView);

		//draw Thomas
		m_Window.draw(m_Thomas.getSprite());

		//draw Bob
		m_Window.draw(m_Bob.getSprite());

		// Now draw Bob's side of the screen
		// Switch to background view
		m_Window.setView(m_BGRightView);

		// Draw the background
		m_Window.draw(m_BackgroundSprite);

		// Switch to m_RightView
		m_Window.setView(m_RightView);

		m_Window.draw(m_VALevel, &m_TextureTiles);


		m_Window.draw(m_VALevel, &m_TextureTiles);

		//draw Thomas
		m_Window.draw(m_Thomas.getSprite());
		//draw Bob
		m_Window.draw(m_Bob.getSprite());


	}
	// Draw the HUD
	// Switch to m_HudView
	m_Window.setView(m_HudView);


	// Show everything we have just drawn
	m_Window.display();
}
