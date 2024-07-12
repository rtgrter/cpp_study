#include "Atlas.h"

//防止重定义，应在.cpp文件中定义全局变量，在.h文件中使用extern关键字进行声明
Atlas* atlas_player_left;
Atlas* atlas_player_right;
Atlas* atlas_enemy_left;
Atlas* atlas_enemy_right;

Atlas::Atlas(LPCTSTR path, int num)
{
	TCHAR path_file[256];
	for (size_t i = 0; i < num; ++i)
	{
		_stprintf_s(path_file, path, i);

		IMAGE* frame = new IMAGE();
		loadimage(frame, path_file);
		frame_list.push_back(frame);
	}
}

Atlas::~Atlas()
{
	for (size_t i = 0; i < frame_list.size(); ++i)
		delete frame_list[i];
}