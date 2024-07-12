#pragma once
#include <graphics.h>
#include <string>
#include <vector>
#include "Atlas.h"

const int PLAY_ANIM_NUM = 6;		//动画加载图片数量

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

inline void putimage_alpha(int x, int y, IMAGE* img);

class Animation
{
public:
	Animation(Atlas* atlas, int interval);

	~Animation();

	void play(int x, int y, int delta);

private:
	int timer = 0;			//动画计时器
	int idx_frame = 0;		//动画帧索引
	int interval_ms = 0;

private:
	Atlas* anim_atlas;
};
