#include "Player.h"
#include "Enemy.h"
#include "Animation.h"
#include "Bullet.h"
#include "Atlas.h"
#include "Button.h"

int idx_current_anim = 0;

const int BUTTON_WIDTH = 192;
const int BUTTON_HEIGHT = 75;

IMAGE img_player_left[PLAY_ANIM_NUM];
IMAGE img_player_right[PLAY_ANIM_NUM];



//Animation anim_left_player(_T("img/player_left_%d.png"), 6, 45);
//Animation anim_right_player(_T("img/player_right_%d.png"), 6, 45);

//加载动画
//void LoadAnimation()
//{
//	for (size_t i = 0; i < PLAY_ANIM_NUM; ++i)
//	{
//		std::wstring path = L"img/player_left_" + std::to_wstring(i) + L".png";
//		loadimage(&img_player_left[i], path.c_str());
//	}
//	for (size_t i = 0; i < PLAY_ANIM_NUM; ++i)
//	{
//		std::wstring path = L"img/player_right_" + std::to_wstring(i) + L".png";
//		loadimage(&img_player_right[i], path.c_str());
//	}
//}

//生成新的敌人
void TryGenerateEnemy(std::vector<Enemy*>& enemy_list)
{
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}

//更新子弹位置
void UpdateBullets(std::vector<Bullet>& bullet_list, const Player& player)
{
	const double RADIAL_SPEED = 0.0045;							//径向波动速度
	const double TANGENT_SPEED = 0.0055;						//切向波动速度
	double radian_interval = 2 * 3.14159 / bullet_list.size();	//子弹之间的弧度间隔
	POINT player_position = player.GetPosition();
	double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);
	for (size_t i = 0; i < bullet_list.size(); ++i)
	{
		double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i;	//当前子弹所在弧度值
		bullet_list[i].position.x = player_position.x + player.FRAME_WIDTH / 2 + (int)(radius * sin(radian));
		bullet_list[i].position.y = player_position.y + player.FRAME_HEIGHT / 2 + (int)(radius * cos(radian));
	}
}

//绘制玩家得分
void DrawPlayerScore(int score)
{
	static TCHAR text[64];
	_stprintf_s(text, _T("当前玩家得分：%d"), score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 185));
	outtextxy(10, 10, text);
}

int main()
{
	initgraph(1280, 720);		//初始化窗口

	atlas_player_left = new Atlas(_T("img/player_left_%d.png"), 6);
	atlas_player_right = new Atlas(_T("img/player_right_%d.png"), 6);
	atlas_enemy_left = new Atlas(_T("img/enemy_left_%d.png"), 6);
	atlas_enemy_right = new Atlas(_T("img/enemy_right_%d.png"), 6);

	mciSendString(_T("open mus/bgm.mp3 alias bgm"), NULL, 0, NULL);		//加载bgm
	mciSendString(_T("open mus/hit.wav alias hit"), NULL, 0, NULL);		//加载音效

	int score = 0;
	Player player;				//玩家只有一个
	ExMessage msg;				//消息处理
	IMAGE img_menu;				//主菜单背景图片
	IMAGE img_background;		//游戏背景图片
	std::vector<Enemy*> enemy_list;		//敌人列表
	std::vector<Bullet> bullet_list(3);	//子弹列表

	RECT region_btn_start_game, region_btn_quit_game;

	region_btn_start_game.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	region_btn_start_game.right = region_btn_start_game.left + BUTTON_WIDTH;
	region_btn_start_game.top = 430;
	region_btn_start_game.bottom = region_btn_start_game.top + BUTTON_HEIGHT;

	region_btn_quit_game.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	region_btn_quit_game.right = region_btn_quit_game.left + BUTTON_WIDTH;
	region_btn_quit_game.top = 550;
	region_btn_quit_game.bottom = region_btn_quit_game.top + BUTTON_HEIGHT;

	StartGameButton btn_start_game = StartGameButton(region_btn_start_game,
		_T("img/ui_start_idle.png"), _T("img/ui_start_hovered.png"), _T("img/ui_start_pushed.png"));
	QuitGameButton btn_quit_game = QuitGameButton(region_btn_quit_game,
		_T("img/ui_quit_idle.png"), _T("img/ui_quit_hovered.png"), _T("img/ui_quit_pushed.png"));

	//LoadAnimation();
	loadimage(&img_menu, _T("img/menu.png"));
	loadimage(&img_background, _T("img/background.png"));

	
	BeginBatchDraw();

	while (running)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			if(is_game_started)
				player.ProcessEvent(msg);
			else
			{
				btn_start_game.ProcessEvent(msg);
				btn_quit_game.ProcessEvent(msg);
			}
		}

		if (is_game_started)
		{
			player.Move();
			UpdateBullets(bullet_list, player);
			TryGenerateEnemy(enemy_list);
			for (Enemy* enemy : enemy_list)
				enemy->Move(player);

			//检测敌人和玩家的碰撞
			for (Enemy* enemy : enemy_list)
			{
				if (enemy->CheckPlayerCollision(player))
				{
					static TCHAR text[128];
					_stprintf_s(text, _T("最终得分：%d !"), score);
					MessageBox(GetHWnd(), text, _T("游戏结束"), MB_OK);
					running = false;
					break;
				}
			}
			//检测子弹和敌人的碰撞
			for (Enemy* enemy : enemy_list)
			{
				for (const Bullet& bullet : bullet_list)
				{
					if (enemy->CheckBulletCollision(bullet))
					{
						mciSendString(_T("play hit from 0"), NULL, 0, NULL);	//播放音效	
						enemy->Hurt();
						score++;
					}
				}
			}
			//移除生命值归零的敌人
			for (size_t i = 0; i < enemy_list.size(); ++i)
			{
				Enemy* enemy = enemy_list[i];
				if (!enemy->CheckAlive())
				{
					std::swap(enemy_list[i], enemy_list.back());
					enemy_list.pop_back();
					delete enemy;
				}
			}
		}




		cleardevice();

		if (is_game_started)
		{
			putimage(0, 0, &img_background);
			player.Draw(1000 / 144);
			for (Enemy* enemy : enemy_list)
				enemy->Draw(1000 / 144);
			for (const Bullet& bullet : bullet_list)
				bullet.Draw();
			DrawPlayerScore(score);
		}
		else
		{
			putimage(0, 0, &img_menu);
			btn_start_game.Draw();
			btn_quit_game.Draw();
		}

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 144)
		{
			Sleep(1000 / 144 - delta_time);
		}
	}

	delete atlas_player_left;
	delete atlas_player_right;
	delete atlas_enemy_left;
	delete atlas_enemy_right;

	EndBatchDraw();
	return 0;

}