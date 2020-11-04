#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Hero.h"
#include "Enemy.h"

using namespace sf;
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")


const int H = 17;
const int W = 150;
float offsetX = 0, offsetY = 0;

String TileMap[17] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
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

String Level2_TileMap[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B         0000                BBBB     B",
"B                                B     B",
"BBB                              B     B",
"B              BB                BB    B",
"B              BB                      B",
"B    B         BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};
RenderWindow *window;
sf::Clock *clocks;
Hero    *Mario;
Enemy   *enemy;
Texture *tileSet;
Sprite  *tile;
Sound   *sound;
SoundBuffer *buffer;

void InitGame()
{
	 

	tileSet = new Texture();
	Mario   = new Hero(*tileSet);
	enemy   = new Enemy();
	tile    = new Sprite(*tileSet); 
     buffer = new SoundBuffer();
      sound = new Sound(*buffer);
	  clocks = new sf::Clock();

    tileSet->loadFromFile("Mario_tileset.png");
	enemy->set(*tileSet, 48 * 16, 13 * 16);

	
	buffer->loadFromFile("Jump.ogg");
	
	Music music;
	music.openFromFile("Mario_Theme.ogg");
	music.setLoop(true);
	music.play();

	Texture menu_texture1, menu_texture2, menu_texture3, about_texture;
	menu_texture1.loadFromFile("111.png");
	menu_texture2.loadFromFile("222.png");
	menu_texture3.loadFromFile("333.png");
	about_texture.loadFromFile("about.png");
	Sprite menu1(menu_texture1), menu2(menu_texture2), menu3(menu_texture3), about(about_texture);
	bool Menu = 1;
	int MenuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);

	/////меню
	while (Menu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		MenuNum = 0;
		window->clear(Color(0, 0, 0));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(*window))) { menu1.setColor(Color::Yellow); MenuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(*window))) { menu2.setColor(Color::Yellow); MenuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(*window))) { menu3.setColor(Color::Yellow); MenuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (MenuNum == 1) Menu = false;
			if (MenuNum == 2) { window->draw(about); window->display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (MenuNum == 3) { window->close(); Menu = false; }

		}


		window->draw(menu1);
		window->draw(menu2);
		window->draw(menu3);

		window->display();
	}
	////////////////
}

int main()
{
	InitGame();

	window  = new RenderWindow(VideoMode(400, 250), "SFML works!");

	while (window->isOpen())
	{

		float time = clocks->getElapsedTime().asMicroseconds();
		clocks->restart();

		time = time / 500;  // здесь регулируем скорость игры

		if (time > 20) time = 20;

		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}


		if (Keyboard::isKeyPressed(Keyboard::Left))    Mario->dx = -0.1;
		if (Keyboard::isKeyPressed(Keyboard::Right))    Mario->dx = 0.1;
		//if (Keyboard::isKeyPressed(Keyboard::Up))	if (Mario.onGround) { Mario.dy = -0.27; Mario.onGround = false;  sound.play(); }
		if (Keyboard::isKeyPressed(Keyboard::Space)) if (Mario->onGround) { Mario->dy = -0.27; Mario->onGround = false;  sound->play(); }



		Mario->update(time);
		enemy->update(time);

		// Если марио атакует
		if (Mario->m_rect.intersects(enemy->rect))
		{
			if (enemy->life) {
				if (Mario->dy > 0) 
				{ 
					enemy->dx = 0; Mario->dy = -0.2; enemy->life = false; enemy->sprite.setColor(Color::Blue);
				} //добавить убрать врага спрайт
				else Mario->sprite.setColor(Color::Red); // иначе сам погибает
			}
		}
		

		if (Mario->m_rect.left > 200) offsetX = Mario->m_rect.left - 200;           //смещение




		window->clear(Color(107, 140, 255));

		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'P')  tile->setTextureRect(IntRect(143 - 16 * 3, 112, 16, 16));

				if (TileMap[i][j] == 'k')  tile->setTextureRect(IntRect(143, 112, 16, 16));

				if (TileMap[i][j] == 'c')  tile->setTextureRect(IntRect(143 - 16, 112, 16, 16));

				if (TileMap[i][j] == 't')  tile->setTextureRect(IntRect(0, 47, 32, 95 - 47));

				if (TileMap[i][j] == 'g')  tile->setTextureRect(IntRect(0, 16 * 9 - 5, 3 * 16, 16 * 2 + 5));

				if (TileMap[i][j] == 'G')  tile->setTextureRect(IntRect(145, 222, 222 - 145, 255 - 222));

				if (TileMap[i][j] == 'd')  tile->setTextureRect(IntRect(0, 106, 74, 127 - 106));

				if (TileMap[i][j] == 'w')  tile->setTextureRect(IntRect(99, 224, 140 - 99, 255 - 224));

				if (TileMap[i][j] == 'r')  tile->setTextureRect(IntRect(143 - 32, 112, 16, 16));

				if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0')) continue;

				tile->setPosition(j * 16 - offsetX, i * 16 - offsetY);
				
			}
		window->draw(*tile);


		window->draw(Mario->sprite);
		window->draw(enemy->sprite);

		window->display();
	}

	return 0;
}



