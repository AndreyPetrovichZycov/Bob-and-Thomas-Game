#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Bob.h"
#include "Thomas.h"
#include "LevelManager.h"

using namespace sf;


class Engine {
private:
	TextureHolder th;

	Thomas m_Thomas;
	Bob m_Bob;

	LevelManager m_LM;


	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	// ���� ����������
	const int GRAVITY = 300;

	// ������ 
	RenderWindow m_Window;

	// �����
	View m_MainView;
	View m_LeftView;
	View m_RightView;

	// Three views for the background
	View m_BGMainView;
	View m_BGLeftView;
	View m_BGRightView;
	View m_HudView;

	// Declare a sprite and a Texture 
	// 
	// for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;

	// Is the game currently playing?
	bool m_Playing = false;

	// Is character 1 or 2 the current focus?
	bool m_Character1 = true;

	// Start in full screen (not split) mode
	bool m_SplitScreen = false;

	// Time left in the current level (seconds)
	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;

	// Is it time for a new/first level?
	bool m_NewLevelRequired = true;

	VertexArray m_VALevel;

	int** m_ArrayLevel = nullptr;

	Texture m_TextureTiles;
	// Private functions for internal use only
	void input();

	void update(float dtAsSeconds);

	void draw();

	void loadLevel();

	bool detectCollisions(PlayableCharacter& character);
public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();
};
