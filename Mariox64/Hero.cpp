#include "pch.h"
#include "Hero.h"

Hero::~Hero()
{
}

Hero::Hero()
{

}
Hero::Hero(float offsetX_,float offsetY_)
{
	offsetX = offsetX_; offsetY = offsetY_;
}
Hero::Hero(Texture &image)
{
	sprite.setTexture(image);
	m_rect = FloatRect(100, 180, 16, 16);

	dx = dy = 0.1;
	currentFrame = 0;
}
void Hero::update(float time)
{

	m_rect.left += dx * time;
	Collision(0);


	if (!onGround) dy = dy + 0.0005*time;
	m_rect.top += dy * time;
	onGround = false;
	Collision(1);


	currentFrame += time * 0.005;
	if (currentFrame > 3) currentFrame -= 3;


	if (dx > 0) sprite.setTextureRect(IntRect(112 + 31 * int(currentFrame), 144, 16, 16));
	if (dx < 0) sprite.setTextureRect(IntRect(112 + 31 * int(currentFrame) + 16, 144, -16, 16));


	sprite.setPosition(m_rect.left - offsetX, m_rect.top - offsetY);

	dx = 0;
}


void Hero::Collision(int num)
{

	for (int i = m_rect.top / 16; i < (m_rect.top + m_rect.height) / 16; i++)
		for (int j = m_rect.left / 16; j < (m_rect.left + m_rect.width) / 16; j++)
		{
			if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't'))
			{
				if (dy > 0 && num == 1)
				{
					m_rect.top = i * 16 - m_rect.height;  dy = 0;   onGround = true;
				}
				if (dy < 0 && num == 1)
				{
					m_rect.top = i * 16 + 16;   dy = 0;
				}
				if (dx > 0 && num == 0)
				{
					m_rect.left = j * 16 - m_rect.width;
				}
				if (dx < 0 && num == 0)
				{
					m_rect.left = j * 16 + 16;
				}
			}

			if (TileMap[i][j] == 'c') {
				// TileMap[i][j]=' '; 
			}
		}

}