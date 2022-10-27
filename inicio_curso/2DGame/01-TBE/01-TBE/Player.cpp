#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	HP3, HP2, HP1
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/Submarine.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(97, 48), glm::vec2(1., 0.33), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(HP3, 8);
	sprite->addKeyframe(HP3, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(HP2, 8);
	sprite->addKeyframe(HP2, glm::vec2(0.f, 0.33f));

	sprite->setAnimationSpeed(HP1, 8);
	sprite->addKeyframe(HP1, glm::vec2(0.f, 0.66f));

	// sprite->setAnimationSpeed(MOVE_LEFT, 8);
	// sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	// sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	// sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	// sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	// sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	// sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
	// sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));

	sprite->changeAnimation(HP1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

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

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
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




