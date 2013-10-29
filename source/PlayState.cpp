/*
 *  PlayState.cpp
 *  Normal "play" state
 *
 *  Created by Marcelo Cohen on 08/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 */

#include <iostream>
#include <cmath>
#include "include/Game.h"
#include "include/PlayState.h"
#include "include/InputManager.h"
#include "include/TextureManager.h"

#define FLOOR 352

PlayState PlayState::m_PlayState;

using namespace std;

void PlayState::init()
{

    im = cgf::InputManager::instance();

    im->addKeyInput("left",  sf::Keyboard::A);
    im->addKeyInput("right", sf::Keyboard::D);
    im->addKeyInput("up",    sf::Keyboard::W);
    im->addKeyInput("down",  sf::Keyboard::S);
    im->addKeyInput("run",   sf::Keyboard::J);
    im->addKeyInput("jump",  sf::Keyboard::K);
    im->addKeyInput("quit",  sf::Keyboard::Escape);

	map = new tmx::MapLoader("data/maps");
	map->Load("simple.tmx");

	/* Loading background */
	cgf::TextureManager *tm = cgf::TextureManager::getInstance();
	sf::Texture* tex = tm->findTexture((char *)"data/imgs/bg_simple.png");
	if (tex == NULL) {
		cout << "PlayState: Init: could not find the texture for the background." << endl;
		exit(EXIT_FAILURE);
	}
	bg = new sf::Sprite(*tex);

	/* Creates Player */
	player = new Player(0, 0);

    cout << "PlayState: Init" << endl;
}

void PlayState::cleanup()
{
	delete(map);
	delete(bg);
	delete(player);
    cout << "PlayState: Clean" << endl;
}

void PlayState::pause()
{
    cout << "PlayState: Paused" << endl;
}

void PlayState::resume()
{
    cout << "PlayState: Resumed" << endl;
}

void PlayState::handleEvents(cgf::Game* game)
{
    sf::Event event;
    sf::RenderWindow* screen = game->getScreen();

    while (screen->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            game->quit();

		if(event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Space)
				game->toggleStats();
		}
    }

    if(im->testEvent("quit"))
        game->quit();

	player->setXDirection(PLAYER_H_NONE);
	if(im->testEvent("left"))
		player->setXDirection(PLAYER_H_LEFT);
	if(im->testEvent("right"))
		player->setXDirection(PLAYER_H_RIGHT);

	player->setJumpPressed(im->testEvent("jump"));
	player->setRunning(im->testEvent("run"));

}

bool PlayState::isPlayerOnTheGround() {
	return player->getY() >= FLOOR;
}

void PlayState::update(cgf::Game* game)
{
	player->setOnTheGround(isPlayerOnTheGround());
	player->update((float) game->getUpdateInterval());

	/* check collisions */
	player->setPosition(player->getX(), fmin(FLOOR, player->getY()));
}

void PlayState::draw(cgf::Game* game)
{
    sf::RenderWindow* screen = game->getScreen();
	screen->draw(*bg);
	map->Draw(*screen);
	player->draw(screen);
}
