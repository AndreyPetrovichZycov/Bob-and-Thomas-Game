#include "LevelManager.h"
#include "TextureHolder.h"
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>


using namespace sf;
using namespace std;


int** LevelManager::nextLevel(VertexArray& rVaLevel) {
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	m_CurrentLevel++;

	if (m_CurrentLevel > NumLevels) {
		m_CurrentLevel = 1;
		m_TimeModifier -= 0.1f;
	}

	string levelToLoad;
	switch (m_CurrentLevel)
	{
	case 1:
		levelToLoad = "levels/level1.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 100;
		m_BaseTimeLimit = 30.0f;
		break;
	case 2:
		levelToLoad = "levels/level2.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 3600;
		m_BaseTimeLimit = 100.0f;
		break;
	case 3:
		levelToLoad = "levels/level3.txt";
		m_StartPosition.x = 1250;
		m_StartPosition.y = 0;
		m_BaseTimeLimit = 30.0f;
		break;
	case 4:
		levelToLoad = "levels/level4.txt";
		m_StartPosition.x = 50;
		m_StartPosition.y = 200;
		m_BaseTimeLimit = 50.0f;
		break;
	}

	ifstream inputFile(levelToLoad);
	string s;
	// Count the number of rows in the file
	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}
	// Store the length of the rows
	m_LevelSize.x = s.length();

	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	// Prepare the 2D array to hold the int values from the file
	int** arrayLevel = new int* [m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		// Add a new array into each array element
		arrayLevel[i] = new int[m_LevelSize.x];
	}


	string row;
	int y = 0;

	while (inputFile >> row) {
		for (int x = 0; x < row.length(); x++) {
			const char val = row[x];
			arrayLevel[y][x] = atoi(&val);
		}
		y++;
	}

	inputFile.close();


	rVaLevel.setPrimitiveType(Quads);
	rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);

	int CurrentVertex = 0;

	for (int x = 0; x < m_LevelSize.x; x++) {
		for (int y = 0; y < m_LevelSize.y; y++) {
			rVaLevel[CurrentVertex + 0].position = Vector2f(x * TileSize, y * TileSize);
			rVaLevel[CurrentVertex + 1].position = Vector2f(x * TileSize + TileSize, y * TileSize);
			rVaLevel[CurrentVertex + 2].position = Vector2f(x * TileSize + TileSize, y * TileSize + TileSize);
			rVaLevel[CurrentVertex + 3].position = Vector2f(x * TileSize, y * TileSize + TileSize);

			int VerticalOffset = arrayLevel[y][x] * TileSize;

			rVaLevel[CurrentVertex + 0].texCoords = Vector2f(0, 0+VerticalOffset);
			rVaLevel[CurrentVertex + 1].texCoords = Vector2f(TileSize, 0+VerticalOffset);
			rVaLevel[CurrentVertex + 2].texCoords = Vector2f(TileSize, TileSize+VerticalOffset);
			rVaLevel[CurrentVertex + 3].texCoords = Vector2f(0, TileSize+VerticalOffset);

			CurrentVertex += VERTS_IN_QUAD;
		}
	}

	return arrayLevel;
}


Vector2i LevelManager::getLevelSize()
{
	return m_LevelSize;
}

int LevelManager::getCurrentLevel()
{
	return m_CurrentLevel;
}

float LevelManager::getTimeLimit()
{
	return m_BaseTimeLimit * m_TimeModifier;
}

Vector2f LevelManager::getStartPosition()
{
	return m_StartPosition;
}
