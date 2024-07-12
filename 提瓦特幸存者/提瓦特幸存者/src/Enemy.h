#pragma once
#include <graphics.h>
#include <string>
#include <vector>

#include "Animation.h"
#include "Player.h"
#include "Bullet.h"


//µ–»À¿‡
class Enemy
{
public:
	Enemy();

	bool CheckBulletCollision(const Bullet& bullet);

	bool CheckPlayerCollision(const Player& player);

	void Move(const Player& player);

	void Draw(int delta);

	void Hurt();

	bool CheckAlive();

	~Enemy();

private:
	const int SPEED = 2;
	const int FRAME_WIDTH = 80;
	const int FRAME_HEIGHT = 60;
	const int SHADOW_WIDTH = 48;

private:
	IMAGE img_shadow;
	Animation* anim_left;
	Animation* anim_right;
	POINT position = { 0,0 };
	bool facing_left = false;
	bool alive = true;

	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;
};
