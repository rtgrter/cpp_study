#pragma once
#include <graphics.h>
#include <string>
#include <vector>

#include "Player.h"
#include "Animation.h"

//玩家类
class Player
{
public:
	const int FRAME_SPEED = 3;		//玩家移动速度
	const int FRAME_WIDTH = 80;		//玩家宽度
	const int FRAME_HEIGHT = 80;	//玩家高度
public:
	Player();

	~Player();

	void ProcessEvent(const ExMessage& msg);

	void Move();

	void Draw(int delta);

	const POINT& GetPosition() const;

private:
	const int SHADOW_WIDTH = 32;	//阴影宽度
private:
	IMAGE img_shadow;		//玩家阴影
	Animation* anim_left;
	Animation* anim_right;
	POINT position = { 500,500 };		//玩家初始坐标
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;
};
