#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>
#include "math.h"

#define rad 0.01745329252

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{

	if (goal.IsAnimation() == false && goal.GetFrameIndexOfBitmap() != 0 && sub_phase == 1)
	{
		sub_phase = 2;
	}
	if (sub_phase == 2) {
		if (timer == 0 && money < goal_money)
		{
			gameover = true;
		}
		if (timer == 0 && money >= goal_money )
		{
			if (phase == 10) {
				win = true;
				gameover = true;
			}
			else {
				sub_phase = 3;
			}
			
		}
	}


}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	phase = 7;
	CAudio::Instance()->Load(0, "resources/sound/goal.mp3");
	CAudio::Instance()->Load(1, "resources/sound/next_level.mp3");
	CAudio::Instance()->Load(2, "resources/sound/shoot_claw.mp3");
	CAudio::Instance()->Load(3, "resources/sound/pull_done.mp3");
	CAudio::Instance()->Load(4, "resources/sound/money.mp3");		//買東西跟獲得錢的音效
	CAudio::Instance()->Load(5, "resources/sound/mine_big.mp3");	//strength跟大金礦是用這個音效
	CAudio::Instance()->Load(6, "resources/sound/mine_small.mp3");
	CAudio::Instance()->Load(7, "resources/sound/mine_rock.mp3");
	CAudio::Instance()->Load(8, "resources/sound/bomb.mp3");
	CAudio::Instance()->Load(9, "resources/sound/pull.mp3");		//拉爪子的音效
	CAudio::Instance()->Load(10, "resources/sound/shop.mp3");		//商店老闆講話的音效，剩這兩個還沒做

	/*Goal頁面*/
	goal.LoadBitmapByString({ "resources/goal_page/goal_bg/52.bmp","resources/goal_page/goal_bg/53.bmp","resources/goal_page/goal_bg/54.bmp","resources/goal_page/goal_bg/55.bmp","resources/goal_page/goal_bg/56.bmp","resources/goal_page/goal_bg/57.bmp","resources/goal_page/goal_bg/58.bmp","resources/goal_page/goal_bg/59.bmp","resources/goal_page/goal_bg/60.bmp","resources/goal_page/goal_bg/61.bmp","resources/goal_page/goal_bg/62.bmp","resources/goal_page/goal_bg/63.bmp","resources/goal_page/goal_bg/64.bmp","resources/goal_page/goal_bg/65.bmp","resources/goal_page/goal_bg/66.bmp","resources/goal_page/goal_bg/67.bmp","resources/goal_page/goal_bg/68.bmp","resources/goal_page/goal_bg/69.bmp","resources/goal_page/goal_bg/70.bmp","resources/goal_page/goal_bg/71.bmp","resources/goal_page/goal_bg/72.bmp","resources/goal_page/goal_bg/73.bmp","resources/goal_page/goal_bg/74.bmp","resources/goal_page/goal_bg/75.bmp","resources/goal_page/goal_bg/76.bmp","resources/goal_page/goal_bg/77.bmp","resources/goal_page/goal_bg/78.bmp","resources/goal_page/goal_bg/79.bmp","resources/goal_page/goal_bg/80.bmp","resources/goal_page/goal_bg/81.bmp","resources/goal_page/goal_bg/82.bmp","resources/goal_page/goal_bg/83.bmp","resources/goal_page/goal_bg/84.bmp","resources/goal_page/goal_bg/85.bmp","resources/goal_page/goal_bg/86.bmp","resources/goal_page/goal_bg/87.bmp","resources/goal_page/goal_bg/88.bmp","resources/goal_page/goal_bg/89.bmp","resources/goal_page/goal_bg/90.bmp","resources/goal_page/goal_bg/91.bmp","resources/goal_page/goal_bg/92.bmp","resources/goal_page/goal_bg/93.bmp" });
	goal.SetAnimation(50, true);
	goal.SetTopLeft(0, 0);

	/*第一關*/
	background.LoadBitmapByString({ "resources/stage/1_1.bmp", "resources/stage/2_1.bmp" ,"resources/stage/3_1.bmp", "resources/stage/4_1.bmp","resources/stage/5_1.bmp", "resources/stage/6_1.bmp" ,"resources/stage/7_1.bmp", "resources/stage/8_1.bmp", "resources/stage/9_1.bmp", "resources/stage/10_1.bmp" });
	background.SetTopLeft(0, 0);

	miner.LoadBitmapByString({ "resources/miner/normal/1.bmp","resources/miner/normal/2.bmp","resources/miner/normal/3.bmp","resources/miner/normal/4.bmp","resources/miner/normal/5.bmp" }, RGB(0, 0, 0));
	miner.SetTopLeft(529, 33);
	miner.SetAnimation(200, true);
	miner_t.LoadBitmapByString({ "resources/miner/throw/31.bmp","resources/miner/throw/32.bmp","resources/miner/throw/33.bmp","resources/miner/throw/34.bmp","resources/miner/throw/35.bmp","resources/miner/throw/36.bmp","resources/miner/throw/37.bmp" }, RGB(0, 0, 0));
	miner_t.SetTopLeft(529, 23);
	miner_t.SetAnimation(20, true);
	miner_s.LoadBitmapByString({ "resources/miner/strength/11.bmp","resources/miner/strength/12.bmp","resources/miner/strength/13.bmp","resources/miner/strength/14.bmp","resources/miner/strength/15.bmp","resources/miner/strength/16.bmp" }, RGB(0, 0, 0));
	miner_s.SetTopLeft(529, 18);
	miner_s.SetAnimation(80, true);
	miner_p.LoadBitmapByString({ "resources/miner/pull/1.bmp","resources/miner/pull/2.bmp","resources/miner/pull/3.bmp","resources/miner/pull/4.bmp","resources/miner/pull/5.bmp","resources/miner/pull/6.bmp","resources/miner/pull/7.bmp","resources/miner/pull/8.bmp","resources/miner/pull/9.bmp","resources/miner/pull/10.bmp","resources/miner/pull/11.bmp","resources/miner/pull/12.bmp","resources/miner/pull/13.bmp","resources/miner/pull/14.bmp","resources/miner/pull/15.bmp","resources/miner/pull/16.bmp","resources/miner/pull/17.bmp","resources/miner/pull/18.bmp","resources/miner/pull/19.bmp","resources/miner/pull/20.bmp","resources/miner/pull/21.bmp","resources/miner/pull/22.bmp" }, RGB(0, 0, 0));
	miner_p.SetTopLeft(529, 23);
	miner_p.SetAnimation(50, false);

	bonus_strength.LoadBitmapByString({ "resources/miner/bonus/35.bmp","resources/miner/bonus/36.bmp","resources/miner/bonus/37.bmp","resources/miner/bonus/38.bmp","resources/miner/bonus/39.bmp","resources/miner/bonus/40.bmp","resources/miner/bonus/41.bmp","resources/miner/bonus/42.bmp","resources/miner/bonus/43.bmp","resources/miner/bonus/44.bmp","resources/miner/bonus/45.bmp","resources/miner/bonus/46.bmp","resources/miner/bonus/47.bmp","resources/miner/bonus/48.bmp","resources/miner/bonus/49.bmp","resources/miner/bonus/50.bmp","resources/miner/bonus/51.bmp","resources/miner/bonus/52.bmp","resources/miner/bonus/53.bmp","resources/miner/bonus/54.bmp","resources/miner/bonus/55.bmp","resources/miner/bonus/56.bmp" }, RGB(0, 0, 0));
	bonus_strength.SetTopLeft(210, 0);
	bonus_strength.SetAnimation(50, true);

	bonus_bomb.LoadBitmapByString({ "resources/miner/bonus/60.bmp","resources/miner/bonus/61.bmp","resources/miner/bonus/62.bmp","resources/miner/bonus/63.bmp","resources/miner/bonus/64.bmp","resources/miner/bonus/65.bmp","resources/miner/bonus/66.bmp","resources/miner/bonus/67.bmp","resources/miner/bonus/68.bmp","resources/miner/bonus/69.bmp","resources/miner/bonus/70.bmp","resources/miner/bonus/71.bmp","resources/miner/bonus/72.bmp","resources/miner/bonus/73.bmp","resources/miner/bonus/74.bmp","resources/miner/bonus/75.bmp","resources/miner/bonus/76.bmp","resources/miner/bonus/77.bmp","resources/miner/bonus/78.bmp" }, RGB(0, 0, 0));
	bonus_bomb.SetTopLeft(430, 30);
	bonus_bomb.SetAnimation(50, true);

	wood.LoadBitmapByString({ "resources/miner/wood.bmp" }, RGB(0, 0, 0));
	wood.SetTopLeft(519, 112);

	claw.LoadBitmapByString({ "resources/claw/0/rotate_new/4.bmp","resources/claw/0/rotate_new/5.bmp","resources/claw/0/rotate_new/6.bmp","resources/claw/0/rotate_new/7.bmp","resources/claw/0/rotate_new/8.bmp","resources/claw/0/rotate_new/9.bmp","resources/claw/0/rotate_new/10.bmp","resources/claw/0/rotate_new/11.bmp","resources/claw/0/rotate_new/12.bmp","resources/claw/0/rotate_new/13.bmp","resources/claw/0/rotate_new/14.bmp","resources/claw/0/rotate_new/15.bmp","resources/claw/0/rotate_new/16.bmp","resources/claw/0/rotate_new/17.bmp","resources/claw/0/rotate_new/18.bmp","resources/claw/0/rotate_new/19.bmp","resources/claw/0/rotate_new/20.bmp","resources/claw/0/rotate_new/21.bmp","resources/claw/0/rotate_new/22.bmp","resources/claw/0/rotate_new/23.bmp","resources/claw/0/rotate_new/24.bmp","resources/claw/0/rotate_new/25.bmp","resources/claw/0/rotate_new/26.bmp","resources/claw/0/rotate_new/27.bmp","resources/claw/0/rotate_new/28.bmp","resources/claw/0/rotate_new/29.bmp","resources/claw/0/rotate_new/30.bmp","resources/claw/0/rotate_new/31.bmp","resources/claw/0/rotate_new/32.bmp","resources/claw/0/rotate_new/33.bmp","resources/claw/0/rotate_new/34.bmp","resources/claw/0/rotate_new/35.bmp","resources/claw/0/rotate_new/36.bmp","resources/claw/0/rotate_new/37.bmp","resources/claw/0/rotate_new/38.bmp","resources/claw/0/rotate_new/39.bmp","resources/claw/0/rotate_new/40.bmp","resources/claw/0/rotate_new/41.bmp","resources/claw/0/rotate_new/42.bmp","resources/claw/0/rotate_new/43.bmp","resources/claw/0/rotate_new/44.bmp","resources/claw/0/rotate_new/45.bmp","resources/claw/0/rotate_new/46.bmp","resources/claw/0/rotate_new/47.bmp","resources/claw/0/rotate_new/48.bmp","resources/claw/0/rotate_new/49.bmp","resources/claw/0/rotate_new/50.bmp","resources/claw/0/rotate_new/51.bmp","resources/claw/0/rotate_new/52.bmp","resources/claw/0/rotate_new/53.bmp","resources/claw/0/rotate_new/54.bmp","resources/claw/0/rotate_new/55.bmp","resources/claw/0/rotate_new/56.bmp","resources/claw/0/rotate_new/57.bmp","resources/claw/0/rotate_new/58.bmp","resources/claw/0/rotate_new/59.bmp","resources/claw/0/rotate_new/60.bmp","resources/claw/0/rotate_new/61.bmp","resources/claw/0/rotate_new/62.bmp","resources/claw/0/rotate_new/63.bmp","resources/claw/0/rotate_new/64.bmp","resources/claw/0/rotate_new/65.bmp","resources/claw/0/rotate_new/66.bmp","resources/claw/0/rotate_new/67.bmp","resources/claw/0/rotate_new/68.bmp","resources/claw/0/rotate_new/69.bmp","resources/claw/0/rotate_new/70.bmp","resources/claw/0/rotate_new/71.bmp","resources/claw/0/rotate_new/72.bmp","resources/claw/0/rotate_new/73.bmp","resources/claw/0/rotate_new/74.bmp","resources/claw/0/rotate_new/75.bmp" }, RGB(0, 0, 0));
	claw.SetTopLeft(507, 90);
	claw.SetAnimation(70, false);

	clawhead.LoadBitmapByString({ "resources/claw/0/rotate_new/4.bmp","resources/claw/0/rotate_new/5.bmp","resources/claw/0/rotate_new/6.bmp","resources/claw/0/rotate_new/7.bmp","resources/claw/0/rotate_new/8.bmp","resources/claw/0/rotate_new/9.bmp","resources/claw/0/rotate_new/10.bmp","resources/claw/0/rotate_new/11.bmp","resources/claw/0/rotate_new/12.bmp","resources/claw/0/rotate_new/13.bmp","resources/claw/0/rotate_new/14.bmp","resources/claw/0/rotate_new/15.bmp","resources/claw/0/rotate_new/16.bmp","resources/claw/0/rotate_new/17.bmp","resources/claw/0/rotate_new/18.bmp","resources/claw/0/rotate_new/19.bmp","resources/claw/0/rotate_new/20.bmp","resources/claw/0/rotate_new/21.bmp","resources/claw/0/rotate_new/22.bmp","resources/claw/0/rotate_new/23.bmp","resources/claw/0/rotate_new/24.bmp","resources/claw/0/rotate_new/25.bmp","resources/claw/0/rotate_new/26.bmp","resources/claw/0/rotate_new/27.bmp","resources/claw/0/rotate_new/28.bmp","resources/claw/0/rotate_new/29.bmp","resources/claw/0/rotate_new/30.bmp","resources/claw/0/rotate_new/31.bmp","resources/claw/0/rotate_new/32.bmp","resources/claw/0/rotate_new/33.bmp","resources/claw/0/rotate_new/34.bmp","resources/claw/0/rotate_new/35.bmp","resources/claw/0/rotate_new/36.bmp","resources/claw/0/rotate_new/37.bmp","resources/claw/0/rotate_new/38.bmp","resources/claw/0/rotate_new/39.bmp","resources/claw/0/rotate_new/40.bmp","resources/claw/0/rotate_new/41.bmp","resources/claw/0/rotate_new/42.bmp","resources/claw/0/rotate_new/43.bmp","resources/claw/0/rotate_new/44.bmp","resources/claw/0/rotate_new/45.bmp","resources/claw/0/rotate_new/46.bmp","resources/claw/0/rotate_new/47.bmp","resources/claw/0/rotate_new/48.bmp","resources/claw/0/rotate_new/49.bmp","resources/claw/0/rotate_new/50.bmp","resources/claw/0/rotate_new/51.bmp","resources/claw/0/rotate_new/52.bmp","resources/claw/0/rotate_new/53.bmp","resources/claw/0/rotate_new/54.bmp","resources/claw/0/rotate_new/55.bmp","resources/claw/0/rotate_new/56.bmp","resources/claw/0/rotate_new/57.bmp","resources/claw/0/rotate_new/58.bmp","resources/claw/0/rotate_new/59.bmp","resources/claw/0/rotate_new/60.bmp","resources/claw/0/rotate_new/61.bmp","resources/claw/0/rotate_new/62.bmp","resources/claw/0/rotate_new/63.bmp","resources/claw/0/rotate_new/64.bmp","resources/claw/0/rotate_new/65.bmp","resources/claw/0/rotate_new/66.bmp","resources/claw/0/rotate_new/67.bmp","resources/claw/0/rotate_new/68.bmp","resources/claw/0/rotate_new/69.bmp","resources/claw/0/rotate_new/70.bmp","resources/claw/0/rotate_new/71.bmp","resources/claw/0/rotate_new/72.bmp","resources/claw/0/rotate_new/73.bmp","resources/claw/0/rotate_new/74.bmp","resources/claw/0/rotate_new/75.bmp","resources/claw/0/rotate_close/4.bmp","resources/claw/0/rotate_close/5.bmp","resources/claw/0/rotate_close/6.bmp","resources/claw/0/rotate_close/7.bmp","resources/claw/0/rotate_close/8.bmp","resources/claw/0/rotate_close/9.bmp","resources/claw/0/rotate_close/10.bmp","resources/claw/0/rotate_close/11.bmp","resources/claw/0/rotate_close/12.bmp","resources/claw/0/rotate_close/13.bmp","resources/claw/0/rotate_close/14.bmp","resources/claw/0/rotate_close/15.bmp","resources/claw/0/rotate_close/16.bmp","resources/claw/0/rotate_close/17.bmp","resources/claw/0/rotate_close/18.bmp","resources/claw/0/rotate_close/19.bmp","resources/claw/0/rotate_close/20.bmp","resources/claw/0/rotate_close/21.bmp","resources/claw/0/rotate_close/22.bmp","resources/claw/0/rotate_close/23.bmp","resources/claw/0/rotate_close/24.bmp","resources/claw/0/rotate_close/25.bmp","resources/claw/0/rotate_close/26.bmp","resources/claw/0/rotate_close/27.bmp","resources/claw/0/rotate_close/28.bmp","resources/claw/0/rotate_close/29.bmp","resources/claw/0/rotate_close/30.bmp","resources/claw/0/rotate_close/31.bmp","resources/claw/0/rotate_close/32.bmp","resources/claw/0/rotate_close/33.bmp","resources/claw/0/rotate_close/34.bmp","resources/claw/0/rotate_close/35.bmp","resources/claw/0/rotate_close/36.bmp","resources/claw/0/rotate_close/37.bmp","resources/claw/0/rotate_close/38.bmp","resources/claw/0/rotate_close/39.bmp","resources/claw/0/rotate_close/40.bmp","resources/claw/0/rotate_close/41.bmp","resources/claw/0/rotate_close/42.bmp","resources/claw/0/rotate_close/43.bmp","resources/claw/0/rotate_close/44.bmp","resources/claw/0/rotate_close/45.bmp","resources/claw/0/rotate_close/46.bmp","resources/claw/0/rotate_close/47.bmp","resources/claw/0/rotate_close/48.bmp","resources/claw/0/rotate_close/49.bmp","resources/claw/0/rotate_close/50.bmp","resources/claw/0/rotate_close/51.bmp","resources/claw/0/rotate_close/52.bmp","resources/claw/0/rotate_close/53.bmp","resources/claw/0/rotate_close/54.bmp","resources/claw/0/rotate_close/55.bmp","resources/claw/0/rotate_close/56.bmp","resources/claw/0/rotate_close/57.bmp","resources/claw/0/rotate_close/58.bmp","resources/claw/0/rotate_close/59.bmp","resources/claw/0/rotate_close/60.bmp","resources/claw/0/rotate_close/61.bmp","resources/claw/0/rotate_close/62.bmp","resources/claw/0/rotate_close/63.bmp","resources/claw/0/rotate_close/64.bmp","resources/claw/0/rotate_close/65.bmp","resources/claw/0/rotate_close/66.bmp","resources/claw/0/rotate_close/67.bmp","resources/claw/0/rotate_close/68.bmp","resources/claw/0/rotate_close/69.bmp","resources/claw/0/rotate_close/70.bmp","resources/claw/0/rotate_close/71.bmp","resources/claw/0/rotate_close/72.bmp","resources/claw/0/rotate_close/73.bmp","resources/claw/0/rotate_close/74.bmp","resources/claw/0/rotate_close/75.bmp" }, RGB(0, 0, 0));
	clawhead.SetTopLeft(507, 90);

	mine_caught.LoadBitmapByString({ "resources/claw/mine_caught/0.bmp","resources/claw/mine_caught/0.bmp","resources/claw/mine_caught/2.bmp","resources/claw/mine_caught/3.bmp","resources/claw/mine_caught/4.bmp","resources/claw/mine_caught/5.bmp","resources/claw/mine_caught/6.bmp","resources/claw/mine_caught/7.bmp","resources/claw/mine_caught/8.bmp","resources/claw/mine_caught/9.bmp","resources/claw/mine_caught/10.bmp","resources/claw/mine_caught/11.bmp","resources/claw/mine_caught/12.bmp","resources/claw/mine_caught/13.bmp","resources/claw/mine_caught/14.bmp" }, RGB(0, 0, 0));
	mine_caught.SetTopLeft(0, 0);


	//clawhead_close.LoadBitmapByString({ "resources/claw/0/rotate_close/4.bmp","resources/claw/0/rotate_close/5.bmp","resources/claw/0/rotate_close/6.bmp","resources/claw/0/rotate_close/7.bmp","resources/claw/0/rotate_close/8.bmp","resources/claw/0/rotate_close/9.bmp","resources/claw/0/rotate_close/10.bmp","resources/claw/0/rotate_close/11.bmp","resources/claw/0/rotate_close/12.bmp","resources/claw/0/rotate_close/13.bmp","resources/claw/0/rotate_close/14.bmp","resources/claw/0/rotate_close/15.bmp","resources/claw/0/rotate_close/16.bmp","resources/claw/0/rotate_close/17.bmp","resources/claw/0/rotate_close/18.bmp","resources/claw/0/rotate_close/19.bmp","resources/claw/0/rotate_close/20.bmp","resources/claw/0/rotate_close/21.bmp","resources/claw/0/rotate_close/22.bmp","resources/claw/0/rotate_close/23.bmp","resources/claw/0/rotate_close/24.bmp","resources/claw/0/rotate_close/25.bmp","resources/claw/0/rotate_close/26.bmp","resources/claw/0/rotate_close/27.bmp","resources/claw/0/rotate_close/28.bmp","resources/claw/0/rotate_close/29.bmp","resources/claw/0/rotate_close/30.bmp","resources/claw/0/rotate_close/31.bmp","resources/claw/0/rotate_close/32.bmp","resources/claw/0/rotate_close/33.bmp","resources/claw/0/rotate_close/34.bmp","resources/claw/0/rotate_close/35.bmp","resources/claw/0/rotate_close/36.bmp","resources/claw/0/rotate_close/37.bmp","resources/claw/0/rotate_close/38.bmp","resources/claw/0/rotate_close/39.bmp","resources/claw/0/rotate_close/40.bmp","resources/claw/0/rotate_close/41.bmp","resources/claw/0/rotate_close/42.bmp","resources/claw/0/rotate_close/43.bmp","resources/claw/0/rotate_close/44.bmp","resources/claw/0/rotate_close/45.bmp","resources/claw/0/rotate_close/46.bmp","resources/claw/0/rotate_close/47.bmp","resources/claw/0/rotate_close/48.bmp","resources/claw/0/rotate_close/49.bmp","resources/claw/0/rotate_close/50.bmp","resources/claw/0/rotate_close/51.bmp","resources/claw/0/rotate_close/52.bmp","resources/claw/0/rotate_close/53.bmp","resources/claw/0/rotate_close/54.bmp","resources/claw/0/rotate_close/55.bmp","resources/claw/0/rotate_close/56.bmp","resources/claw/0/rotate_close/57.bmp","resources/claw/0/rotate_close/58.bmp","resources/claw/0/rotate_close/59.bmp","resources/claw/0/rotate_close/60.bmp","resources/claw/0/rotate_close/61.bmp","resources/claw/0/rotate_close/62.bmp","resources/claw/0/rotate_close/63.bmp","resources/claw/0/rotate_close/64.bmp","resources/claw/0/rotate_close/65.bmp","resources/claw/0/rotate_close/66.bmp","resources/claw/0/rotate_close/67.bmp","resources/claw/0/rotate_close/68.bmp","resources/claw/0/rotate_close/69.bmp","resources/claw/0/rotate_close/70.bmp","resources/claw/0/rotate_close/71.bmp","resources/claw/0/rotate_close/72.bmp","resources/claw/0/rotate_close/73.bmp","resources/claw/0/rotate_close/74.bmp","resources/claw/0/rotate_close/75.bmp" }, RGB(0, 0, 0));
	//clawhead_close.SetTopLeft(507, 90);

	for (int i = 0; i < 100; i++) {
		line[i].LoadBitmapByString({ "resources/claw/line.bmp" });
	}
	for (int i = 0; i < 100; i++) {
		line2[i].LoadBitmapByString({ "resources/claw/line.bmp" });
	}
	for (int i = 0; i < 100; i++) {
		line3[i].LoadBitmapByString({ "resources/claw/line.bmp" });
	}

	load_mines();

	hitbox.LoadBitmapByString({ "resources/claw/hitbox0.bmp" }, RGB(0, 0, 0));
	hitbox.SetTopLeft(538, 90);

	bomb.LoadBitmapByString({ "resources/claw/bomb.bmp" }, RGB(0, 0, 0));
	bomb.SetTopLeft(507, 90);

	bomb_explosion.LoadBitmapByString({ "resources/claw/bomb_explosion/1.bmp","resources/claw/bomb_explosion/2.bmp","resources/claw/bomb_explosion/3.bmp","resources/claw/bomb_explosion/4.bmp","resources/claw/bomb_explosion/5.bmp","resources/claw/bomb_explosion/6.bmp","resources/claw/bomb_explosion/7.bmp","resources/claw/bomb_explosion/8.bmp","resources/claw/bomb_explosion/9.bmp","resources/claw/bomb_explosion/10.bmp","resources/claw/bomb_explosion/11.bmp","resources/claw/bomb_explosion/12.bmp" }, RGB(0, 0, 0));
	bomb_explosion.SetAnimation(30, true);
	



	number_of_bombs.LoadBitmapByString({ "resources/number_of_bombs/1.bmp","resources/number_of_bombs/2.bmp","resources/number_of_bombs/3.bmp","resources/number_of_bombs/4.bmp","resources/number_of_bombs/5.bmp","resources/number_of_bombs/6.bmp","resources/number_of_bombs/7.bmp","resources/number_of_bombs/8.bmp","resources/number_of_bombs/9.bmp" }, RGB(0, 0, 0));
	number_of_bombs.SetTopLeft(687, 70);

	exit.LoadBitmapByString({ "resources/exit/1.bmp", "resources/exit/2.bmp" }, RGB(0, 0, 0));
	exit.SetTopLeft(800, 12);

	exit_background.LoadBitmapByString({ "resources/exit_background/170.bmp" });
	exit_background.SetTopLeft(0, 0);

	playagain_button.LoadBitmapByString({ "resources/exit_background/1.bmp", "resources/exit_background/2.bmp"}, RGB(0, 0, 0));
	playagain_button.SetTopLeft(125, 664);

	timer_bling.LoadBitmapByString({"resources/stage/timer_bling.bmp"}, RGB(0, 0, 0));
	timer_bling.SetTopLeft(1020, 12);

	/*輸,贏*/
	fail.LoadBitmapByString({ "resources/fail_page/140.bmp","resources/fail_page/141.bmp","resources/fail_page/142.bmp","resources/fail_page/143.bmp","resources/fail_page/144.bmp","resources/fail_page/145.bmp","resources/fail_page/146.bmp","resources/fail_page/147.bmp","resources/fail_page/148.bmp","resources/fail_page/149.bmp","resources/fail_page/150.bmp","resources/fail_page/151.bmp","resources/fail_page/152.bmp","resources/fail_page/153.bmp","resources/fail_page/154.bmp","resources/fail_page/155.bmp","resources/fail_page/156.bmp","resources/fail_page/157.bmp","resources/fail_page/158.bmp","resources/fail_page/159.bmp","resources/fail_page/160.bmp","resources/fail_page/161.bmp","resources/fail_page/162.bmp","resources/fail_page/163.bmp","resources/fail_page/164.bmp","resources/fail_page/165.bmp","resources/fail_page/166.bmp","resources/fail_page/167.bmp","resources/fail_page/168.bmp" });
	fail.SetTopLeft(0, 0);
	fail.SetAnimation(50, true);

	success.LoadBitmapByString({ "resources/success_page/94.bmp","resources/success_page/95.bmp","resources/success_page/96.bmp","resources/success_page/97.bmp","resources/success_page/98.bmp","resources/success_page/99.bmp","resources/success_page/100.bmp","resources/success_page/101.bmp","resources/success_page/102.bmp","resources/success_page/103.bmp","resources/success_page/104.bmp","resources/success_page/105.bmp","resources/success_page/106.bmp","resources/success_page/107.bmp","resources/success_page/108.bmp","resources/success_page/109.bmp","resources/success_page/110.bmp","resources/success_page/111.bmp","resources/success_page/112.bmp","resources/success_page/113.bmp","resources/success_page/114.bmp","resources/success_page/115.bmp","resources/success_page/116.bmp","resources/success_page/117.bmp","resources/success_page/118.bmp","resources/success_page/119.bmp","resources/success_page/120.bmp","resources/success_page/121.bmp","resources/success_page/122.bmp","resources/success_page/123.bmp","resources/success_page/124.bmp","resources/success_page/125.bmp","resources/success_page/126.bmp","resources/success_page/127.bmp","resources/success_page/128.bmp","resources/success_page/129.bmp" });
	success.SetTopLeft(0, 0);
	success.SetAnimation(50, true);

	/*商店*/
	shop_bg.LoadBitmapByString({ "resources/shop_page/shop_bg.bmp" });
	shop_bg.SetTopLeft(0, 0);

	next_level_button.LoadBitmapByString({ "resources/shop_page/next_level_button/1.bmp" ,"resources/shop_page/next_level_button/2.bmp" }, RGB(0, 0, 0));
	next_level_button.SetTopLeft(847, 122);

	owner_talk.LoadBitmapByString({"resources/shop_page/owner/talk/1.bmp","resources/shop_page/owner/talk/2.bmp","resources/shop_page/owner/talk/3.bmp","resources/shop_page/owner/talk/4.bmp","resources/shop_page/owner/talk/5.bmp","resources/shop_page/owner/talk/6.bmp","resources/shop_page/owner/talk/7.bmp","resources/shop_page/owner/talk/8.bmp","resources/shop_page/owner/talk/9.bmp","resources/shop_page/owner/talk/10.bmp","resources/shop_page/owner/talk/11.bmp","resources/shop_page/owner/talk/12.bmp","resources/shop_page/owner/talk/13.bmp","resources/shop_page/owner/talk/14.bmp","resources/shop_page/owner/talk/15.bmp","resources/shop_page/owner/talk/16.bmp","resources/shop_page/owner/talk/17.bmp","resources/shop_page/owner/talk/18.bmp"}, RGB(0, 0, 0));
	owner_talk.SetTopLeft(-4, 186);
	owner_talk.SetAnimation(50, true);

	owner_buy.LoadBitmapByString({"resources/shop_page/owner/buy/19.bmp", "resources/shop_page/owner/buy/20.bmp", "resources/shop_page/owner/buy/21.bmp", "resources/shop_page/owner/buy/22.bmp", "resources/shop_page/owner/buy/23.bmp", "resources/shop_page/owner/buy/24.bmp", "resources/shop_page/owner/buy/25.bmp"}, RGB(0, 0, 0));
	owner_buy.SetTopLeft(-4, 186);
	owner_buy.SetAnimation(50, true);

	owner_angry.LoadBitmapByString({ "resources/shop_page/owner/angry/26.bmp", "resources/shop_page/owner/angry/27.bmp", "resources/shop_page/owner/angry/28.bmp", "resources/shop_page/owner/angry/29.bmp", "resources/shop_page/owner/angry/30.bmp", "resources/shop_page/owner/angry/31.bmp", "resources/shop_page/owner/angry/32.bmp", "resources/shop_page/owner/angry/33.bmp", "resources/shop_page/owner/angry/34.bmp", "resources/shop_page/owner/angry/35.bmp", "resources/shop_page/owner/angry/36.bmp", "resources/shop_page/owner/angry/37.bmp", "resources/shop_page/owner/angry/38.bmp" }, RGB(0, 0, 0));
	owner_angry.SetTopLeft(-4, 186);
	owner_angry.SetAnimation(50, true);

	item_1.LoadBitmapByString({"resources/shop_page/1.bmp"}, RGB(0, 0, 0));
	item_1.SetTopLeft(50, 440);

	item_2.LoadBitmapByString({ "resources/shop_page/2.bmp" }, RGB(0, 0, 0));
	item_2.SetTopLeft(190, 410);

	item_3.LoadBitmapByString({ "resources/shop_page/3.bmp" }, RGB(0, 0, 0));
	item_3.SetTopLeft(330, 420);

	item_4.LoadBitmapByString({ "resources/shop_page/4.bmp" }, RGB(0, 0, 0));
	item_4.SetTopLeft(470, 440);

	item_5.LoadBitmapByString({ "resources/shop_page/5.bmp" }, RGB(0, 0, 0));
	item_5.SetTopLeft(610, 455);

	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN) {
		if (claw_is_ready == true) {
			if (miner.GetFrameIndexOfBitmap() == 0) {
				CAudio::Instance()->Play(2);
			}
			miner.ToggleAnimation();
			key_down_index = claw.GetFrameIndexOfBitmap();
			clawhead.SetFrameIndexOfBitmap(key_down_index);
			claw_is_ready = false;
		}
	}
	if (nChar == VK_UP) {
		
		if (bomb_num >= 1 && hit && !bomb_is_throw){
			bomb_is_throw = true;
			action_state = 2;
			bomb_num = bomb_num - 1;
		}
		
	}
	if (nChar == VK_RIGHT) {
		if (phase == 10) {
			win = true;
			gameover = true;
		}
		else {
			sub_phase = 3;
		}
	}
	if (nChar == VK_LEFT) {
		bomb_num = bomb_num + 1;
		bonus_bomb.ToggleAnimation();
	}
	if (nChar == VK_SPACE) {
		item_2_effect = true;
		action_state = 3;
	}
	if (nChar == 0x5A) {
		timer = 0;
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if (exit.GetFrameIndexOfBitmap() == 1 && sub_phase == 2 && money < goal_money) {
		gameover = true;
	}
	if (exit.GetFrameIndexOfBitmap() == 1 && sub_phase == 2 && money >= goal_money) {
		if (phase == 10) {
			win = true;
			gameover = true;
		}
		else {
			sub_phase = 3;
		}
	}
	if (next_level_button.GetFrameIndexOfBitmap() == 1 && sub_phase == 3) {
		next_level_button_clicked = true;
		if (item_is_bought_1 == true || item_is_bought_2 == true || item_is_bought_3 == true || item_is_bought_4 == true || item_is_bought_5 == true) {
			CAudio::Instance()->Play(4);
		}
		else {
			CAudio::Instance()->Play(7);
		}
	}

	//按下play again
	if (playagain_button.GetFrameIndexOfBitmap() == 1) {
		return_game = true;
	}

	/*按下後確認滑鼠位置與商店裡面1~5座標是否相同，相同的話則購買*/
	if (sub_phase == 3) {
		if (point.x >= item_1.GetLeft() &&
			point.x <= item_1.GetLeft() + item_1.GetWidth() &&
			point.y >= item_1.GetTop() &&
			point.y <= item_1.GetTop() + item_1.GetHeight() &&
			!item_is_bought_1 && item_in_stock_in_level[0] &&
			money >= item_price[0])
		{
			item_is_bought_1 = true;
			bomb_num = bomb_num + 1;
			money = money - item_price[0];
			CAudio::Instance()->Play(4);
		}
		if (point.x >= item_2.GetLeft() &&
			point.x <= item_2.GetLeft() + item_2.GetWidth() &&
			point.y >= item_2.GetTop() &&
			point.y <= item_2.GetTop() + item_2.GetHeight() &&
			!item_is_bought_2 && item_in_stock_in_level[1] &&
			money >= item_price[1])
		{
			item_is_bought_2 = true;
			item_2_effect = true;
			money = money - item_price[1];
			CAudio::Instance()->Play(4);
		}
		if (point.x >= item_3.GetLeft() &&
			point.x <= item_3.GetLeft() + item_3.GetWidth() &&
			point.y >= item_3.GetTop() &&
			point.y <= item_3.GetTop() + item_3.GetHeight() &&
			!item_is_bought_3 && item_in_stock_in_level[2] &&
			money >= item_price[2])
		{
			item_is_bought_3 = true;
			item_3_effect = true;
			money = money - item_price[2];
			CAudio::Instance()->Play(4);
		}
		if (point.x >= item_4.GetLeft() &&
			point.x <= item_4.GetLeft() + item_4.GetWidth() &&
			point.y >= item_4.GetTop() &&
			point.y <= item_4.GetTop() + item_4.GetHeight() &&
			!item_is_bought_4 && item_in_stock_in_level[3] &&
			money >= item_price[3])
		{
			item_is_bought_4 = true;
			item_4_effect = true;
			money = money - item_price[3];
			CAudio::Instance()->Play(4);
		}
		if (point.x >= item_5.GetLeft() &&
			point.x <= item_5.GetLeft() + item_5.GetWidth() &&
			point.y >= item_5.GetTop() &&
			point.y <= item_5.GetTop() + item_5.GetHeight() &&
			!item_is_bought_5 && item_in_stock_in_level[4] &&
			money >= item_price[4])
		{
			item_is_bought_5 = true;
			item_5_effect = true;
			money = money - item_price[4];
			CAudio::Instance()->Play(4);
		}
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{	
	//判別exit的位置
	if (point.x >= exit.GetLeft() && point.x <= exit.GetLeft() + exit.GetWidth() && point.y >= exit.GetTop() && point.y <= exit.GetTop() + exit.GetHeight())
	{
		exit.SetFrameIndexOfBitmap(1);
	}
	else 
	{
		exit.SetFrameIndexOfBitmap(0);
	}
	//判別next level的位置
	if (point.x >= next_level_button.GetLeft() && point.x <= next_level_button.GetLeft() + next_level_button.GetWidth() && point.y >= next_level_button.GetTop() && point.y <= next_level_button.GetTop() + next_level_button.GetHeight())
	{
		next_level_button.SetFrameIndexOfBitmap(1);
	}
	else
	{
		next_level_button.SetFrameIndexOfBitmap(0);
	}

	//判別play again
	if (point.x >= playagain_button.GetLeft() && point.x <= playagain_button.GetLeft() + playagain_button.GetWidth() &&
		point.y >= playagain_button.GetTop() && point.y <= playagain_button.GetTop() + playagain_button.GetHeight())
	{
		playagain_button.SetFrameIndexOfBitmap(1);
	}
	else
	{
		playagain_button.SetFrameIndexOfBitmap(0);
	}
		
	if (sub_phase == 3 && !success.IsAnimation()) {
		if (point.x >= item_1.GetLeft() &&
			point.x <= item_1.GetLeft() + item_1.GetWidth() &&
			point.y >= item_1.GetTop() &&
			point.y <= item_1.GetTop() + item_1.GetHeight() &&
			!item_is_bought_1 && item_in_stock_in_level[0])
		{
			item_mouse_on = 1;
		}
		if (point.x >= item_2.GetLeft() &&
			point.x <= item_2.GetLeft() + item_2.GetWidth() &&
			point.y >= item_2.GetTop() &&
			point.y <= item_2.GetTop() + item_2.GetHeight()	&&
			!item_is_bought_2 && item_in_stock_in_level[1])
		{
			item_mouse_on = 2;
		}
		if (point.x >= item_3.GetLeft() &&
			point.x <= item_3.GetLeft() + item_3.GetWidth() &&
			point.y >= item_3.GetTop() &&
			point.y <= item_3.GetTop() + item_3.GetHeight() &&
			!item_is_bought_3 && item_in_stock_in_level[2])
		{
			item_mouse_on = 3;
		}
		if (point.x >= item_4.GetLeft() &&
			point.x <= item_4.GetLeft() + item_4.GetWidth() &&
			point.y >= item_4.GetTop() &&
			point.y <= item_4.GetTop() + item_4.GetHeight() &&
			!item_is_bought_4 && item_in_stock_in_level[3])
		{
			item_mouse_on = 4;
		}
		if (point.x >= item_5.GetLeft() &&
			point.x <= item_5.GetLeft() + item_5.GetWidth() &&
			point.y >= item_5.GetTop() &&
			point.y <= item_5.GetTop() + item_5.GetHeight() &&
			!item_is_bought_5 && item_in_stock_in_level[4])
		{
			item_mouse_on = 5;
		}
	}
	
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{

}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	show_image_by_phase();

	if (sub_phase == 2){
		if ((clock() % 1000) > 700 && timer <= 10 && timer > 0) {
			timer_bling.ShowBitmap();
		}
		show_mine_caught();
		if (claw_is_ready == false) {
			clawhead.ShowBitmap();
			hitbox.ShowBitmap();
			shoot_claw_by_angle();
			show_line();
		}
		if (hit == true) {
			pull_claw();
			hitbox.SetTopLeft(507, 90);
		}
		if (miss == true) {
			weight = 0;
			money_gain = 0;
			pull_claw();
			hitbox.SetTopLeft(507, 90);
		}
		if (money_gain_flag == true) {
			show_text_of_money_gain();
		}
		if (bomb_is_throw == true) {
			bomb.ShowBitmap();
			throw_bomb();
		}
		if (bomb_explosion.IsAnimation())
		{
			bomb_explosion.ShowBitmap();
		}
		
	}

	show_text_by_phase();

	if (gameover == true) {
		gameover_and_restart();
	}

}

void CGameStateRun::show_image_by_phase() {

	if (sub_phase == 1) 
	{
		gameover = false;
		goal.ShowBitmap();
		show_text_of_goals();
		if (goal.GetFrameIndexOfBitmap() == 0 && goal.IsAnimation() == false)
		{

			CAudio::Instance()->Play(0);

			goal.ToggleAnimation();
			fade_rate = 1;
			mine_random_num = rand() % 3 + 1;
			set_mines();
			set_bombs_image();
		}
	}
	if (sub_phase == 2) 
	{
		goal.UnshowBitmap();
		background.ShowBitmap();
		exit.ShowBitmap();
		show_mines();
		wood.ShowBitmap();
		if (bonus_bomb.IsAnimation() == false && bonus_bomb.GetFrameIndexOfBitmap() != 0) {
			set_bombs_image();
		}
		number_of_bombs.ShowBitmap();
		

		if (action_state == 1) 
		{
			miner.ShowBitmap();
		}

		if (action_state == 2) 
		{
			miner.UnshowBitmap();
			miner_t.ShowBitmap();

			if (miner_t.GetFrameIndexOfBitmap() == 0 && miner_t.IsAnimation() == false)
			{
				miner_t.ToggleAnimation();
			}
			if (miner_t.IsAnimation() == false && goal.GetFrameIndexOfBitmap() != 0)
			{
				miner_t.UnshowBitmap();
				miner.ShowBitmap();
				action_state = 1;
				miner_t.SetFrameIndexOfBitmap(0);
			}
		}
		if (action_state == 3)
		{
			miner.UnshowBitmap();
			miner_s.ShowBitmap();

			if (miner_s.GetFrameIndexOfBitmap() == 0 && miner_s.IsAnimation() == false)
			{
				CAudio::Instance()->Play(5);
				miner_s.ToggleAnimation();
				bonus_strength.ToggleAnimation();
			}
			if (miner_s.IsAnimation() == false && goal.GetFrameIndexOfBitmap() != 0)
			{
				miner_s.UnshowBitmap();
				miner_s.ShowBitmap();
				action_state = 1;
				miner_s.SetFrameIndexOfBitmap(0);
			}
		}
		if (action_state == 4) 
		{
			miner.UnshowBitmap();
			miner_p.ShowBitmap();
			if (claw_is_ready == true) {
				action_state = 1;
			}
		}
		if (claw_is_ready == true)
		{
			claw.ShowBitmap();
		}
		bonus_strength.ShowBitmap();
		bonus_bomb.ShowBitmap();
	}
	if (sub_phase == 3)
	{
		//把沒炸完的炸藥桶炸完(在背景跑完動畫，方便在下一關重置)
		for (int i = 0; i < mine_num_now[7]; i++) {
			if (explosion[i].IsAnimation()) {
				explosion[i].ShowBitmap();
			}
		}
		if (success.GetFrameIndexOfBitmap() == 0 && success.IsAnimation() == false)
		{
			CAudio::Instance()->Play(1);
			success.ToggleAnimation();
			set_item_price();
			/*初始化物品是否有被點擊*/
			item_is_bought_1 = false;
			item_is_bought_2 = false;
			item_is_bought_3 = false;
			item_is_bought_4 = false;
			item_is_bought_5 = false;

			item_2_effect = false;
			item_3_effect = false;
			item_4_effect = false;
			item_5_effect = false;
		}
		//跳出來next level 畫面
		if (success.IsAnimation() == true)  
		{
			success.ShowBitmap();
		}
		//顯示商店
		if (success.IsAnimation() == false && success.GetFrameIndexOfBitmap() != 0)
		{
			shop_bg.ShowBitmap();
			next_level_button.ShowBitmap();

			if (next_level_button_clicked == false) //避免老闆生氣時或老闆開心時的圖片跳出，原本圖片仍存在
			{
				owner_talk.ShowBitmap();
			}
			if (owner_talk.GetFrameIndexOfBitmap() == 0 && owner_talk.IsAnimation() == false) 
			{
				owner_talk.ToggleAnimation();
			}
			set_last_time_audio();
			set_stock();
			show_items();
			show_description_of_item();
		}
		/*老闆開心*/
		if (next_level_button_clicked == true && (item_is_bought_1 == true || item_is_bought_2 == true || item_is_bought_3 == true || item_is_bought_4 == true || item_is_bought_5 == true) )
		{
			owner_buy.ShowBitmap();
			if (owner_buy.GetFrameIndexOfBitmap() == 0 && owner_buy.IsAnimation() == false)
			{
				owner_buy.ToggleAnimation();
				
				/*讓物品消失*/
				item_is_bought_1 = true;
				item_is_bought_2 = true;
				item_is_bought_3 = true;
				item_is_bought_4 = true;
				item_is_bought_5 = true;
				
			}
		}
		/*沒買商品*/
		if (next_level_button_clicked == true && (item_is_bought_1 == false && item_is_bought_2 == false && item_is_bought_3 == false && item_is_bought_4 == false && item_is_bought_5 == false))
		{
			owner_angry.ShowBitmap();
			if (owner_angry.GetFrameIndexOfBitmap() == 0 && owner_angry.IsAnimation() == false)
			{
				owner_angry.ToggleAnimation();

			}
		}
		if ((owner_buy.IsAnimation() == false && owner_buy.GetFrameIndexOfBitmap() != 0) || (owner_angry.IsAnimation() == false && owner_angry.GetFrameIndexOfBitmap() != 0))
		{
			goto_next_stage();
		}
	}
}

void CGameStateRun::set_bombs_image()
{
	if (bomb_num > 9) {
		number_of_bombs.SetFrameIndexOfBitmap(8);
	}
	else {
		number_of_bombs.SetFrameIndexOfBitmap(bomb_num);
	}
}

void CGameStateRun::shoot_claw_by_angle()
{
	if (!hit && !miss) {
		if (clock() - last_time_claw >= 1 && claw_length < 100)
		{
			claw_x = claw_x + (int)(sin(angles[key_down_index] * rad) * 8 );
			claw_y = claw_y + (int)(cos(angles[key_down_index] * rad) * 8 );
			clawhead.SetTopLeft(claw_x, claw_y);
			hitbox.SetTopLeft(claw_x + 43 - 21 + (int)(11 * (sin(angles[key_down_index] * rad))), claw_y + 5 + (int)(11 * (cos(angles[key_down_index] * rad))));

			claw_xway[claw_length] = claw_x;
			claw_yway[claw_length] = claw_y;

			claw_length = claw_length + 1;
			last_time_claw = clock();
		}
		else if(claw_length >= 100){
			miss = true;
		}
	}
}

void CGameStateRun::pull_claw()
{
	int miss_speedup = miss ? 1 : 0;
	int s = item_2_effect ? 5 : 1;
	if(!miss && !bomb_is_throw) action_state = 4;
	if (clock() - last_time_claw >= (1*weight/s) && claw_length > 0 )
	{
		claw_length = claw_length - 1 - miss_speedup;
		clawhead.SetTopLeft(claw_xway[claw_length], claw_yway[claw_length]);
		last_time_claw = clock();
	}
	else if (claw_length <= 0){
		//抓到道具袋(money_gain為-1)，第一關第一次一定是力量藥，後面關卡1/2機率是力量藥，1/3是炸藥，剩下是錢
		if (money_gain < 0) {
			if ( phase == 1 && item_2_effect == false || ( (clock() % 6 <= 2) && item_2_effect == false)){
				item_2_effect = true;
				action_state = 3;
				money_gain = 0;
			}
			else if (clock() % 6 <= 1) {
				bomb_num = bomb_num + 1;
				CAudio::Instance()->Play(5);
				money_gain = 0;
				bonus_bomb.ShowBitmap();
			}
			else {
				money_gain = clock() % 800;
			}
		}
		//抓到其他，或是道具袋骰到錢
		if (money_gain > 0) {
			money_gain_flag = true;
			CAudio::Instance()->Play(3);
		}
		money = money + money_gain;
		reset_claw();
	}
	set_last_time_audio();
}

void CGameStateRun::show_mine_caught()
{
	mine_caught.ShowBitmap();
	if (claw_is_ready == false) {
		int x = clawhead.GetLeft() + 43 - mine_caught.GetWidth() / 2 + (int)(sin(angles[key_down_index] * rad) * mine_caught.GetWidth() * 0.5);
		int y = clawhead.GetTop() + 36 - mine_caught.GetHeight() / 2 + (int)(cos(angles[key_down_index] * rad) * mine_caught.GetHeight() * 0.5) - 5;
		mine_caught.SetTopLeft(x, y);
	}
}

void CGameStateRun::reset_claw() 
{
	claw_length = 0;
	claw_x = 507;
	claw_y = 90;
	clawhead.SetTopLeft(claw_x, claw_y);
	mine_caught.SetFrameIndexOfBitmap(0);
	mine_caught.SetTopLeft(0, 0);
	hitbox.SetTopLeft(claw_x, claw_y);
	claw_is_ready = true;
	hit = false;
	miss = false;
	miner.SetFrameIndexOfBitmap(0);
}

void CGameStateRun::show_line() {
	for (int i = 0; i < 100; i++) {
		if (i < claw_length) {
			line[i].SetTopLeft(claw_xway[i]+43, claw_yway[i]+17);
			line[i].ShowBitmap();

			int x = line[i].GetLeft();
			int y = line[i].GetTop();

			if (angles[key_down_index] < 55 && angles[key_down_index] > -55) {
				y += +line[i].GetHeight();
				if (angles[key_down_index] > 30) {
					x += line[i].GetWidth();
				}
				if (angles[key_down_index] < -30) {
					x -= line[i].GetWidth();
				}
				line2[i].SetTopLeft(x, y);
				line2[i].ShowBitmap();

				y += +line[i].GetHeight();
				if (angles[key_down_index] > 30) {
					x += line[i].GetWidth();
				}
				if (angles[key_down_index] < -30) {
					x -= line[i].GetWidth();
				}
				line3[i].SetTopLeft(x, y);
				line3[i].ShowBitmap();
			}
			else {
				if (angles[key_down_index] > 30) {
					x += line[i].GetWidth();
				}
				if (angles[key_down_index] < -30) {
					x -= line[i].GetWidth();
				}
				line2[i].SetTopLeft(x, y);
				line2[i].ShowBitmap();

				if (angles[key_down_index] > 30) {
					x += line[i].GetWidth();
				}
				if (angles[key_down_index] < -30) {
					x -= line[i].GetWidth();
				}
				line3[i].SetTopLeft(x, y);
				line3[i].ShowBitmap();
			}

		}
	}
}

void CGameStateRun::throw_bomb() 
{


	if (clock() - last_time_bomb >= 1)
	{
		bomb_x = bomb_x + (int)(sin(angles[key_down_index] * rad) * 16);
		bomb_y = bomb_y + (int)(cos(angles[key_down_index] * rad) * 16);
		bomb.SetTopLeft(bomb_x, bomb_y);

		last_time_bomb = clock();
	}
	
	//炸藥炸到礦物
	if (bomb.GetTop() >= clawhead.GetTop()) {
		bomb_explosion.ToggleAnimation();
		bomb_explosion.SetTopLeft(claw_xway[claw_length]+ (int)sin(angles[key_down_index] * rad) -22, claw_yway[claw_length]+ (int)cos(angles[key_down_index] * rad));
		reset_bomb();
		reset_claw();
		CAudio::Instance()->Play(8);
	}
	set_bombs_image();
}

void CGameStateRun::reset_bomb()
{
	bomb_is_throw = false;
	bomb_x = 507;
	bomb_y = 90;
	bomb.SetTopLeft(bomb_x, bomb_y);
}

void CGameStateRun::set_stock()
{
	int stock_sheet[10][5] = {  {1,1,1,1,1},
								{1,0,0,1,0},
								{0,1,0,1,1},
								{1,0,1,0,0},
								{0,1,1,0,1},
								{1,0,1,1,0},
								{0,1,1,1,1},
								{1,1,0,0,0},
								{0,1,0,0,1},
								{1,1,0,1,0} };

	for (int item_num = 0; item_num < 5; item_num++) {
		item_in_stock_in_level[item_num] = stock_sheet[phase-1][item_num];
	}
}

void CGameStateRun::set_item_price() 
{
	for (int i = 0; i < 5; i++) {
		item_price[i] = (rand() % 350) + 1;			//最低1元起跳，最高290，
		if (phase <= 5 && item_price[i] > 290) {	//提高前五關商品低於100元的機率
			item_price[i] = (rand() % 100) + 1;
		}
		else {
			item_price[i] = (rand() % 290) + 1;
		}
	}
}

void CGameStateRun::show_items() 
{	
	if (item_is_bought_1 == false && item_in_stock_in_level[0] == 1) {
		item_1.ShowBitmap();
	}
	if (item_is_bought_2 == false && item_in_stock_in_level[1] == 1) {
		item_2.ShowBitmap();
	}
	if (item_is_bought_3 == false && item_in_stock_in_level[2] == 1) {
		item_3.ShowBitmap();
	}
	if (item_is_bought_4 == false && item_in_stock_in_level[3] == 1) {
		item_4.ShowBitmap();
	}
	if (item_is_bought_5 == false && item_in_stock_in_level[4] == 1) {
		item_5.ShowBitmap();
	}

}

void CGameStateRun::set_goal_money()
{
	goal_money = goal_money + 5 + 270 * phase;

}

void CGameStateRun::gameover_and_restart()
{
	if (!win) {
		fail.ShowBitmap();

		if (fail.GetFrameIndexOfBitmap() == 0 && fail.IsAnimation() == false) {
			fail.ToggleAnimation();
		}
	}

	CAudio::Instance()->Pause();
	if (fail.IsAnimation() == false && fail.GetFrameIndexOfBitmap() != 0 || win) {
		exit_background.ShowBitmap();
		playagain_button.ShowBitmap();

		CDC *pDC = CDDraw::GetBackCDC();
		CTextDraw::ChangeFontLog(pDC, 25, "calibri", RGB(0, 0, 0), 45000);
		CTextDraw::Print(pDC, 180, 673, "play again");
		if (win) {
			CTextDraw::ChangeFontLog(pDC, 25, "calibri", RGB(0, 0, 0), 45000);
			CTextDraw::Print(pDC, 180, 648, "You win!!");
		}
		CDDraw::ReleaseBackCDC();

		if (return_game == true) 
		{
			//reset_mines();
			reset_claw();
			fail.SetFrameIndexOfBitmap(0);
			goal.SetFrameIndexOfBitmap(0);
			background.SetFrameIndexOfBitmap(0);
			owner_buy.SetFrameIndexOfBitmap(0);
			owner_angry.SetFrameIndexOfBitmap(0);
			item_mouse_on = -1;
			money = 0;
			new_money = 0;
			sub_phase = 1;
			timer = 61;
			phase = 1;
			goal_money = 650;
			bomb_num = 0;
			return_game = false;
			win = false;
			GotoGameState(GAME_STATE_INIT);
		}

	}
}

void CGameStateRun::goto_next_stage()
{
	timer = 61;
	fade_rate = 1;
	goal.SetFrameIndexOfBitmap(0);
	goal.ToggleAnimation();					//為何要加這行才會動，奇怪
	success.SetFrameIndexOfBitmap(0);
	sub_phase = 1;
	phase = phase + 1;
	background.SetFrameIndexOfBitmap(phase-1);
	owner_talk.SetFrameIndexOfBitmap(0);
	owner_buy.SetFrameIndexOfBitmap(0);
	owner_angry.SetFrameIndexOfBitmap(0);
	item_mouse_on = -1;
	next_level_button_clicked = false;
	set_goal_money();
	set_bombs_image();

	new_money = money;
	timer_of_money_gain_text = 50;
	money_gain_flag = false;

	CAudio::Instance()->Play(0);
	reset_claw();
	mine_random_num = rand() % 3 + 1;
	set_mines();

}

void CGameStateRun::show_text_by_phase() {
	
	CDC *pDC = CDDraw::GetBackCDC();

	//CTextDraw::ChangeFontLog(pDC, 20, "新細明體", RGB(255, 0, 0), 15000);
	//CTextDraw::Print(pDC, 10, 10, std::to_string((int)(sin(angles[key_down_index] * rad )* mine_caught.GetWidth())));
	//CTextDraw::Print(pDC, 30, 10, std::to_string(hit));

	
	if (sub_phase == 2 && timer > 0) {

		CTextDraw::ChangeFontLog(pDC, 25, "新細明體", RGB(255, 102, 0), 15000);
		CTextDraw::Print(pDC, 1033, 10, std::to_string(timer));

		
		if (clock() - last_time >= 1000)
		{	
	
			timer -= 1;
			last_time = clock();
		}

		CTextDraw::Print(pDC, 1033, 58, std::to_string(phase));

		CTextDraw::ChangeFontLog(pDC, 25, "新細明體", RGB(0, 0, 0), 15000);
		CTextDraw::Print(pDC, 140, 12, std::to_string(new_money));
		CTextDraw::ChangeFontLog(pDC, 25, "新細明體", RGB(0, 153, 0), 15000);
		CTextDraw::Print(pDC, 140, 10, std::to_string(new_money));

		CTextDraw::ChangeFontLog(pDC, 25, "新細明體", RGB(0, 0, 0), 15000);
		CTextDraw::Print(pDC, 138, 62, std::to_string(goal_money));
		CTextDraw::ChangeFontLog(pDC, 25, "新細明體", RGB(255, 153, 0), 15000);
		CTextDraw::Print(pDC, 138, 60, std::to_string(goal_money));

		//CTextDraw::ChangeFontLog(pDC, 25, "新細明體", RGB(0, 0, 0), 15000);
		//CTextDraw::Print(pDC, 700, 60, std::to_string(bomb_num));


	}
	if (sub_phase == 3 && !success.IsAnimation()) {

		string s = "$" ;

		string str1; str1 += s; str1 += std::to_string(item_price[0]);
		if (!item_is_bought_1 && item_in_stock_in_level[0]) {
			CTextDraw::ChangeFontLog(pDC, 15, "新細明體", RGB(0, 153, 0), 15000);
			CTextDraw::Print(pDC, 100, 580, str1);
		}

		string str2; str2 += s; str2 += std::to_string(item_price[1]);
		if (!item_is_bought_2 && item_in_stock_in_level[1]) {
			CTextDraw::ChangeFontLog(pDC, 15, "新細明體", RGB(0, 153, 0), 15000);
			CTextDraw::Print(pDC, 240, 580, str2);
		}

		string str3; str3 += s; str3 += std::to_string(item_price[2]);
		if (!item_is_bought_3 && item_in_stock_in_level[2]) {
			CTextDraw::ChangeFontLog(pDC, 15, "新細明體", RGB(0, 153, 0), 15000);
			CTextDraw::Print(pDC, 380, 580, str3);
		}

		string str4; str4 += s; str4 += std::to_string(item_price[3]);
		if (!item_is_bought_4 && item_in_stock_in_level[3]) {
			CTextDraw::ChangeFontLog(pDC, 15, "新細明體", RGB(0, 153, 0), 15000);
			CTextDraw::Print(pDC, 520, 580, str4);
		}

		string str5; str5 += s; str5 += std::to_string(item_price[4]);
		if (!item_is_bought_5 && item_in_stock_in_level[4]) {
			CTextDraw::ChangeFontLog(pDC, 15, "新細明體", RGB(0, 153, 0), 15000);
			CTextDraw::Print(pDC, 660, 580, str5);
		}

	}

	CDDraw::ReleaseBackCDC();
	
}

void CGameStateRun::show_description_of_item() {
	CDC *pDC = CDDraw::GetBackCDC();
	string description1;
	string description2;
	string description3;
	switch (item_mouse_on) {
		case 1:
			description1 = "After you have grabbed onto something with your claw, press the";
			description2 = "up arrow to throw a piece of dynamite at it and blow it up.";
			description3 = " ";
			break;
		case 2:
			description1 = "Strength drink.The Miner will reel up objects a little faster on";
			description2 = "the next level.The drink only lasts for one level.";
			description3 = " ";
			break;
		case 3:
			description1 = "Lucky Clover. This will increase the chances of getting something";
			description2 = "good out of the grab bags on the next level. This is only good for";
			description3 = "one level.";
			break;
		case 4:
			description1 = "Rock Collectors book. Rocks will be worth three times as much";
			description2 = "money on the next level. This is only good for one level.";
			description3 = " ";
			break;
		case 5:
			description1 = "Diamond Polish. Durring the next level diamonds will be worth ";
			description2 = "more money. Only good for one level";
			description3 = " ";
			break;
	}
	CTextDraw::ChangeFontLog(pDC, 18, "新細明體", RGB(253, 252, 1), 1500);
	CTextDraw::Print(pDC, 95, 630, description1);
	CTextDraw::Print(pDC, 95, 666, description2);
	CTextDraw::Print(pDC, 95, 702, description3);

	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::show_text_of_goals() {
	CDC *pDC = CDDraw::GetBackCDC();
	
	COLORREF fade_from RGB(155, 78, 0);
	COLORREF fade_to RGB(255, 255, 0);

	COLORREF fade_from2 RGB(155, 78, 0);
	COLORREF fade_to2 RGB(0, 204, 0);

	int fade_time = 800;
	int fade_interval = 20;


	if (clock() - last_time_fade >= fade_interval && fade_interval * fade_rate / fade_time < 1)
	{
		color_now1[0] = GetRValue(fade_from) + (GetRValue(fade_to) - GetRValue(fade_from))*fade_interval * fade_rate / fade_time;
		color_now1[1] = GetGValue(fade_from) + (GetGValue(fade_to) - GetGValue(fade_from))*fade_interval * fade_rate / fade_time;
		color_now1[2] = GetBValue(fade_from) + (GetBValue(fade_to) - GetBValue(fade_from))*fade_interval * fade_rate / fade_time;

		color_now2[0] = GetRValue(fade_from2) + (GetRValue(fade_to2) - GetRValue(fade_from2))*fade_interval * fade_rate / fade_time;
		color_now2[1] = GetGValue(fade_from2) + (GetGValue(fade_to2) - GetGValue(fade_from2))*fade_interval * fade_rate / fade_time;
		color_now2[2] = GetBValue(fade_from2) + (GetBValue(fade_to2) - GetBValue(fade_from2))*fade_interval * fade_rate / fade_time;


		fade_rate = fade_rate + 1;
		last_time_fade = clock();
	}
	if (fade_interval * fade_rate / fade_time >= 1) {
		color_now1[0] = GetRValue(fade_to);
		color_now1[1] = GetGValue(fade_to);
		color_now1[2] = GetBValue(fade_to);

		color_now2[0] = GetRValue(fade_to2);
		color_now2[1] = GetGValue(fade_to2);
		color_now2[2] = GetBValue(fade_to2);
	}


	if (phase == 1) {
		CTextDraw::ChangeFontLog(pDC, 50, "新細明體", RGB(color_now1[0], color_now1[1], color_now1[2]), 45000);
		CTextDraw::Print(pDC, 350, 250, "Your First Goal is");
	}
	else {
		CTextDraw::ChangeFontLog(pDC, 50, "新細明體", RGB(color_now1[0], color_now1[1], color_now1[2]), 45000);
		CTextDraw::Print(pDC, 350, 250, "Your Next Goal is");
	}
	
	
	CTextDraw::ChangeFontLog(pDC, 60, "新細明體", RGB(color_now2[0], color_now2[1], color_now2[2]), 45000);
	CTextDraw::Print(pDC, 490, 340, std::to_string(goal_money));

	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::show_text_of_money_gain() {
	CDC *pDC = CDDraw::GetBackCDC();
	
	int p1[3] = { 507,90,1 };
	int p2[3] = { 300,20,35 };
	int p3[3] = { 140,10,25 };
	
	if (clock() - last_time_money_gain >= 0)
	{
		timer_of_money_gain_text = timer_of_money_gain_text - 1;

		if (timer_of_money_gain_text > 40) {
			font[0] = (int)((p1[0] * (timer_of_money_gain_text - 40) + (50 - timer_of_money_gain_text)*p2[0]) / 10);
			font[1] = (int)((p1[1] * (timer_of_money_gain_text - 40) + (50 - timer_of_money_gain_text)*p2[1]) / 10);
			font[2] = (int)((p1[2] * (timer_of_money_gain_text - 40) + (50 - timer_of_money_gain_text)*p2[2]) / 10);
		}
		if (timer_of_money_gain_text > 0 && timer_of_money_gain_text < 20) {
			font[0] = (int)((p2[0] * (timer_of_money_gain_text - 0) + (20 - timer_of_money_gain_text)*p3[0]) / 20);
			font[1] = (int)((p2[1] * (timer_of_money_gain_text - 0) + (20 - timer_of_money_gain_text)*p3[1]) / 20);
			font[2] = (int)((p2[2] * (timer_of_money_gain_text - 0) + (20 - timer_of_money_gain_text)*p3[2]) / 20);
		}
		

		if (timer_of_money_gain_text == 0) {
			new_money = money;
			timer_of_money_gain_text = 50;
			money_gain_flag = false;
			CAudio::Instance()->Play(4);
		}
		last_time_money_gain = clock();
	}
	
	string s = "$"; s += std::to_string(money_gain);
	
	CTextDraw::ChangeFontLog(pDC, font[2], "新細明體", RGB(0, 0, 0), 15000);
	CTextDraw::Print(pDC, font[0], font[1]+2, s);
	CTextDraw::ChangeFontLog(pDC, font[2], "新細明體", RGB(0, 153, 0), 15000);
	CTextDraw::Print(pDC, font[0], font[1], s);


	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::load_mines()
{
	for (int i = 0; i < mine_max_num[0]; i++) {
		mine2[i].LoadBitmapByString({ "resources/mines/2.bmp" }, RGB(0, 0, 0));
		mine2[i].SetTopLeft(-1000, -1000);
	}
	for (int i = 0; i < mine_max_num[1]; i++) {
		mine3[i].LoadBitmapByString({ "resources/mines/3.bmp" }, RGB(0, 0, 0));
		mine3[i].SetTopLeft(-1000, -1000);
	}
	for (int i = 0; i < mine_max_num[2]; i++) {
		mine4[i].LoadBitmapByString({ "resources/mines/4.bmp" }, RGB(0, 0, 0));
		mine4[i].SetTopLeft(-1000, -1000);
	}
	for (int i = 0; i < mine_max_num[3]; i++) {
		mine5[i].LoadBitmapByString({ "resources/mines/5.bmp" }, RGB(0, 0, 0));
		mine5[i].SetTopLeft(-1000, -1000);
	}
	for (int i = 0; i < mine_max_num[4]; i++) {
		mine6[i].LoadBitmapByString({ "resources/mines/6/1.bmp","resources/mines/6/2.bmp","resources/mines/6/3.bmp","resources/mines/6/4.bmp","resources/mines/6/5.bmp","resources/mines/6/6.bmp","resources/mines/6/7.bmp","resources/mines/6/1.bmp","resources/mines/6/2.bmp","resources/mines/6/3.bmp","resources/mines/6/4.bmp","resources/mines/6/5.bmp","resources/mines/6/6.bmp","resources/mines/6/7.bmp","resources/mines/6/1.bmp","resources/mines/6/2.bmp","resources/mines/6/3.bmp","resources/mines/6/4.bmp","resources/mines/6/5.bmp","resources/mines/6/6.bmp","resources/mines/6/7.bmp","resources/mines/6/1.bmp","resources/mines/6/2.bmp","resources/mines/6/3.bmp","resources/mines/6/4.bmp","resources/mines/6/5.bmp","resources/mines/6/6.bmp","resources/mines/6/7.bmp","resources/mines/6/1.bmp","resources/mines/6/2.bmp","resources/mines/6/3.bmp","resources/mines/6/4.bmp","resources/mines/6/5.bmp","resources/mines/6/6.bmp","resources/mines/6/7.bmp","resources/mines/6/1.bmp","resources/mines/6/2.bmp","resources/mines/6/3.bmp","resources/mines/6/4.bmp","resources/mines/6/5.bmp","resources/mines/6/6.bmp","resources/mines/6/7.bmp","resources/mines/6/8.bmp","resources/mines/6/9.bmp","resources/mines/6/10.bmp","resources/mines/6/11.bmp","resources/mines/6/12.bmp","resources/mines/6/13.bmp","resources/mines/6/14.bmp","resources/mines/6/8.bmp","resources/mines/6/9.bmp","resources/mines/6/10.bmp","resources/mines/6/11.bmp","resources/mines/6/12.bmp","resources/mines/6/13.bmp","resources/mines/6/14.bmp","resources/mines/6/8.bmp","resources/mines/6/9.bmp","resources/mines/6/10.bmp","resources/mines/6/11.bmp","resources/mines/6/12.bmp","resources/mines/6/13.bmp","resources/mines/6/14.bmp","resources/mines/6/8.bmp","resources/mines/6/9.bmp","resources/mines/6/10.bmp","resources/mines/6/11.bmp","resources/mines/6/12.bmp","resources/mines/6/13.bmp","resources/mines/6/14.bmp","resources/mines/6/8.bmp","resources/mines/6/9.bmp","resources/mines/6/10.bmp","resources/mines/6/11.bmp","resources/mines/6/12.bmp","resources/mines/6/13.bmp","resources/mines/6/14.bmp","resources/mines/6/8.bmp","resources/mines/6/9.bmp","resources/mines/6/10.bmp","resources/mines/6/11.bmp","resources/mines/6/12.bmp","resources/mines/6/13.bmp","resources/mines/6/14.bmp" }, RGB(0, 0, 0));
		mine6[i].SetTopLeft(-1000, -1000);
		mine6[i].SetAnimation(200, false);
	}
	for (int i = 0; i < mine_max_num[5]; i++) {
		mine7[i].LoadBitmapByString({ "resources/mines/7.bmp" }, RGB(0, 0, 0));
		mine7[i].SetTopLeft(-1000, -1000);
	}
	for (int i = 0; i < mine_max_num[6]; i++) {
		mine8[i].LoadBitmapByString({ "resources/mines/8.bmp" }, RGB(0, 0, 0));
		mine8[i].SetTopLeft(-1000, -1000);
	}
	for (int i = 0; i < mine_max_num[7]; i++) {
		mine9[i].LoadBitmapByString({ "resources/mines/9.bmp" }, RGB(0, 0, 0));
		mine9[i].SetTopLeft(-1000, -1000);
	}
	for (int i = 0; i < mine_max_num[8]; i++) {
		mine10[i].LoadBitmapByString({ "resources/mines/10/1.bmp","resources/mines/10/2.bmp","resources/mines/10/3.bmp","resources/mines/10/4.bmp","resources/mines/10/5.bmp","resources/mines/10/6.bmp","resources/mines/10/7.bmp","resources/mines/10/1.bmp","resources/mines/10/2.bmp","resources/mines/10/3.bmp","resources/mines/10/4.bmp","resources/mines/10/5.bmp","resources/mines/10/6.bmp","resources/mines/10/7.bmp","resources/mines/10/1.bmp","resources/mines/10/2.bmp","resources/mines/10/3.bmp","resources/mines/10/4.bmp","resources/mines/10/5.bmp","resources/mines/10/6.bmp","resources/mines/10/7.bmp","resources/mines/10/1.bmp","resources/mines/10/2.bmp","resources/mines/10/3.bmp","resources/mines/10/4.bmp","resources/mines/10/5.bmp","resources/mines/10/6.bmp","resources/mines/10/7.bmp","resources/mines/10/1.bmp","resources/mines/10/2.bmp","resources/mines/10/3.bmp","resources/mines/10/4.bmp","resources/mines/10/5.bmp","resources/mines/10/6.bmp","resources/mines/10/7.bmp","resources/mines/10/1.bmp","resources/mines/10/2.bmp","resources/mines/10/3.bmp","resources/mines/10/4.bmp","resources/mines/10/5.bmp","resources/mines/10/6.bmp","resources/mines/10/7.bmp","resources/mines/10/8.bmp","resources/mines/10/9.bmp","resources/mines/10/10.bmp","resources/mines/10/11.bmp","resources/mines/10/12.bmp","resources/mines/10/13.bmp","resources/mines/10/14.bmp","resources/mines/10/8.bmp","resources/mines/10/9.bmp","resources/mines/10/10.bmp","resources/mines/10/11.bmp","resources/mines/10/12.bmp","resources/mines/10/13.bmp","resources/mines/10/14.bmp","resources/mines/10/8.bmp","resources/mines/10/9.bmp","resources/mines/10/10.bmp","resources/mines/10/11.bmp","resources/mines/10/12.bmp","resources/mines/10/13.bmp","resources/mines/10/14.bmp","resources/mines/10/8.bmp","resources/mines/10/9.bmp","resources/mines/10/10.bmp","resources/mines/10/11.bmp","resources/mines/10/12.bmp","resources/mines/10/13.bmp","resources/mines/10/14.bmp","resources/mines/10/8.bmp","resources/mines/10/9.bmp","resources/mines/10/10.bmp","resources/mines/10/11.bmp","resources/mines/10/12.bmp","resources/mines/10/13.bmp","resources/mines/10/14.bmp","resources/mines/10/8.bmp","resources/mines/10/9.bmp","resources/mines/10/10.bmp","resources/mines/10/11.bmp","resources/mines/10/12.bmp","resources/mines/10/13.bmp","resources/mines/10/14.bmp" }, RGB(0, 0, 0));
		mine10[i].SetTopLeft(-1000, -1000);
		mine10[i].SetAnimation(200, false);
	}
	for (int i = 0; i < mine_max_num[9]; i++) {
		mine11[i].LoadBitmapByString({ "resources/mines/11.bmp" }, RGB(0, 0, 0));
		mine11[i].SetTopLeft(-1000, -1000);
		explosion[i].LoadBitmapByString({ "resources/mines/9_2/1.bmp", "resources/mines/9_2/2.bmp", "resources/mines/9_2/3.bmp", "resources/mines/9_2/4.bmp", "resources/mines/9_2/5.bmp", "resources/mines/9_2/6.bmp", "resources/mines/9_2/7.bmp", "resources/mines/9_2/8.bmp", "resources/mines/9_2/9.bmp", "resources/mines/9_2/10.bmp", "resources/mines/9_2/11.bmp", "resources/mines/9_2/12.bmp" }, RGB(0, 0, 0));
		explosion[i].SetTopLeft(-1000, -1000);
		explosion[i].SetAnimation(100, true);
	}
	for (int i = 0; i < mine_max_num[10]; i++) {
		mine12[i].LoadBitmapByString({ "resources/mines/12.bmp" }, RGB(0, 0, 0));
		mine12[i].SetTopLeft(-1000, -1000);
	}
	for (int i = 0; i < mine_max_num[11]; i++) {
		mine13[i].LoadBitmapByString({ "resources/mines/13.bmp" }, RGB(0, 0, 0));
		mine13[i].SetTopLeft(-1000, -1000);
	}
	for (int i = 0; i < mine_max_num[12]; i++) {
		mine14[i].LoadBitmapByString({ "resources/mines/14.bmp" }, RGB(0, 0, 0));
		mine14[i].SetTopLeft(-1000, -1000);
	}


};

void CGameStateRun::show_mines()
{

	if (phase == 1) {
		if (mine_random_num == 1) {

			int location2[10][2] = { {250,350},{350,500},{750,350},{850,300} };	//金礦(小)
			int location3[10][2] = { {130,700},{600,400},{950,600} };	//金礦(中)
			int location5[10][2] = { {130,500},{600,550} };	//金礦(巨大)
			int location8[10][2] = { {530,650},{700,450} };	//石頭(大)
			int location12[10][2] = { {100,250},{800,330} }; //道具袋
			int location14[10][2] = { {200,230},{880,250} };	//石頭(中)
			//int location6[10][2] = { {500, 300}, {600, 400}, {700, 500} }; //豬
			//int location10[10][2] = { {500, 500}, {600, 600}, {700, 700} }; //鑽石豬


			show_mine_2(location2);
			
			show_mine_3(location3);

			show_mine_5(location5);

			show_mine_8(location8);
			/*豬*/
			//show_mine_6(location6);
			/*鑽石豬*/
			//show_mine_10(location10);
			
			show_mine_12(location12);
			
			show_mine_14(location14);
		}
		if (mine_random_num == 2) {

			int location2[10][2] = { {200,230},{340,350},{840,410},{835,350}, {888, 280} }; //金礦(小)
			int location3[10][2] = { {230,600}, {450, 560},{620, 360} }; //金礦(中)
			int location5[10][2] = { {70,400},{1000,460} }; //金礦(巨大)
			int location8[10][2] = { {330,680},{780,450} }; //石頭(大)
			//int location11[10][2] = { {770, 550} };//鑽石
			int location12[10][2] = { {750,670} }; //道具袋
			int location14[10][2] = { {110,310},{900, 230} }; //石頭(中)


			show_mine_2(location2);

			show_mine_3(location3);

			show_mine_5(location5);

			show_mine_8(location8);

			//show_mine_9(location9);

			show_mine_12(location12);

			show_mine_14(location14);
		}
		if (mine_random_num == 3)
 {

			int location2[10][2] = { {200,230},{340,350},{500,370},{690,325}, {840, 230} };	//金礦(小)
			int location3[10][2] = { {340,480},{500,500},{600,450} };	//金礦(中)
			int location5[10][2] = { {12,392},{910,420} };	//金礦(巨大)
			int location8[10][2] = { {420,650},{750,480} };	//石頭(大)
			int location12[10][2] = { {330,675}}; //道具袋
			int location14[10][2] = { {185,400},{870,275} };	//石頭(中)


			show_mine_2(location2);

			show_mine_3(location3);

			show_mine_5(location5);

			show_mine_8(location8);

			show_mine_12(location12);

			show_mine_14(location14);
		}
	}
	if (phase == 2) {
		if (mine_random_num == 1) {

			int location2[10][2] = { {200,550},{370,450},{500,350},{650,400}, {730, 580}, {830, 250}, {920, 400} }; //金礦(小)
			int location3[10][2] = { {60,300}, {950, 630} }; //金礦(中)
			int location5[10][2] = { {20,550},{670,630} }; //金礦(巨大)
			int location8[10][2] = { {120,330},{260,500}, {580, 520}, {850, 670} }; //石頭(大)
			int location11[10][2] = { {770, 550} };//鑽石
			int location12[10][2] = { {300,630} }; //道具袋
			int location14[10][2] = { {450,600},{780, 450} , {880, 300} }; //石頭(中)


			show_mine_2(location2);

			show_mine_3(location3);

			show_mine_5(location5);

			show_mine_8(location8);

			show_mine_11(location11);

			show_mine_12(location12);

			show_mine_14(location14);
		}
		if (mine_random_num == 2) {

			int location2[10][2] = { {630,465},{690,260},{730,600},{735,380}, {840, 700}, {860, 260}, {950, 410} }; //金礦(小)
			int location3[10][2] = { {660,560}, {770, 495},{950 ,500 }}; //金礦(中)
			int location5[10][2] = { {30,640},{920,660} }; //金礦(巨大)
			int location8[10][2] = { {5,385},{25,520}, {75, 230}, {290, 480} }; //石頭(大)
			int location12[10][2] = { {90,300} }; //道具袋
			int location14[10][2] = { {175,740},{205, 570},{330, 350}}; //石頭(中)


			show_mine_2(location2);

			show_mine_3(location3);

			show_mine_5(location5);

			show_mine_8(location8);

			show_mine_12(location12);

			show_mine_14(location14);
		}
		if (mine_random_num == 3) {

			int location2[10][2] = { {120,310},{370,450},{690,260},{730,600}, {735, 380}, {860, 240}, {940, 420} }; //金礦(小)
			int location3[10][2] = { {40,310}, {770, 490}, {960,660} }; //金礦(中)
			int location5[10][2] = { {60,630},{280,690} }; //金礦(巨大)
			int location8[10][2] = { {30,520},{130,350}, {290, 480}, {600, 520} }; //石頭(大)
			int location11[10][2] = { {770, 550} };//鑽石
			int location12[10][2] = { {460,610} }; //道具袋
			int location14[10][2] = { {210,570},{550, 440} , {760, 280} }; //石頭(中)


			show_mine_2(location2);

			show_mine_3(location3);

			show_mine_5(location5);

			show_mine_8(location8);

			show_mine_11(location11);

			show_mine_12(location12);

			show_mine_14(location14);
		}
	}
	if (phase == 3)
	{
		if (mine_random_num == 1) {

			int location2[10][2] = { {190,300},{190,230},{250,240},{750,400} }; //金礦(小)
			int location3[10][2] = { {120,470}, {240, 600}, {990, 385} }; //金礦(中)
			int location5[10][2] = { {520,670} }; //金礦(巨大)
			int location8[10][2] = { {170,520},{650,460}, {920, 560}, {920, 350} }; //石頭(大)
			int location11[10][2] = { {840, 590} };//鑽石
			int location12[10][2] = { {130,320} }; //道具袋
			int location14[10][2] = { {500,360},{680, 600} , {800, 430} }; //石頭(中)


			show_mine_2(location2);

			show_mine_3(location3);

			show_mine_5(location5);

			show_mine_8(location8);
			show_mine_11(location11);
			show_mine_12(location12);
			show_mine_14(location14);
		}
		if (mine_random_num == 2) {

			int location2[10][2] = { {190,230},{190,295},{250,235},{750,400} }; //金礦(小)
			int location3[10][2] = { {125,425}, {710, 680}, {990, 390} }; //金礦(中)
			int location5[10][2] = { {265,720} }; //金礦(巨大)
			int location8[10][2] = { {170,520},{730,480}, {880, 430}, {900, 520} }; //石頭(大)
			int location11[10][2] = { {840, 520} };//鑽石
			int location12[10][2] = { {100,240} }; //道具袋
			int location14[10][2] = { {530,360},{800, 430} , {800, 570} }; //石頭(中)


			show_mine_2(location2);

			show_mine_3(location3);

			show_mine_5(location5);

			show_mine_8(location8);
			show_mine_11(location11);
			show_mine_12(location12);
			show_mine_14(location14);
		}
		if (mine_random_num == 3) {

			int location2[10][2] = { {190,230},{190,295},{250,235},{750,400} }; //金礦(小)
			int location3[10][2] = { {125,425}, {810, 465}, {990, 390} }; //金礦(中)
			int location5[10][2] = { {265,720} }; //金礦(巨大)
			int location8[10][2] = { {170,520},{700,480}, {880, 430}, {900, 520} }; //石頭(大)
			int location11[10][2] = { {860, 600} };//鑽石
			int location12[10][2] = { {630,470} }; //道具袋
			int location14[10][2] = { {530,360},{560, 440} , {800, 570} }; //石頭(中)


			show_mine_2(location2);

			show_mine_3(location3);

			show_mine_5(location5);

			show_mine_8(location8);
			show_mine_11(location11);
			show_mine_12(location12);
			show_mine_14(location14);
		}
	}
	if (phase == 4)
	{
		if (mine_random_num == 1) {
			int location2[10][2] = { {210,260},{720,320},{750,340},{770,390} }; //金礦(小)
			int location3[10][2] = { {630, 390} }; //金礦(中)
			int location4[10][2] = { {290,580}, {600, 610} }; //金礦(大)
			int location6[10][2] = { {330, 550} }; //豬
			int location8[10][2] = { {180,660},{250,300}, {890, 330} }; //石頭(大)
			int location11[10][2] = { {840, 590} };//鑽石
			int location12[10][2] = { {270,440} , {470,600},{740, 480},  {830, 360} }; //道具袋
			int location14[10][2] = { {650,490} }; //石頭(中)


			show_mine_2(location2);
			show_mine_3(location3);
			show_mine_4(location4);
			show_mine_6(location6);
			show_mine_8(location8);
			show_mine_11(location11);
			show_mine_12(location12);
			show_mine_14(location14);
		}
		if (mine_random_num == 2) {
			int location2[10][2] = { {180,250},{330,250},{390,350},{740,390} }; //金礦(小)
			int location3[10][2] = { {110, 450},{660, 410}, {1000, 330} }; //金礦(中)
			int location4[10][2] = { {185,610}, {600, 580} }; //金礦(大)
			int location6[10][2] = { {105, 400}, {500, 530}, {740, 260} }; //豬
			int location8[10][2] = { {245,300},{300,700}, {890, 340} }; //石頭(大)
			int location12[10][2] = { {400,445} , {800,300} }; //道具袋
			int location14[10][2] = { {530,360} }; //石頭(中)


			show_mine_2(location2);
			show_mine_3(location3);
			show_mine_4(location4);
			show_mine_6(location6);
			show_mine_8(location8);
			show_mine_12(location12);
			show_mine_14(location14);
		}
		if (mine_random_num == 3) {
			int location2[10][2] = { {55,350},{310,560},{370,540},{740,480} }; //金礦(小)
			int location3[10][2] = { {45, 550},{680, 510}, {990, 470} }; //金礦(中)
			int location4[10][2] = { {185,610}, {600, 580} }; //金礦(大)
			int location6[10][2] = { {180, 355}, {270, 240}, {850, 290} }; //豬
			int location8[10][2] = { {115,540},{310,690}, {920, 520} }; //石頭(大)
			int location12[10][2] = { {444,584} , {830,510} }; //道具袋
			int location14[10][2] = { {530,560} }; //石頭(中)



			show_mine_2(location2);
			show_mine_3(location3);
			show_mine_4(location4);
			show_mine_6(location6);
			show_mine_8(location8);
			show_mine_12(location12);
			show_mine_14(location14);
		}
	}
	if (phase == 5)
	{
		if (mine_random_num == 1) {

			int location2[10][2] = { {180,230},{220,600},{270,250},{680,500} }; //金礦(小)
			int location3[10][2] = { {110, 450}, {390, 440}, {888, 320} }; //金礦(中)
			int location4[10][2] = { {320,670} }; //金礦(大)
			int location5[10][2] = { {-70, 600}, {1060, 530} };//金礦(巨大)
			int location6[10][2] = { {120, 380}, {990, 540} }; //豬
			int location8[10][2] = { {580,350},{810,370}, {900, 750} }; //石頭(大)
			int location11[10][2] = { {120, 650}, {880, 700}, {960, 700}, {980, 600} };//鑽石
			int location12[10][2] = { {750, 640} }; //道具袋
			int location14[10][2] = { {1000,660} }; //石頭(中)

			show_mine_2(location2);
			show_mine_3(location3);
			show_mine_4(location4);
			show_mine_5(location5);
			show_mine_6(location6);
			show_mine_8(location8);
			show_mine_11(location11);
			show_mine_12(location12);
			show_mine_14(location14);
		}
		if (mine_random_num == 2) {

			int location2[10][2] = { {180,240},{220,600},{270,250},{680,500} }; //金礦(小)
			int location3[10][2] = { {110, 450}, {390, 440}, {888, 320} }; //金礦(中)
			int location4[10][2] = { {320,670},{600, 610} }; //金礦(大)
			int location5[10][2] = { {-70, 600}, {1060, 560} };//金礦(巨大)
			int location6[10][2] = { {240, 380}, {880, 550} }; //豬
			int location8[10][2] = { {190,290},{310,510}, {810, 370} }; //石頭(大)
			int location11[10][2] = { {120, 650}, {880, 690}, {980, 600} };//鑽石
			int location12[10][2] = { {750, 640} }; //道具袋
			int location14[10][2] = { {590,490} }; //石頭(中)

			show_mine_2(location2);
			show_mine_3(location3);
			show_mine_4(location4);
			show_mine_5(location5);
			show_mine_6(location6);
			show_mine_8(location8);
			show_mine_11(location11);
			show_mine_12(location12);
			show_mine_14(location14);
		}
		if (mine_random_num == 3) {

			int location2[10][2] = { {180,240},{220,600},{460,540},{680,500} }; //金礦(小)
			int location3[10][2] = { {110, 450}, {390, 440}, {888, 320} }; //金礦(中)
			int location4[10][2] = { {380,720},{600, 610} }; //金礦(大)
			int location5[10][2] = { {-70, 600}, {800, 720} };//金礦(巨大)
			int location6[10][2] = { {240, 380}, {880, 550} }; //豬
			int location8[10][2] = { {190,290},{310,510}, {810, 370} }; //石頭(大)
			int location11[10][2] = { {30, 540}, {500, 590}, {1000, 490} };//鑽石
			int location12[10][2] = { {730, 320} }; //道具袋
			int location14[10][2] = { {590,490} }; //石頭(中)

			show_mine_2(location2);
			show_mine_3(location3);
			show_mine_4(location4);
			show_mine_5(location5);
			show_mine_6(location6);
			show_mine_8(location8);
			show_mine_11(location11);
			show_mine_12(location12);
			show_mine_14(location14);
		}
	}
	if (phase == 6)
	{
		if (mine_random_num == 1) {

			int location2[10][2] = { {130,270},{180,444},{330,550},{700,320}, {820, 540}, {830, 240}, {940, 450} }; //金礦(小)
			int location3[10][2] = { {20, 400}, {410, 320}, {910, 610} }; //金礦(中)
			int location5[10][2] = { {500, 550} };//金礦(巨大)
			int location8[10][2] = { {24,550},{420,620}, {630, 640} }; //石頭(大)
			int location10[10][2] = { {130, 380}, {780, 740} }; //鑽石豬
			int location11[10][2] = { {120, 650}, {880, 700} };//鑽石
			int location12[10][2] = { {540, 460} }; //道具袋
			int location14[10][2] = { {222,626}, {860, 660}, {1010, 600} }; //石頭(中)

			show_mine_2(location2);

			show_mine_3(location3);

			show_mine_5(location5);

			show_mine_8(location8);

			show_mine_10(location10);

			show_mine_11(location11);

			show_mine_12(location12);

			show_mine_14(location14);
		}
		if (mine_random_num == 2) {

			int location2[10][2] = { {180,440},{320,560},{375,685},{820,540}, {830, 490}, {860, 520}, {910, 530} }; //金礦(小)
			int location3[10][2] = { {140, 700}, {720, 740}, {750, 490} }; //金礦(中)
			int location5[10][2] = { {1035, 630} };//金礦(巨大)
			int location8[10][2] = { {170,270},{410,480}, {600, 710} }; //石頭(大)
			int location10[10][2] = { {70, 350}, {275, 580}, {800, 630}, {860, 390} }; //鑽石豬
			int location11[10][2] = { {120, 650}, {880, 700} };//鑽石
			int location12[10][2] = { {920, 370} }; //道具袋
			int location14[10][2] = { {200,520}, {690, 310}, {855, 235} }; //石頭(中)

			show_mine_2(location2);
			show_mine_3(location3);
			show_mine_5(location5);
			show_mine_8(location8);
			show_mine_10(location10);
			show_mine_11(location11);
			show_mine_12(location12);
			show_mine_14(location14);
		}
		if (mine_random_num == 3) {

			int location2[10][2] = { {235,565},{375,680},{670,550},{840,580}, {860, 690}, {880, 560}, {970, 620} }; //金礦(小)
			int location3[10][2] = { {20, 620}, {130, 700}, {720, 730} }; //金礦(中)
			int location5[10][2] = { {420, 680} };//金礦(巨大)
			int location8[10][2] = { {65,300},{570,505}, {1010, 510} }; //石頭(大)
			int location10[10][2] = { {50, 390}, {390, 450},{800, 610}, {1035, 385} }; //鑽石豬
			int location11[10][2] = { {120, 650}, {880, 700} };//鑽石
			int location12[10][2] = { {870, 610} }; //道具袋
			int location14[10][2] = { {160,520}, {390, 320}, {800, 310} }; //石頭(中)

			show_mine_2(location2);

			show_mine_3(location3);

			show_mine_5(location5);

			show_mine_8(location8);

			show_mine_10(location10);

			show_mine_11(location11);

			show_mine_12(location12);

			show_mine_14(location14);
		}
	}
	if (phase == 7) {
		if (mine_random_num == 1) {

			int location2[10][2] = { {100,340},{570,335} }; //金礦(小)
			int location4[10][2] = { {320,580}, {1000, 300} }; //金礦(大)
			int location5[10][2] = { {-25, 660}, {340, 720},{820, 600} };//金礦(巨大)
			int location6[10][2] = { {15, 460}, {150, 640}, {520, 510}, {625, 230}, {970, 425}, {1050, 270} }; //豬
			int location7[10][2] = { {120, 500}, {800, 360} }; // 骨頭
			int location9[10][2] = { {235, 520}, {860, 300} }; //炸藥
			int location12[10][2] = { {800, 465} }; //道具袋
			int location13[10][2] = { {310, 440}, {760, 380} }; //骷髏

			show_mine_2(location2);
			show_mine_4(location4);
			show_mine_5(location5);
			show_mine_6(location6);
			show_mine_7(location7);
			show_mine_9(location9);
			show_mine_12(location12);
			show_mine_13(location13);
			show_mine_13(location13);
		}
		if (mine_random_num == 2) {

			int location2[10][2] = { {10,460},{580,530} }; //金礦(小)
			int location4[10][2] = { {310,560}, {950, 340} }; //金礦(大)
			int location5[10][2] = { {-25, 660}, {440, 710},{600, 560} };//金礦(巨大)
			int location6[10][2] = { {10, 275}, {100, 530}, {220, 666}, {710, 305}, {920, 520}, {1030, 260} }; //豬
			int location7[10][2] = { {105, 340}, {400, 460} }; // 骨頭
			int location9[10][2] = { {290, 410}, {700, 400} }; //炸藥
			int location12[10][2] = { {210, 370} }; //道具袋
			int location13[10][2] = { {110, 615}, {820, 350} }; //骷髏


			show_mine_2(location2);
			show_mine_4(location4);
			show_mine_5(location5);
			show_mine_6(location6);
			show_mine_7(location7);
			show_mine_9(location9);
			show_mine_12(location12);
			show_mine_13(location13);
		}
		if (mine_random_num == 3) {

			int location2[10][2] = { {135,360},{580,330} }; //金礦(小)
			int location4[10][2] = { {60,245}, {990, 300} }; //金礦(大)
			int location5[10][2] = { {260, 610}, {520, 675},{760, 625} };//金礦(巨大)
			int location6[10][2] = { {15, 535}, {210, 400}, {320, 270}, {930, 440}, {1120, 260}, {1240, 550} }; //豬
			int location7[10][2] = { {790, 360}, {840, 540} }; // 骨頭
			int location9[10][2] = { {430, 570}, {666, 570} }; //炸藥
			int location12[10][2] = { {845, 365} }; //道具袋
			int location13[10][2] = { {240, 460}, {760, 390} }; //骷髏

			show_mine_2(location2);
			show_mine_4(location4);
			show_mine_5(location5);
			show_mine_6(location6);
			show_mine_9(location9);
			show_mine_12(location12);
			show_mine_13(location13);
		}
	}
	if (phase == 8)
	{
		if (mine_random_num == 1) {

			int location9[10][2] = { {90, 390}, {270, 500}, {690, 520}, {870, 300}, {930, 680} }; //炸藥
			int location10[10][2] = { {20, 400}, {170, 500} }; //鑽石豬
			int location11[10][2] = { {130, 560}, {200, 290}, {390, 590},{400, 340}, {640, 400},{645, 680}, {800, 480},{985, 240} };//鑽石
			int location12[10][2] = { {65, 685} , {1010, 580} }; //道具袋

			show_mine_9(location9);
			show_mine_10(location10);
			show_mine_11(location11);
			show_mine_12(location12);
		}
		if (mine_random_num == 2) {

			int location9[10][2] = { {230, 580}, {365, 430}, {510, 295}, {650, 430}, {770, 600} }; //炸藥
			int location10[10][2] = { {180, 570}, {290, 430}, {750, 320} }; //鑽石豬
			int location11[10][2] = { {170, 525}, {425, 745}, {470, 285},{525, 750}, {570, 260},{620, 740}, {640, 390},{830, 570} };//鑽石
			int location12[10][2] = { {10, 580} , {1010, 560} }; //道具袋

			show_mine_9(location9);

			show_mine_10(location10);
			show_mine_11(location11);

			show_mine_12(location12);
		}
		if (mine_random_num == 3) {

			int location5[10][2] = { {0, 565}, {210, 690},{470, 610}, {745, 570}, {980, 690} };//金礦(巨大)
			int location8[10][2] = { {170,490},{190,280}, {245, 420}, {400, 400}, {620, 545}, {760, 450}, {800, 280}, {980, 230}, {1045, 440} }; //石頭(大)
			int location9[10][2] = { {85, 370}, {940, 360}}; //炸藥
			int location11[10][2] = { {90, 730}, {140, 690}, {390, 590},{1050, 580}};//鑽石
			int location14[10][2] = { {35,460}, {45, 250}, {250, 380} , {440, 530}, {590, 300}, {830, 380}, {920, 480} }; //石頭(中)


			show_mine_5(location5);
			show_mine_8(location8);
			show_mine_9(location9);
			show_mine_11(location11);
			show_mine_14(location14);
		}
	}
	if (phase == 9)
	{
		if (mine_random_num == 1)
		{

			int location2[10][2] = { {500,300} }; //金礦(小)
			int location5[10][2] = { {170, 580}, {730, 600} };//金礦(巨大)
			int location7[10][2] = { {950, 650} }; // 骨頭
			int location9[10][2] = { {-22, 280}, {40, 570}, {290, 720}, {600, 720}, {900, 700}, {1065, 470}, {1060, 210} }; //炸藥
			int location10[10][2] = { {110, 430}, {250, 540} , {730, 480}, {940, 330} }; //鑽石豬
			int location11[10][2] = { {120, 650}, {120, 500}, {200, 720}, {850, 520}, {980, 400}, {1040, 650}, {1070, 370} };//鑽石
			int location12[10][2] = { {15, 370}, {380, 670}, {1000, 520} }; //道具袋
			int location13[10][2] = { {540, 600} }; //骷髏

			show_mine_2(location2);
			show_mine_5(location5);
			show_mine_7(location7);
			show_mine_9(location9);
			show_mine_10(location10);
			show_mine_11(location11);

			show_mine_12(location12);
			show_mine_13(location13);
		}
		if (mine_random_num == 2)
		{

			int location2[10][2] = { {205, 222} }; //金礦(小)
			int location5[10][2] = { {160, 580}, {730, 600} };//金礦(巨大)
			int location7[10][2] = { {950, 650} }; // 骨頭
			int location9[10][2] = { {15, 680}, {210, 270}, {380, 490}, {500, 500}, {620, 500}, {790, 260}, {1000, 690} }; //炸藥
			int location10[10][2] = { {80, 385}, {260, 520} , {750, 500}, {920, 370} }; //鑽石豬
			int location11[10][2] = { {120, 510}, {430, 760}, {450, 450}, {580, 460}, {710, 760}, {750, 330}, {1000, 630} };//鑽石
			int location12[10][2] = { {0, 370}, {510, 735}, {1000, 520} }; //道具袋
			int location13[10][2] = { {560, 635} }; //骷髏

			show_mine_2(location2);
			show_mine_5(location5);
			show_mine_7(location7);
			show_mine_9(location9);
			show_mine_10(location10);
			show_mine_11(location11);
			show_mine_12(location12);
			show_mine_13(location13);
		}
		if (mine_random_num == 3)
		{

			int location2[10][2] = { {220,340} }; //金礦(小)
			int location6[10][2] = { {170, 540}, {370, 240}, {380, 460}, {720, 380}}; //豬
			int location9[10][2] = { {500, 450}}; //炸藥
			int location10[10][2] = { {50, 680}, {75, 380} , {730, 480}, {640, 485},{980,660} }; //鑽石豬
			int location12[10][2] = { {500, 710} }; //道具袋

			show_mine_2(location2);
			show_mine_6(location6);
			show_mine_9(location9);
			show_mine_10(location10);
			show_mine_12(location12);
		}
	}
	if (phase == 10) {
		if (mine_random_num == 1) {

			int location2[10][2] = { {80,360},{220,440},{240,545},{630,450}, {750, 440}, {860, 320} }; //金礦(小)
			int location3[10][2] = { {160, 515}, {310, 660}, {430, 560}, {700, 660}, {1000, 600} }; //金礦(中)
			int location4[10][2] = { {25,444}, {230, 720}, {560, 500}, {800, 700}, {888, 360} }; //金礦(大)
			int location5[10][2] = { {60,580},{430,660}, {760, 510}, {980, 700}, {1020, 480} }; //金礦(巨大)
			int location8[10][2] = { {210,590},{215,290}, {500, 380}, {600,600}, {750, 280} }; //石頭(大)

			show_mine_2(location2);
			show_mine_3(location3);
			show_mine_4(location4);
			show_mine_5(location5);
			show_mine_8(location8);
		}
		if (mine_random_num == 2) {

			int location2[10][2] = { {490,290}}; //金礦(小)
			int location5[10][2] = { {160,580},{730,600}}; //金礦(巨大)
			int location7[10][2] = { {900, 610} }; // 骨頭
			int location8[10][2] = { {210,590},{215,290}, {500, 380}, {600,600}, {750, 280} }; //石頭(大)
			int location9[10][2] = { {35,600},{60,280},{310,280}, {405, 495},{625,670},{720,295},{890,445} }; //炸藥
			int location10[10][2] = { {110, 440}, {245, 505} , {730, 480}, {930, 330} }; //鑽石豬
			int location11[10][2] = { {90, 545}, {125, 745}, {220, 745}, {365, 400}, {580, 680}, {845, 520}, {970, 400} };//鑽石
			int location12[10][2] = { {120, 310}, {420, 620}, {870, 700} }; //道具袋
			int location13[10][2] = { {730, 530} }; //骷髏

			show_mine_2(location2);
			show_mine_5(location5);
			show_mine_7(location7);
			show_mine_8(location8);
			show_mine_9(location9);
			show_mine_10(location10);
			show_mine_11(location11);
			show_mine_12(location12);
			show_mine_13(location13);
		}
		if (mine_random_num == 3) {


			int location2[10][2] = { {490,300} }; //金礦(小)
			int location5[10][2] = { {160,580},{765,740} }; //金礦(巨大)
			int location7[10][2] = { {950, 650} }; // 骨頭
			int location8[10][2] = { {210,590},{215,290}, {500, 380}, {600,600}, {750, 280} }; //石頭(大)
			int location9[10][2] = { {75,545},{290,720},{330,330}, {500, 660},{670,590},{890,700},{1060,530} }; //炸藥
			int location10[10][2] = { {110, 440}, {240, 540} , {730, 480}, {930, 330} }; //鑽石豬
			int location11[10][2] = { {170, 525}, {300, 690}, {440, 425}, {845, 520}, {980, 400}, {1030, 680}, {1045, 400} };//鑽石
			int location12[10][2] = { {15, 310}, {380, 660}, {950, 530} }; //道具袋
			int location13[10][2] = { {550, 600} }; //骷髏

			show_mine_2(location2);
			show_mine_5(location5);
			show_mine_7(location7);
			show_mine_8(location8);
			show_mine_9(location9);
			show_mine_10(location10);
			show_mine_11(location11);
			show_mine_12(location12);
			show_mine_13(location13);
		}
	}
	set_location_of_pig();
}

void CGameStateRun::set_mines()
{
	int p = phase - 1;
	for (int i = 0; i < 13; i++) {
		switch (mine_random_num) {
		case 1:
			mine_num_now[i] = mine_num_1[p][i];
			break;
		case 2:
			mine_num_now[i] = mine_num_2[p][i];
			break;
		case 3:
			mine_num_now[i] = mine_num_3[p][i];
			break;
		}
	}
	for (int i = 0; i < mine_max_num[0]; i++) {
		if (i < mine_num_now[0]) {
			exist2[i] = 1;
			mine2[i].SetTopLeft(0, 0);
		}
		else {
			exist2[i] = 0;
			mine2[i].SetTopLeft(-1000, -1000);
		}
	}
	for (int i = 0; i < mine_max_num[1]; i++) {
		if (i < mine_num_now[1]) {
			exist3[i] = 1;
			mine3[i].SetTopLeft(0, 0);
		}
		else {
			exist3[i] = 0;
			mine3[i].SetTopLeft(-1000, -1000);
		}
	}
	for (int i = 0; i < mine_max_num[2]; i++) {
		if (i < mine_num_now[2]) {
			exist4[i] = 1;
			mine4[i].SetTopLeft(0, 0);
		}
		else {
			exist4[i] = 0;
			mine4[i].SetTopLeft(-1000, -1000);
		}
	}
	for (int i = 0; i < mine_max_num[3]; i++) {
		if (i < mine_num_now[3]) {
			exist5[i] = 1;
			mine5[i].SetTopLeft(0, 0);
		}
		else {
			exist5[i] = 0;
			mine5[i].SetTopLeft(-1000, -1000);
		}
	}
	for (int i = 0; i < mine_max_num[4]; i++) {
		if (i < mine_num_now[4]) {
			exist6[i] = 1;
			mine6[i].SetTopLeft(0, 0);
		}
		else {
			exist6[i] = 0;
			mine6[i].SetTopLeft(-1000, -1000);
		}
	}
	for (int i = 0; i < mine_max_num[5]; i++) {
		if (i < mine_num_now[5]) {
			exist7[i] = 1;
			mine7[i].SetTopLeft(0, 0);
		}
		else {
			exist7[i] = 0;
			mine7[i].SetTopLeft(-1000, -1000);
		}
	}
	for (int i = 0; i < mine_max_num[6]; i++) {
		if (i < mine_num_now[6]) {
			exist8[i] = 1;
			mine8[i].SetTopLeft(0, 0);
		}
		else {
			exist8[i] = 0;
			mine8[i].SetTopLeft(-1000, -1000);
		}
	}
	//爆炸桶
	for (int i = 0; i < mine_max_num[7]; i++) {
		if (i < mine_num_now[7]) {
			exist9[i] = 1;
			mine9[i].SetTopLeft(0, 0);
		}
		else {
			exist9[i] = 0;
			mine9[i].SetTopLeft(-1000, -1000);
		}
	}
	for (int i = 0; i < mine_max_num[8]; i++) {
		if (i < mine_num_now[8]) {
			exist10[i] = 1;
			mine10[i].SetTopLeft(0, 0);
		}
		else {
			exist10[i] = 0;
			mine10[i].SetTopLeft(-1000, -1000);
		}
	}
	for (int i = 0; i < mine_max_num[9]; i++) {
		if (i < mine_num_now[9]) {
			exist11[i] = 1;
			mine11[i].SetTopLeft(0, 0);
		}
		else {
			exist11[i] = 0;
			mine11[i].SetTopLeft(-1000, -1000);
		}
	}
	for (int i = 0; i < mine_max_num[10]; i++) {
		if (i < mine_num_now[10]) {
			exist12[i] = 1;
			mine12[i].SetTopLeft(0, 0);
		}
		else {
			exist12[i] = 0;
			mine12[i].SetTopLeft(-1000, -1000);
		}
	}
	for (int i = 0; i < mine_max_num[11]; i++) {
		if (i < mine_num_now[11]) {
			exist13[i] = 1;
			mine13[i].SetTopLeft(0, 0);
		}
		else {
			exist13[i] = 0;
			mine13[i].SetTopLeft(-1000, -1000);
		}
	}
	for (int i = 0; i < mine_max_num[12]; i++) {
		if (i < mine_num_now[12]) {
			exist14[i] = 1;
			mine14[i].SetTopLeft(0, 0);
		}
		else {
			exist14[i] = 0;
			mine14[i].SetTopLeft(-1000, -1000);
		}
	}
}

bool CGameStateRun::is_blew_up(int mine, int index) 
{
	for (int j = 0; j < mine_num_now[7]; j++) {
		switch (mine) {
		case 2:
			if (mine2[index].IsOverlap(mine2[index], explosion[j])) {
				exist2[index] = 0;
				mine2[index].SetTopLeft(-1000, -1000);
				return 1;
			}
			break;
		case 3:
			if (mine3[index].IsOverlap(mine3[index], explosion[j])) {
				exist3[index] = 0;
				mine3[index].SetTopLeft(-1000, -1000);
				return 1;
			}
			break;
		case 4:
			if (mine4[index].IsOverlap(mine4[index], explosion[j])) {
				exist4[index] = 0;
				mine4[index].SetTopLeft(-1000, -1000);
				return 1;
			}
			break;
		case 5:
			if (mine5[index].IsOverlap(mine5[index], explosion[j])) {
				exist5[index] = 0;
				mine5[index].SetTopLeft(-1000, -1000);
				return 1;
			}

			break;
		case 6:
			if (mine6[index].IsOverlap(mine6[index], explosion[j])) {
				exist6[index] = 0;
				mine6[index].SetTopLeft(-1000, -1000);
				return 1;
			}
			break;
		case 7:
			if (mine7[index].IsOverlap(mine7[index], explosion[j])) {
				exist7[index] = 0;
				mine7[index].SetTopLeft(-1000, -1000);
				return 1;
			}
			break;
		case 8:
			if (mine8[index].IsOverlap(mine8[index], explosion[j])) {
				exist8[index] = 0;
				mine8[index].SetTopLeft(-1000, -1000);
				return 1;
			}
			break;
		case 9:
			if (mine9[index].IsOverlap(mine9[index], explosion[j])) {
				return 1;
			}
			break;
		case 10:
			if (mine10[index].IsOverlap(mine10[index], explosion[j])) {
				exist10[index] = 0;
				mine10[index].SetTopLeft(-1000, -1000);
				return 1;
			}
			break;
		case 11:
			if (mine11[index].IsOverlap(mine11[index], explosion[j])) {
				exist11[index] = 0;
				mine11[index].SetTopLeft(-1000, -1000);
				return 1;
			}
			break;
		case 12:
			if (mine12[index].IsOverlap(mine12[index], explosion[j])) {
				exist12[index] = 0;
				mine12[index].SetTopLeft(-1000, -1000);
				return 1;
			}
			break;
		case 13:
			if (mine13[index].IsOverlap(mine13[index], explosion[j])) {
				exist13[index] = 0;
				mine13[index].SetTopLeft(-1000, -1000);
				return 1;
			}
			break;
		case 14:
			if (mine14[index].IsOverlap(mine14[index], explosion[j])) {
				exist14[index] = 0;
				mine14[index].SetTopLeft(-1000, -1000);
				return 1;
			}
			break;
		}
	}
	return 0;
}

void CGameStateRun::set_location_of_explosion(int index, int left, int top) 
{
	int move_x;
	int move_y;
	/*
	(40, 39, 91, 84)
	1.png
	(37, 36, 94, 87)
	2.png
	(34, 33, 97, 90)
	3.png
	(31, 21, 101, 93)
	4.png
	(27, 19, 104, 96)
	5.png
	(24, 17, 107, 98)
	6.png
	(21, 14, 111, 101)
	7.png
	(18, 11, 114, 104)
	8.png
	(16, 16, 117, 106)
	9.png
	(13, 13, 120, 109)
	10.png
	(35, 20, 78, 66)
	11.png
	(56, 18, 79, 39)
	12.png
	*/
	switch (explosion[index].GetFrameIndexOfBitmap()) {
	case 0:
		move_x = 80;
		move_y = 78;
		break;
	case 1:
		move_x = 74;
		move_y = 72;
		break;
	case 2:
		move_x = 68;
		move_y = 66;
		break;
	case 3:
		move_x = 62;
		move_y = 42;
		break;
	case 4:
		move_x = 54;
		move_y = 38;
		break;
	case 5:
		move_x = 48;
		move_y = 34;
		break;
	case 6:
		move_x = 42;
		move_y = 28;
		break;
	case 7:
		move_x = 36;
		move_y = 22;
		break;
	case 8:
		move_x = 32;
		move_y = 32;
		break;
	case 9:
		move_x = 26;
		move_y = 26;
		break;
	case 10:
		move_x = 70;
		move_y = 40;
		break;
	case 11:
		move_x = 112;
		move_y = 36;
		break;
	}
	//explosion[index].SetTopLeft(left + move_x, top + move_y);
	explosion[index].SetTopLeft(left + move_x + 32 - 130, top + move_y + 42 - 122);
}

void CGameStateRun::set_location_of_pig() 
{
	int velocity = 100;
	int interval = 20;
	int move_x = (int)(velocity * interval * 0.001);

	for (int i = 0; i < mine_num_now[4]; i++) {

		if (exist6[i] == 1 && !is_blew_up(6, i)) {
			int left = mine6[i].GetLeft();
			int top = mine6[i].GetTop();
			if (clock() - last_time_pig6[i] > interval) {

				if (mine6[i].GetFrameIndexOfBitmap() > 41) {
					mine6[i].SetTopLeft(left + move_x, top);
				}
				else {
					mine6[i].SetTopLeft(left - move_x, top);
				}

				last_time_pig6[i] = clock();
			}
		}
	}

	for (int i = 0; i < mine_num_now[8]; i++) {

		if (exist10[i] == 1 && !is_blew_up(10, i)) {
			int left = mine10[i].GetLeft();
			int top = mine10[i].GetTop();
			if (clock() - last_time_pig10[i] > interval) {

				if (mine10[i].GetFrameIndexOfBitmap() > 41) {
					mine10[i].SetTopLeft(left + move_x, top);
				}
				else {
					mine10[i].SetTopLeft(left - move_x, top);
				}

				last_time_pig10[i] = clock();
			}
		}

	}
}





void CGameStateRun::show_mine_2(int location[][2]) 
{
	for (int i = 0; i < mine_num_now[0]; i++) {
		if (exist2[i] == 1 && mine2[i].GetLeft() == 0 && mine2[i].GetTop() == 0) {
			mine2[i].SetTopLeft(location[i][0], location[i][1]);
		}
		if (exist2[i] == 1 && !is_blew_up(2, i)) {
			if (mine2[i].IsOverlap(hitbox, mine2[i])) {
				if (clawhead.GetFrameIndexOfBitmap() < 72)
				{
					clawhead.SetFrameIndexOfBitmap(clawhead.GetFrameIndexOfBitmap() + 72);
				}
				mine_caught.SetFrameIndexOfBitmap(2);
				exist2[i] = 0;
				mine2[i].SetTopLeft(-1000, -1000);
				hit = true;
				CAudio::Instance()->Play(6);

				money_gain = money_of_mine[0];
				weight = weight_of_mine[0];
			}
			mine2[i].ShowBitmap();
		}
	}
}

void CGameStateRun::show_mine_3(int location[][2])
{
	for (int i = 0; i < mine_num_now[1]; i++) {
		if (exist3[i] == 1 && mine3[i].GetLeft() == 0 && mine3[i].GetTop() == 0) {
			mine3[i].SetTopLeft(location[i][0], location[i][1]);
		}
		if (exist3[i] == 1 && !is_blew_up(3, i)) {
			if (mine3[i].IsOverlap(hitbox, mine3[i])) {
				if (clawhead.GetFrameIndexOfBitmap() < 72)
				{
					clawhead.SetFrameIndexOfBitmap(clawhead.GetFrameIndexOfBitmap() + 72);
				}
				mine_caught.SetFrameIndexOfBitmap(3);
				exist3[i] = 0;
				mine3[i].SetTopLeft(-1000, -1000);
				hit = true;
				CAudio::Instance()->Play(6);

				money_gain = money_of_mine[1];
				weight = weight_of_mine[1];
			}
			mine3[i].ShowBitmap();
		}
	}
}

void CGameStateRun::show_mine_4(int location[][2])
{
	for (int i = 0; i < mine_num_now[2]; i++) {
		if (exist4[i] == 1 && mine4[i].GetLeft() == 0 && mine4[i].GetTop() == 0) {
			mine4[i].SetTopLeft(location[i][0], location[i][1]);
		}
		if (exist4[i] == 1 && !is_blew_up(4, i)) {
			if (mine4[i].IsOverlap(hitbox, mine4[i])) {
				if (clawhead.GetFrameIndexOfBitmap() < 72)
				{
					clawhead.SetFrameIndexOfBitmap(clawhead.GetFrameIndexOfBitmap() + 72);
				}
				mine_caught.SetFrameIndexOfBitmap(4);
				exist4[i] = 0;
				mine4[i].SetTopLeft(-1000, -1000);
				hit = true;
				CAudio::Instance()->Play(5);

				money_gain = money_of_mine[2];
				weight = weight_of_mine[2];
			}
			mine4[i].ShowBitmap();
		}
	}
}

void CGameStateRun::show_mine_5(int location[][2])
{
	for (int i = 0; i < mine_num_now[3]; i++) {
		if (exist5[i] == 1 && mine5[i].GetLeft() == 0 && mine5[i].GetTop() == 0) {
			mine5[i].SetTopLeft(location[i][0], location[i][1]);
		}
		if (exist5[i] == 1 && !is_blew_up(5, i)) {
			if (mine5[i].IsOverlap(hitbox, mine5[i])) {
				if (clawhead.GetFrameIndexOfBitmap() < 72)
				{
					clawhead.SetFrameIndexOfBitmap(clawhead.GetFrameIndexOfBitmap() + 72);
				}
				mine_caught.SetFrameIndexOfBitmap(5);
				exist5[i] = 0;
				mine5[i].SetTopLeft(-1000, -1000);
				hit = true;
				CAudio::Instance()->Play(5);

				money_gain = money_of_mine[3];
				weight = weight_of_mine[3];
			}
			mine5[i].ShowBitmap();
		}
	}
}

void CGameStateRun::show_mine_6(int location[][2])
{
	for (int i = 0; i < mine_num_now[4]; i++) {
		if (exist6[i] == 1 && mine6[i].GetLeft() == 0 && mine6[i].GetTop() == 0) {
			mine6[i].SetTopLeft(location[i][0], location[i][1]);
			mine6[i].SetFrameIndexOfBitmap((int)rand() % 84);
		}
		if (exist6[i] == 1 && !is_blew_up(6, i)) {
			if (mine6[i].IsOverlap(hitbox, mine6[i])) {
				if (clawhead.GetFrameIndexOfBitmap() < 72)
				{
					clawhead.SetFrameIndexOfBitmap(clawhead.GetFrameIndexOfBitmap() + 72);
				}
				mine_caught.SetFrameIndexOfBitmap(6);
				exist6[i] = 0;
				mine6[i].SetTopLeft(-1000, -1000);
				hit = true;
				CAudio::Instance()->Play(7);

				money_gain = money_of_mine[4];
				weight = weight_of_mine[4];
			}
			mine6[i].ShowBitmap();
		}
	}
}

void CGameStateRun::show_mine_7(int location[][2])
{
	for (int i = 0; i < mine_num_now[5]; i++) {
		if (exist7[i] == 1 && mine7[i].GetLeft() == 0 && mine7[i].GetTop() == 0) {
			mine7[i].SetTopLeft(location[i][0], location[i][1]);
		}
		if (exist7[i] == 1 && !is_blew_up(7, i)) {
			if (mine7[i].IsOverlap(hitbox, mine7[i])) {
				if (clawhead.GetFrameIndexOfBitmap() < 72)
				{
					clawhead.SetFrameIndexOfBitmap(clawhead.GetFrameIndexOfBitmap() + 72);
				}
				mine_caught.SetFrameIndexOfBitmap(7);
				exist7[i] = 0;
				mine7[i].SetTopLeft(-1000, -1000);
				hit = true;
				CAudio::Instance()->Play(7);

				money_gain = money_of_mine[5];
				weight = weight_of_mine[5];
			}
			mine7[i].ShowBitmap();
		}
	}
}

void CGameStateRun::show_mine_8(int location[][2])
{
	for (int i = 0; i < mine_num_now[6]; i++) {
		if (exist8[i] == 1 && mine8[i].GetLeft() == 0 && mine8[i].GetTop() == 0) {
			mine8[i].SetTopLeft(location[i][0], location[i][1]);
		}
		if (exist8[i] == 1 && !is_blew_up(8, i)) {
			if (mine8[i].IsOverlap(hitbox, mine8[i])) {
				if (clawhead.GetFrameIndexOfBitmap() < 72)
				{
					clawhead.SetFrameIndexOfBitmap(clawhead.GetFrameIndexOfBitmap() + 72);
				}
				mine_caught.SetFrameIndexOfBitmap(8);
				exist8[i] = 0;
				mine8[i].SetTopLeft(-1000, -1000);
				hit = true;
				CAudio::Instance()->Play(7);

				money_gain = money_of_mine[6] + (money_of_mine[6] * item_4_effect * 2);
				weight = weight_of_mine[6];
			}
			mine8[i].ShowBitmap();
		}
	}
}

void CGameStateRun::show_mine_9(int location[][2])
{
	for (int i = 0; i < mine_num_now[7]; i++) {
		if (exist9[i] == 1 && mine9[i].GetLeft() == 0 && mine9[i].GetTop() == 0) {
			mine9[i].SetTopLeft(location[i][0], location[i][1]);
		}
		if (exist9[i] == 1 && !is_blew_up(9, i)) {
			if (mine9[i].IsOverlap(hitbox, mine9[i])) {
				if (clawhead.GetFrameIndexOfBitmap() < 72)
				{
					clawhead.SetFrameIndexOfBitmap(clawhead.GetFrameIndexOfBitmap() + 72);
				}
				mine_caught.SetFrameIndexOfBitmap(9);
				exist9[i] = 0;
				mine9[i].SetTopLeft(-1000, -1000);
				hit = true;

				//爆炸
				explosion[i].SetFrameIndexOfBitmap(0);

				CAudio::Instance()->Play(8);
				if (explosion[i].GetFrameIndexOfBitmap() == 0 && explosion[i].IsAnimation() == false) {
					explosion[i].ToggleAnimation();
				}

				money_gain = money_of_mine[7];
				weight = weight_of_mine[7];
			}
			mine9[i].ShowBitmap();
		}
		if (is_blew_up(9, i) && exist9[i] == 1) {
			exist9[i] = 0;
			mine9[i].SetTopLeft(-1000, -1000);

			//爆炸
			explosion[i].SetFrameIndexOfBitmap(0);
			CAudio::Instance()->Stop(8);
			CAudio::Instance()->Play(8);
			if (explosion[i].GetFrameIndexOfBitmap() == 0 && explosion[i].IsAnimation() == false) {
				explosion[i].ToggleAnimation();
			}
		}
		if (explosion[i].IsAnimation() && exist9[i] == 0) {
			explosion[i].ShowBitmap();
			set_location_of_explosion(i, location[i][0], location[i][1]);
		}
	}
}

void CGameStateRun::show_mine_10(int location[][2])
{
	for (int i = 0; i < mine_num_now[8]; i++) {
		if (exist10[i] == 1 && mine10[i].GetLeft() == 0 && mine10[i].GetTop() == 0) {
			mine10[i].SetTopLeft(location[i][0], location[i][1]);
			mine10[i].SetFrameIndexOfBitmap((int)rand() % 84);
		}
		if (exist10[i] == 1 && !is_blew_up(10, i)) {
			if (mine10[i].IsOverlap(hitbox, mine10[i])) {
				if (clawhead.GetFrameIndexOfBitmap() < 72)
				{
					clawhead.SetFrameIndexOfBitmap(clawhead.GetFrameIndexOfBitmap() + 72);
				}
				mine_caught.SetFrameIndexOfBitmap(10);
				exist10[i] = 0;
				mine10[i].SetTopLeft(-1000, -1000);
				hit = true;
				CAudio::Instance()->Play(5);

				money_gain = money_of_mine[8] + 300 * item_5_effect;
				weight = weight_of_mine[8];
			}
			mine10[i].ShowBitmap();
		}
	}
}

void CGameStateRun::show_mine_11(int location[][2])
{
	for (int i = 0; i < mine_num_now[9]; i++) {
		if (exist11[i] == 1 && mine11[i].GetLeft() == 0 && mine11[i].GetTop() == 0) {
			mine11[i].SetTopLeft(location[i][0], location[i][1]);
		}
		if (exist11[i] == 1 && !is_blew_up(11, i)) {
			if (mine11[i].IsOverlap(hitbox, mine11[i])) {
				if (clawhead.GetFrameIndexOfBitmap() < 72)
				{
					clawhead.SetFrameIndexOfBitmap(clawhead.GetFrameIndexOfBitmap() + 72);
				}
				mine_caught.SetFrameIndexOfBitmap(11);
				exist11[i] = 0;
				mine11[i].SetTopLeft(-1000, -1000);
				hit = true;
				CAudio::Instance()->Play(5);

				money_gain = money_of_mine[9] + 300 * item_5_effect;
				weight = weight_of_mine[9];
			}
			mine11[i].ShowBitmap();
		}
	}
}

void CGameStateRun::show_mine_12(int location[][2])
{
	for (int i = 0; i < mine_num_now[10]; i++) {
		if (exist12[i] == 1 && mine12[i].GetLeft() == 0 && mine12[i].GetTop() == 0) {
			mine12[i].SetTopLeft(location[i][0], location[i][1]);
		}
		if (exist12[i] == 1 && !is_blew_up(12, i)) {
			if (mine12[i].IsOverlap(hitbox, mine12[i])) {
				if (clawhead.GetFrameIndexOfBitmap() < 72)
				{
					clawhead.SetFrameIndexOfBitmap(clawhead.GetFrameIndexOfBitmap() + 72);
				}
				mine_caught.SetFrameIndexOfBitmap(12);
				exist12[i] = 0;
				mine12[i].SetTopLeft(-1000, -1000);
				hit = true;
				CAudio::Instance()->Play(6);

				money_gain = money_of_mine[10];
				weight = weight_of_mine[10];
			}
			mine12[i].ShowBitmap();
		}
	}
}

void CGameStateRun::show_mine_13(int location[][2])
{
	for (int i = 0; i < mine_num_now[11]; i++) {
		if (exist13[i] == 1 && mine13[i].GetLeft() == 0 && mine13[i].GetTop() == 0) {
			mine13[i].SetTopLeft(location[i][0], location[i][1]);
		}
		if (exist13[i] == 1 && !is_blew_up(13, i)) {
			if (mine13[i].IsOverlap(hitbox, mine13[i])) {
				if (clawhead.GetFrameIndexOfBitmap() < 72)
				{
					clawhead.SetFrameIndexOfBitmap(clawhead.GetFrameIndexOfBitmap() + 72);
				}
				mine_caught.SetFrameIndexOfBitmap(13);
				exist13[i] = 0;
				mine13[i].SetTopLeft(-1000, -1000);
				hit = true;
				CAudio::Instance()->Play(7);

				money_gain = money_of_mine[11] + (money_of_mine[11] * item_4_effect * 2);
				weight = weight_of_mine[11];
			}
			mine13[i].ShowBitmap();
		}
	}
}

void CGameStateRun::show_mine_14(int location[][2])
{
	for (int i = 0; i < mine_num_now[12]; i++) {
		if (exist14[i] == 1 && mine14[i].GetLeft() == 0 && mine14[i].GetTop() == 0) {
			mine14[i].SetTopLeft(location[i][0], location[i][1]);
		}
		if (exist14[i] == 1 && !is_blew_up(14, i)) {
			if (mine14[i].IsOverlap(hitbox, mine14[i])) {
				if (clawhead.GetFrameIndexOfBitmap() < 72)
				{
					clawhead.SetFrameIndexOfBitmap(clawhead.GetFrameIndexOfBitmap() + 72);
				}
				mine_caught.SetFrameIndexOfBitmap(14);
				exist14[i] = 0;
				mine14[i].SetTopLeft(-1000, -1000);
				hit = true;
				CAudio::Instance()->Play(7);

				money_gain = money_of_mine[12] + (money_of_mine[12] * item_4_effect * 2);
				weight = weight_of_mine[12];
			}
			mine14[i].ShowBitmap();
		}
	}
}


void CGameStateRun::set_last_time_audio() 
{
	if (sub_phase == 3 && owner_talk.IsAnimation()) 
	{
		if (clock() - last_time_audio_1 > 100) 
		{
			CAudio::Instance()->Play(10);
			last_time_audio_1 = clock();
		}
	}

	if (sub_phase == 2) 
	{
		if (clock() - last_time_audio_1 > 1000)
		{
			CAudio::Instance()->Play(9);
			last_time_audio_1 = clock();
			last_time_audio_2 = clock();
		}
		if (clock() - last_time_audio_2 > 250 && clock() - last_time_audio_1 < 300)
		{
			CAudio::Instance()->Play(9);
			last_time_audio_2 = clock();
		}
		
	}

}