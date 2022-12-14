#pragma once

#include "Sprite.h"
#include "TileMap.h"

class Projectile
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl, posProjectile;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};

