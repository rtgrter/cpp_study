#include "Animation.h"

#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"MSIMG32.LIB")

inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });

}

//¶¯»­Àà
Animation::Animation(Atlas* atlas, int interval)
{
	anim_atlas = atlas;
	interval_ms = interval;
}

Animation::~Animation() = default;

void Animation::play(int x, int y, int delta)
{
	timer += delta;
	if (timer >= interval_ms)
	{
		idx_frame = (idx_frame + 1) % anim_atlas->frame_list.size();
		timer = 0;
	}
	putimage_alpha(x, y, anim_atlas->frame_list[idx_frame]);
}