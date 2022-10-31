#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Projectile.h"
#include "Game.h"



void Projectile::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Projectile.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(69, 18), glm::vec2(1., 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posProjectile.x), float(tileMapDispl.y + posProjectile.y)));

}

void Projectile::update(int deltaTime)
{
	sprite->update(deltaTime);
	posProjectile += 5;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posProjectile.x), float(tileMapDispl.y + posProjectile.y)));
}

void Projectile::render()
{
	sprite->render();
}

void Projectile::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Projectile::setPosition(const glm::vec2& pos)
{
	posProjectile = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posProjectile.x), float(tileMapDispl.y + posProjectile.y)));
}