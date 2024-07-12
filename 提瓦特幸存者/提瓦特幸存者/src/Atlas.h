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

//防止重定义，应在.cpp文件中定义全局变量，在.h文件中使用extern关键字进行声明
extern Atlas* atlas_player_left;
extern Atlas* atlas_player_right;
extern Atlas* atlas_enemy_left;
extern Atlas* atlas_enemy_right;