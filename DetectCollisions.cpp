#include "Engine.h"

bool Engine::detectCollisions(PlayableCharacter& character) {
	bool reachedGoal = false;
	FloatRect detectionZone = character.getPosition();

	FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	int startX = static_cast<int>(detectionZone.left / TILE_SIZE) - 1;
	int startY = static_cast<int>(detectionZone.top / TILE_SIZE) - 1;
	int EndX = static_cast<int>(detectionZone.left / TILE_SIZE) + 2;
	int EndY = static_cast<int>(detectionZone.top / TILE_SIZE) + 3;


	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	if (EndX >= m_LM.getLevelSize().x) EndX = m_LM.getLevelSize().x;
	if (EndY >= m_LM.getLevelSize().y) EndY = m_LM.getLevelSize().y;

	FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);

	if (!character.getPosition().intersects(level))
	{
		// respawn the character
		character.spawn(m_LM.getStartPosition(), GRAVITY);
	}

	for (int x = startX; x < EndX; x++)
	{
		for (int y = startY; y < EndY; y++)
		{
			// Initialize the starting position of the current block
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;
			// Has character been burnt or drowned?
			// Use head as this allows him to sink a bit
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (character.getHead().intersects(block))
				{
					character.spawn(m_LM.getStartPosition(), GRAVITY);
					// Which sound should be played?
					if (m_ArrayLevel[y][x] == 2)// Fire, ouch!
					{
						// Play a sound
					}
					else // Water
					{
						// Play a sound
					}
				}
			}

			// Is character colliding with a regular block
			if (m_ArrayLevel[y][x] == 1)
			{
				if (character.getRight().intersects(block))
				{
					character.stopRight(block.left);
				}
				else if (character.getLeft().intersects(block))
				{
					character.stopLeft(block.left);
				}
				if (character.getFeet().intersects(block))
				{
					character.stopFalling(block.top);
				}
				else if (character.getHead().intersects(block))
				{
					character.stopJump();
				}
			}

			// More collision detection here once we have 
			// learned about particle effects
			// Has the character reached the goal?
			if (m_ArrayLevel[y][x] == 4)
			{
				// Character has reached the goal
				reachedGoal = true;
			}
		}
	}
	return reachedGoal;
}