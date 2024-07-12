#pragma once
#include <graphics.h>
#include <string>
#include <vector>

class Atlas
{
public:
	Atlas(LPCTSTR path, int num);

	~Atlas();
public:
	std::vector<IMAGE*> frame_list;
};

//��ֹ�ض��壬Ӧ��.cpp�ļ��ж���ȫ�ֱ�������.h�ļ���ʹ��extern�ؼ��ֽ�������
extern Atlas* atlas_player_left;
extern Atlas* atlas_player_right;
extern Atlas* atlas_enemy_left;
extern Atlas* atlas_enemy_right;