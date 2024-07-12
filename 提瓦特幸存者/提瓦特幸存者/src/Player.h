#pragma once
#include <graphics.h>
#include <string>
#include <vector>

#include "Player.h"
#include "Animation.h"

//�����
class Player
{
public:
	const int FRAME_SPEED = 3;		//����ƶ��ٶ�
	const int FRAME_WIDTH = 80;		//��ҿ��
	const int FRAME_HEIGHT = 80;	//��Ҹ߶�
public:
	Player();

	~Player();

	void ProcessEvent(const ExMessage& msg);

	void Move();

	void Draw(int delta);

	const POINT& GetPosition() const;

private:
	const int SHADOW_WIDTH = 32;	//��Ӱ���
private:
	IMAGE img_shadow;		//�����Ӱ
	Animation* anim_left;
	Animation* anim_right;
	POINT position = { 500,500 };		//��ҳ�ʼ����
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;
};
