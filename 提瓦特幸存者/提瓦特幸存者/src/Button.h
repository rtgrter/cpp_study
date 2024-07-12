#pragma once
#include <graphics.h>
#include <string>
#include <vector>

extern bool running;
extern bool is_game_started;

class Button
{
public:
	Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);

	void ProcessEvent(const ExMessage& msg);

	void Draw();

	~Button();

private:
	//检测鼠标点击
	bool CheckCursorHit(int x, int y);

	virtual void OnClick() = 0;

private:
	enum class Status
	{
		Idle = 0,
		Hovered,
		Pushed
	};
private:
	RECT region;
	IMAGE img_idle;
	IMAGE img_hovered;
	IMAGE img_pushed;
	Status status = Status::Idle;
};

//开始游戏按钮
class StartGameButton :public Button
{
public:
	StartGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
		: Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {}
	~StartGameButton() = default;

protected:
	void OnClick()
	{
		is_game_started = true;
		mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);			//播放bgm
	}
};

//退出游戏按钮
class QuitGameButton :public Button
{
public:
	QuitGameButton(RECT rect,LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
		: Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {}
	~QuitGameButton() = default;

protected:
	void OnClick()
	{
		running = false;
	}
};
