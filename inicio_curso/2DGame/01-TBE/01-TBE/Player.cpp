#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define SCREEN_X 30
#define SCREEN_Y 30


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	texProgram = shaderProgram;
	spritesheet.loadFromFile("images/Submarine.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(97, 48), glm::vec2(1., 0.33), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.66f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));

	// sprite->setAnimationSpeed(MOVE_LEFT, 8);
	// sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	// sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	// sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	// sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	// sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	// sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
	// sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	cooldown = 0;
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		// if(sprite->animation() != MOVE_LEFT)
			// sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(97, 48)))
		{
			posPlayer.x += 2;
		}
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		posPlayer.x += 2;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(97, 48)))
		{
			posPlayer.x -= 2;
		}
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		posPlayer.y -= 2;
		if (map->collisionMoveUp(posPlayer, glm::ivec2(97, 48)))
		{
			posPlayer.y += 2;
		}
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		posPlayer.y += 2;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(97, 48)))
		{
			posPlayer.y -= 2;
		}
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_F1) && cooldown <= 0) {
		Projectiles.push_back(new Projectile());
		Projectiles[Projectiles.size()-1]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		Projectiles[Projectiles.size() - 1]->setPosition(glm::vec2(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y))));
		Projectiles[Projectiles.size() - 1]->setTileMap(map);
		cooldown = 10;
	}
	cooldown -= 1;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
	for (int i = 0; i < Projectiles.size(); ++i) {
		Projectiles[i]->render();
	}
}

void Player::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




