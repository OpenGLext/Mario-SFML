#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Hero
{
public:
	float dx, dy;
	FloatRect m_rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;
	float offsetX = 0, offsetY = 0;
	sf::String TileMap[17] = {"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		"0                                                                                                                                                    0",
		"0                                                                                    w                                                               0",
		"0                   w                                  w                   w                                                                         0",
		"0                                      w                                       kk                                                                    0",
		"0                                                                             k  k    k    k                                                         0",
		"0                      c                                                      k      kkk  kkk  w                                                     0",
		"0                                                                       r     k       k    k                                                         0",
		"0                                                                      rr     k  k                                                                   0",
		"0                                                                     rrr      kk                                                                    0",
		"0               c    kckck                                           rrrr                                                                            0",
		"0                                      t0                           rrrrr                                                                            0",
		"0G                                     00              t0          rrrrrr            G                                                               0",
		"0           d    g       d             00              00         rrrrrrr                                                                            0",
		"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
		"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
		"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
};
	Hero(float offsetX_ = 0, float offsetY_ = 0);

	Hero();
	Hero(Texture &image);
	void Collision(int num);
	void update(float time);
	~Hero();
};

