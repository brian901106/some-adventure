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
	if (timer == 0 && money < goal_money)
	{
		gameover = true;
	}
	if (timer == 0 && money >= goal_money)
	{
		sub_phase = 3;
	}
	

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{

	
	/*Goal頁面*/
	goal.LoadBitmapByString({ "resources/goal_page/goal_bg/52.bmp","resources/goal_page/goal_bg/53.bmp","resources/goal_page/goal_bg/54.bmp","resources/goal_page/goal_bg/55.bmp","resources/goal_page/goal_bg/56.bmp","resources/goal_page/goal_bg/57.bmp","resources/goal_page/goal_bg/58.bmp","resources/goal_page/goal_bg/59.bmp","resources/goal_page/goal_bg/60.bmp","resources/goal_page/goal_bg/61.bmp","resources/goal_page/goal_bg/62.bmp","resources/goal_page/goal_bg/63.bmp","resources/goal_page/goal_bg/64.bmp","resources/goal_page/goal_bg/65.bmp","resources/goal_page/goal_bg/66.bmp","resources/goal_page/goal_bg/67.bmp","resources/goal_page/goal_bg/68.bmp","resources/goal_page/goal_bg/69.bmp","resources/goal_page/goal_bg/70.bmp","resources/goal_page/goal_bg/71.bmp","resources/goal_page/goal_bg/72.bmp","resources/goal_page/goal_bg/73.bmp","resources/goal_page/goal_bg/74.bmp","resources/goal_page/goal_bg/75.bmp","resources/goal_page/goal_bg/76.bmp","resources/goal_page/goal_bg/77.bmp","resources/goal_page/goal_bg/78.bmp","resources/goal_page/goal_bg/79.bmp","resources/goal_page/goal_bg/80.bmp","resources/goal_page/goal_bg/81.bmp","resources/goal_page/goal_bg/82.bmp","resources/goal_page/goal_bg/83.bmp","resources/goal_page/goal_bg/84.bmp","resources/goal_page/goal_bg/85.bmp","resources/goal_page/goal_bg/86.bmp","resources/goal_page/goal_bg/87.bmp","resources/goal_page/goal_bg/88.bmp","resources/goal_page/goal_bg/89.bmp","resources/goal_page/goal_bg/90.bmp","resources/goal_page/goal_bg/91.bmp","resources/goal_page/goal_bg/92.bmp","resources/goal_page/goal_bg/93.bmp" });
	goal.SetAnimation(50, true);
	goal.SetTopLeft(0, 0);
	//goal_audio.Load(0, "sound/goal.midi");
	//goal_audio.Play(0, false);

	/*第一關*/
	background.LoadBitmapByString({ "resources/stage/1_1.bmp", "resources/stage/2_1.bmp" });
	background.SetTopLeft(0, 0);

	miner.LoadBitmapByString({ "resources/miner/normal/1.bmp","resources/miner/normal/2.bmp","resources/miner/normal/3.bmp","resources/miner/normal/4.bmp","resources/miner/normal/5.bmp" }, RGB(0, 0, 0));
	miner.SetTopLeft(529, 33);
	miner.SetAnimation(200, true);
	miner_t.LoadBitmapByString({ "resources/miner/throw/31.bmp","resources/miner/throw/32.bmp","resources/miner/throw/33.bmp","resources/miner/throw/34.bmp","resources/miner/throw/35.bmp","resources/miner/throw/36.bmp","resources/miner/throw/37.bmp" }, RGB(0, 0, 0));
	miner_t.SetTopLeft(529, 23);
	miner_t.SetAnimation(20, true);
	miner_s.LoadBitmapByString({ "resources/miner/strength/1.bmp","resources/miner/strength/2.bmp","resources/miner/strength/3.bmp","resources/miner/strength/4.bmp","resources/miner/strength/5.bmp","resources/miner/strength/6.bmp","resources/miner/strength/7.bmp","resources/miner/strength/8.bmp","resources/miner/strength/9.bmp","resources/miner/strength/10.bmp","resources/miner/strength/11.bmp","resources/miner/strength/12.bmp","resources/miner/strength/13.bmp","resources/miner/strength/14.bmp","resources/miner/strength/15.bmp","resources/miner/strength/16.bmp" }, RGB(0, 0, 0));
	miner_s.SetTopLeft(529, 33);
	miner_s.SetAnimation(200, true);

	claw.LoadBitmapByString({ "resources/claw/0/rotate_new/4.bmp","resources/claw/0/rotate_new/5.bmp","resources/claw/0/rotate_new/6.bmp","resources/claw/0/rotate_new/7.bmp","resources/claw/0/rotate_new/8.bmp","resources/claw/0/rotate_new/9.bmp","resources/claw/0/rotate_new/10.bmp","resources/claw/0/rotate_new/11.bmp","resources/claw/0/rotate_new/12.bmp","resources/claw/0/rotate_new/13.bmp","resources/claw/0/rotate_new/14.bmp","resources/claw/0/rotate_new/15.bmp","resources/claw/0/rotate_new/16.bmp","resources/claw/0/rotate_new/17.bmp","resources/claw/0/rotate_new/18.bmp","resources/claw/0/rotate_new/19.bmp","resources/claw/0/rotate_new/20.bmp","resources/claw/0/rotate_new/21.bmp","resources/claw/0/rotate_new/22.bmp","resources/claw/0/rotate_new/23.bmp","resources/claw/0/rotate_new/24.bmp","resources/claw/0/rotate_new/25.bmp","resources/claw/0/rotate_new/26.bmp","resources/claw/0/rotate_new/27.bmp","resources/claw/0/rotate_new/28.bmp","resources/claw/0/rotate_new/29.bmp","resources/claw/0/rotate_new/30.bmp","resources/claw/0/rotate_new/31.bmp","resources/claw/0/rotate_new/32.bmp","resources/claw/0/rotate_new/33.bmp","resources/claw/0/rotate_new/34.bmp","resources/claw/0/rotate_new/35.bmp","resources/claw/0/rotate_new/36.bmp","resources/claw/0/rotate_new/37.bmp","resources/claw/0/rotate_new/38.bmp","resources/claw/0/rotate_new/39.bmp","resources/claw/0/rotate_new/40.bmp","resources/claw/0/rotate_new/41.bmp","resources/claw/0/rotate_new/42.bmp","resources/claw/0/rotate_new/43.bmp","resources/claw/0/rotate_new/44.bmp","resources/claw/0/rotate_new/45.bmp","resources/claw/0/rotate_new/46.bmp","resources/claw/0/rotate_new/47.bmp","resources/claw/0/rotate_new/48.bmp","resources/claw/0/rotate_new/49.bmp","resources/claw/0/rotate_new/50.bmp","resources/claw/0/rotate_new/51.bmp","resources/claw/0/rotate_new/52.bmp","resources/claw/0/rotate_new/53.bmp","resources/claw/0/rotate_new/54.bmp","resources/claw/0/rotate_new/55.bmp","resources/claw/0/rotate_new/56.bmp","resources/claw/0/rotate_new/57.bmp","resources/claw/0/rotate_new/58.bmp","resources/claw/0/rotate_new/59.bmp","resources/claw/0/rotate_new/60.bmp","resources/claw/0/rotate_new/61.bmp","resources/claw/0/rotate_new/62.bmp","resources/claw/0/rotate_new/63.bmp","resources/claw/0/rotate_new/64.bmp","resources/claw/0/rotate_new/65.bmp","resources/claw/0/rotate_new/66.bmp","resources/claw/0/rotate_new/67.bmp","resources/claw/0/rotate_new/68.bmp","resources/claw/0/rotate_new/69.bmp","resources/claw/0/rotate_new/70.bmp","resources/claw/0/rotate_new/71.bmp","resources/claw/0/rotate_new/72.bmp","resources/claw/0/rotate_new/73.bmp","resources/claw/0/rotate_new/74.bmp","resources/claw/0/rotate_new/75.bmp" }, RGB(0, 0, 0));
	claw.SetTopLeft(507, 90);
	claw.SetAnimation(70, false);

	clawhead.LoadBitmapByString({ "resources/claw/0/rotate_new/4.bmp","resources/claw/0/rotate_new/5.bmp","resources/claw/0/rotate_new/6.bmp","resources/claw/0/rotate_new/7.bmp","resources/claw/0/rotate_new/8.bmp","resources/claw/0/rotate_new/9.bmp","resources/claw/0/rotate_new/10.bmp","resources/claw/0/rotate_new/11.bmp","resources/claw/0/rotate_new/12.bmp","resources/claw/0/rotate_new/13.bmp","resources/claw/0/rotate_new/14.bmp","resources/claw/0/rotate_new/15.bmp","resources/claw/0/rotate_new/16.bmp","resources/claw/0/rotate_new/17.bmp","resources/claw/0/rotate_new/18.bmp","resources/claw/0/rotate_new/19.bmp","resources/claw/0/rotate_new/20.bmp","resources/claw/0/rotate_new/21.bmp","resources/claw/0/rotate_new/22.bmp","resources/claw/0/rotate_new/23.bmp","resources/claw/0/rotate_new/24.bmp","resources/claw/0/rotate_new/25.bmp","resources/claw/0/rotate_new/26.bmp","resources/claw/0/rotate_new/27.bmp","resources/claw/0/rotate_new/28.bmp","resources/claw/0/rotate_new/29.bmp","resources/claw/0/rotate_new/30.bmp","resources/claw/0/rotate_new/31.bmp","resources/claw/0/rotate_new/32.bmp","resources/claw/0/rotate_new/33.bmp","resources/claw/0/rotate_new/34.bmp","resources/claw/0/rotate_new/35.bmp","resources/claw/0/rotate_new/36.bmp","resources/claw/0/rotate_new/37.bmp","resources/claw/0/rotate_new/38.bmp","resources/claw/0/rotate_new/39.bmp","resources/claw/0/rotate_new/40.bmp","resources/claw/0/rotate_new/41.bmp","resources/claw/0/rotate_new/42.bmp","resources/claw/0/rotate_new/43.bmp","resources/claw/0/rotate_new/44.bmp","resources/claw/0/rotate_new/45.bmp","resources/claw/0/rotate_new/46.bmp","resources/claw/0/rotate_new/47.bmp","resources/claw/0/rotate_new/48.bmp","resources/claw/0/rotate_new/49.bmp","resources/claw/0/rotate_new/50.bmp","resources/claw/0/rotate_new/51.bmp","resources/claw/0/rotate_new/52.bmp","resources/claw/0/rotate_new/53.bmp","resources/claw/0/rotate_new/54.bmp","resources/claw/0/rotate_new/55.bmp","resources/claw/0/rotate_new/56.bmp","resources/claw/0/rotate_new/57.bmp","resources/claw/0/rotate_new/58.bmp","resources/claw/0/rotate_new/59.bmp","resources/claw/0/rotate_new/60.bmp","resources/claw/0/rotate_new/61.bmp","resources/claw/0/rotate_new/62.bmp","resources/claw/0/rotate_new/63.bmp","resources/claw/0/rotate_new/64.bmp","resources/claw/0/rotate_new/65.bmp","resources/claw/0/rotate_new/66.bmp","resources/claw/0/rotate_new/67.bmp","resources/claw/0/rotate_new/68.bmp","resources/claw/0/rotate_new/69.bmp","resources/claw/0/rotate_new/70.bmp","resources/claw/0/rotate_new/71.bmp","resources/claw/0/rotate_new/72.bmp","resources/claw/0/rotate_new/73.bmp","resources/claw/0/rotate_new/74.bmp","resources/claw/0/rotate_new/75.bmp" }, RGB(0, 0, 0));
	clawhead.SetTopLeft(507, 90);

	load_mines();

	hitbox.LoadBitmapByString({ "resources/claw/hitbox.bmp" }, RGB(0, 0, 0));
	hitbox.SetTopLeft(538, 90);

	bomb.LoadBitmapByString({ "resources/claw/bomb.bmp" }, RGB(0, 0, 0));
	bomb.SetTopLeft(507, 90);

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
			miner.ToggleAnimation();
			key_down_index = claw.GetFrameIndexOfBitmap();
			clawhead.SetFrameIndexOfBitmap(key_down_index);
			claw_is_ready = false;
		}
	}
	if (nChar == VK_UP) {
		action_state = 2;
		bomb_is_throw = true;
	}
	if (nChar == VK_RIGHT) {
		sub_phase = 3;
	}
	if (nChar == VK_LEFT) {
		money = money + 100;
		timer = timer - 8;
	}
	if (nChar == VK_SPACE) {

	}
}


void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if (exit.GetFrameIndexOfBitmap() == 1 && sub_phase == 2 ) {
		gameover = true;
	}
	if (next_level_button.GetFrameIndexOfBitmap() == 1 && sub_phase == 3) {
		next_level_button_clicked = true;
	}

	//按下play again
	if (playagain_button.GetFrameIndexOfBitmap() == 1) {
		return_game = true;
	}

	/*確認滑鼠位置與商店裡面1~5座標是否相同，相同的話跳到show_items()*/
	if (sub_phase == 3) {
		if (point.x >= item_1.GetLeft() &&
			point.x <= item_1.GetLeft() + item_1.GetWidth() &&
			point.y >= item_1.GetTop() &&
			point.y <= item_1.GetTop() + item_1.GetHeight())
		{
			item_is_bought_1 = true;
		}
		if (point.x >= item_2.GetLeft() &&
			point.x <= item_2.GetLeft() + item_2.GetWidth() &&
			point.y >= item_2.GetTop() &&
			point.y <= item_2.GetTop() + item_2.GetHeight())
		{
			item_is_bought_2 = true;
		}
		if (point.x >= item_3.GetLeft() &&
			point.x <= item_3.GetLeft() + item_3.GetWidth() &&
			point.y >= item_3.GetTop() &&
			point.y <= item_3.GetTop() + item_3.GetHeight())
		{
			item_is_bought_3 = true;
		}
		if (point.x >= item_4.GetLeft() &&
			point.x <= item_4.GetLeft() + item_4.GetWidth() &&
			point.y >= item_4.GetTop() &&
			point.y <= item_4.GetTop() + item_4.GetHeight())
		{
			item_is_bought_4 = true;
		}
		if (point.x >= item_5.GetLeft() &&
			point.x <= item_5.GetLeft() + item_5.GetWidth() &&
			point.y >= item_5.GetTop() &&
			point.y <= item_5.GetTop() + item_5.GetHeight())
		{
			item_is_bought_5 = true;
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
	if ((clock() % 1000) > 700 && timer <= 10 && timer > 0) {
		timer_bling.ShowBitmap();
	}

	if (sub_phase == 2){
		show_text_by_phase();
		if (claw_is_ready == false) {
			clawhead.ShowBitmap();
			hitbox.ShowBitmap();
			shoot_claw_by_angle();
		}
		if (hit == true) {
			pull_claw();
		}
		if (bomb_is_throw == true) {
			bomb.ShowBitmap();
			throw_bomb();
		}
	}

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
			goal.ToggleAnimation();
			fade_rate = 1;
		}
	}
	if (sub_phase == 2) 
	{
		goal.UnshowBitmap();
		background.ShowBitmap();
		exit.ShowBitmap();
		show_mines();
		if (claw_is_ready == true)
		{
			claw.ShowBitmap();
		}

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
		
	}
	if (sub_phase == 3)
	{
		if (success.GetFrameIndexOfBitmap() == 0 && success.IsAnimation() == false)
		{
			success.ToggleAnimation();
			/*初始化物品是否有被點擊*/
			item_is_bought_1 = false;
			item_is_bought_2 = false;
			item_is_bought_3 = false;
			item_is_bought_4 = false;
			item_is_bought_5 = false;
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
			set_stock();
			show_items();
		}
		/*老闆開心*/
		if (next_level_button_clicked == true && (item_is_bought_1 == true || item_is_bought_2 == true || item_is_bought_3 == true || item_is_bought_4 == true || item_is_bought_5 == true))
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

void CGameStateRun::shoot_claw_by_angle()
{
	int angles[72] = { 70, 70, 69, 68, 66, 64, 62, 59, 55, 51, 47, 42, 37, 32, 27, 21, 15, 9, 3, -2, -8, -15, -20, -26, -32, -37, -42, -46, -50, -54, -57, -60, -63, -65, -67, -68, -68, -68, -68, -67, -66, -65, -63, -60, -57, -53, -50, -45, -40, -35, -29, -24, -18, -12, -6, 0, 5, 11, 17, 23, 29, 34, 39, 44, 49, 53, 57, 60, 63, 65, 67, 69};

	if (!hit) {
		if (clock() - last_time_claw >= 1 && claw_length < 90)
		{
			claw_x = claw_x + (int)(sin(angles[key_down_index] * rad) * 8);
			claw_y = claw_y + (int)(cos(angles[key_down_index] * rad) * 8);
			clawhead.SetTopLeft(claw_x, claw_y);
			hitbox.SetTopLeft(claw_x + 43 - 21 + (int)(11 * (sin(angles[key_down_index] * rad))), claw_y + 5 + (int)(11 * (cos(angles[key_down_index] * rad))));

			claw_xway[claw_length] = claw_x;
			claw_yway[claw_length] = claw_y;

			claw_length = claw_length + 1;
			last_time_claw = clock();
		}
		else if(claw_length == 90){
			reset_claw();
		}
	}
}

void CGameStateRun::pull_claw()
{
	int angles[72] = { 70, 70, 69, 68, 66, 64, 62, 59, 55, 51, 47, 42, 37, 32, 27, 21, 15, 9, 3, -2, -8, -15, -20, -26, -32, -37, -42, -46, -50, -54, -57, -60, -63, -65, -67, -68, -68, -68, -68, -67, -66, -65, -63, -60, -57, -53, -50, -45, -40, -35, -29, -24, -18, -12, -6, 0, 5, 11, 17, 23, 29, 34, 39, 44, 49, 53, 57, 60, 63, 65, 67, 69 };

	if (clock() - last_time_claw >= (1*weight) && claw_length > 0 )
	{
		claw_length = claw_length - 1;
		clawhead.SetTopLeft(claw_xway[claw_length], claw_yway[claw_length]);
		last_time_claw = clock();
	}
	else if (claw_length == 0){
		reset_claw();
	}
}

void CGameStateRun::reset_claw() 
{
	claw_length = 0;
	claw_x = 507;
	claw_y = 90;
	clawhead.SetTopLeft(claw_x, claw_y);
	hitbox.SetTopLeft(claw_x, claw_y);
	claw_is_ready = true;
	hit = false;
}

void CGameStateRun::throw_bomb() 
{
	int angles[72] = { 70, 70, 69, 68, 66, 64, 62, 59, 55, 51, 47, 42, 37, 32, 27, 21, 15, 9, 3, -2, -8, -15, -20, -26, -32, -37, -42, -46, -50, -54, -57, -60, -63, -65, -67, -68, -68, -68, -68, -67, -66, -65, -63, -60, -57, -53, -50, -45, -40, -35, -29, -24, -18, -12, -6, 0, 5, 11, 17, 23, 29, 34, 39, 44, 49, 53, 57, 60, 63, 65, 67, 69 };

	if (hit && bomb_is_throw) {
		if (clock() - last_time_bomb >= 1)
		{
			bomb_x = bomb_x + (int)(sin(angles[key_down_index] * rad) * 8);
			bomb_y = bomb_y + (int)(cos(angles[key_down_index] * rad) * 8);
			bomb.SetTopLeft(bomb_x, bomb_y);

			last_time_bomb = clock();
		}
	}
}


void CGameStateRun::set_stock()
{
	int stock_sheet[10][5] = {  {1,1,1,0,0},
								{0,0,0,0,1},
								{1,1,1,1,1},
								{1,1,1,1,1},
								{1,1,1,1,1},
								{1,1,1,1,1}};

	for (int item_num = 0; item_num < 5; item_num++) {
		item_in_stock_in_level[item_num] = stock_sheet[phase-1][item_num];
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

	fail.ShowBitmap();

	if (fail.GetFrameIndexOfBitmap() == 0 && fail.IsAnimation() == false) {
		fail.ToggleAnimation();
	}

	
	
	if (fail.IsAnimation() == false && fail.GetFrameIndexOfBitmap() != 0) {
		exit_background.ShowBitmap();
		playagain_button.ShowBitmap();

		CDC *pDC = CDDraw::GetBackCDC();
		CTextDraw::ChangeFontLog(pDC, 25, "calibri", RGB(0, 0, 0), 45000);
		CTextDraw::Print(pDC, 180, 673, "play again");
		CDDraw::ReleaseBackCDC();

		if (return_game == true) 
		{
			reset_mines();
			reset_claw();
			GotoGameState(GAME_STATE_INIT);
			fail.SetFrameIndexOfBitmap(0);
			goal.SetFrameIndexOfBitmap(0);
			money = 0;
			sub_phase = 1;
			timer = 61;
			phase = 1;
			goal_money = 650;
			return_game = false;
		}

	}
}
void CGameStateRun::goto_next_stage()
{
	timer = 61;
	fade_rate = 1;
	goal.SetFrameIndexOfBitmap(0);
	success.SetFrameIndexOfBitmap(0);
	sub_phase = 1;
	phase = phase + 1;
	background.SetFrameIndexOfBitmap(phase-1);
	owner_buy.SetFrameIndexOfBitmap(0);
	owner_angry.SetFrameIndexOfBitmap(0);
	next_level_button_clicked = false;
	set_goal_money();

	claw_length = 0;
	claw_x = 507;
	claw_y = 90;
	clawhead.SetTopLeft(claw_x, claw_y);
	hitbox.SetTopLeft(claw_x, claw_y);
	claw_is_ready = true;

	reset_mines();

}

void CGameStateRun::reset_mines()
{
	for (int i = 0; i < mine_max_num[0]; i++) {
		if (exist2[i] == 0)
			exist2[i] = 1;
	}
	for (int i = 0; i < mine_max_num[1]; i++) {
		if (exist3[i] == 0)
			exist3[i] = 1;
	}
	for (int i = 0; i < mine_max_num[2]; i++) {
		if (exist4[i] == 0)
			exist4[i] = 1;
	}
	for (int i = 0; i < mine_max_num[3]; i++) {
		if (exist5[i] == 0)
			exist5[i] = 1;
	}
	for (int i = 0; i < mine_max_num[4]; i++) {
		if (exist6[i] == 0)
			exist6[i] = 1;
	}
	for (int i = 0; i < mine_max_num[5]; i++) {
		if (exist7[i] == 0)
			exist7[i] = 1;
	}
	for (int i = 0; i < mine_max_num[6]; i++) {
		if (exist8[i] == 0)
			exist8[i] = 1;
	}
	for (int i = 0; i < mine_max_num[7]; i++) {
		if (exist9[i] == 0)
			exist9[i] = 1;
	}
	for (int i = 0; i < mine_max_num[8]; i++) {
		if (exist10[i] == 0)
			exist10[i] = 1;
	}
	for (int i = 0; i < mine_max_num[9]; i++) {
		if (exist11[i] == 0)
			exist11[i] = 1;
	}
	for (int i = 0; i < mine_max_num[10]; i++) {
		if (exist12[i] == 0)
			exist12[i] = 1;
	}
	for (int i = 0; i < mine_max_num[11]; i++) {
		if (exist13[i] == 0)
			exist13[i] = 1;
	}
	for (int i = 0; i < mine_max_num[12]; i++) {
		if (exist14[i] == 0)
			exist14[i] = 1;
	}
	for (int i = 0; i < mine_max_num[0]; i++) {
		mine2[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[1]; i++) {
		mine3[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[2]; i++) {
		mine4[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[3]; i++) {
		mine5[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[4]; i++) {
		mine6[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[5]; i++) {
		mine7[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[6]; i++) {
		mine8[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[7]; i++) {
		mine9[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[8]; i++) {
		mine10[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[9]; i++) {
		mine11[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[10]; i++) {
		mine12[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[11]; i++) {
		mine13[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[12]; i++) {
		mine14[i].SetTopLeft(0, 0);
	}
}

void CGameStateRun::show_text_by_phase() {
	
	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 25, "新細明體", RGB(255, 102, 0), 15000);
	
	if (sub_phase == 2 && timer > 0) {
		
		CTextDraw::Print(pDC, 1033, 10, std::to_string(timer));

		
		if (clock() - last_time >= 1000)
		{	
	
			timer -= 1;
			last_time = clock();
		}
	}

	CTextDraw::Print(pDC, 1033, 58, std::to_string(phase));

	CTextDraw::ChangeFontLog(pDC, 25, "新細明體", RGB(0, 0, 0), 15000);
	CTextDraw::Print(pDC, 140, 12, std::to_string(money));
	CTextDraw::ChangeFontLog(pDC, 25, "新細明體", RGB(0, 153, 0), 15000);
	CTextDraw::Print(pDC, 140, 10, std::to_string(money));

	CTextDraw::ChangeFontLog(pDC, 25, "新細明體", RGB(0, 0, 0), 15000);
	CTextDraw::Print(pDC, 138, 62, std::to_string(goal_money));
	CTextDraw::ChangeFontLog(pDC, 25, "新細明體", RGB(255, 153, 0), 15000);
	CTextDraw::Print(pDC, 138, 60, std::to_string(goal_money));
	
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


void CGameStateRun::load_mines()
{
	for (int i = 0; i < mine_max_num[0]; i++) {
		mine2[i].LoadBitmapByString({ "resources/mines/2.bmp" }, RGB(0, 0, 0));
		mine2[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[1]; i++) {
		mine3[i].LoadBitmapByString({ "resources/mines/3.bmp" }, RGB(0, 0, 0));
		mine3[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[2]; i++) {
		mine4[i].LoadBitmapByString({ "resources/mines/4.bmp" }, RGB(0, 0, 0));
		mine4[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[3]; i++) {
		mine5[i].LoadBitmapByString({ "resources/mines/5.bmp" }, RGB(0, 0, 0));
		mine5[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[4]; i++) {
		mine6[i].LoadBitmapByString({ "resources/mines/6/1.bmp" }, RGB(0, 0, 0));
		mine6[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[5]; i++) {
		mine7[i].LoadBitmapByString({ "resources/mines/7.bmp" }, RGB(0, 0, 0));
		mine7[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[6]; i++) {
		mine8[i].LoadBitmapByString({ "resources/mines/8.bmp" }, RGB(0, 0, 0));
		mine8[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[7]; i++) {
		mine9[i].LoadBitmapByString({ "resources/mines/9.bmp" }, RGB(0, 0, 0));
		mine9[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[8]; i++) {
		mine10[i].LoadBitmapByString({ "resources/mines/10/1.bmp" }, RGB(0, 0, 0));
		mine10[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[9]; i++) {
		mine11[i].LoadBitmapByString({ "resources/mines/11.bmp" }, RGB(0, 0, 0));
		mine11[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[10]; i++) {
		mine12[i].LoadBitmapByString({ "resources/mines/12.bmp" }, RGB(0, 0, 0));
		mine12[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[11]; i++) {
		mine13[i].LoadBitmapByString({ "resources/mines/13.bmp" }, RGB(0, 0, 0));
		mine13[i].SetTopLeft(0, 0);
	}
	for (int i = 0; i < mine_max_num[12]; i++) {
		mine14[i].LoadBitmapByString({ "resources/mines/14.bmp" }, RGB(0, 0, 0));
		mine14[i].SetTopLeft(0, 0);
	}

};

void CGameStateRun::show_mines()
{
	if (phase == 1) {

		for (int i = 0; i < mine_num_L1_1[0]; i++) {
			if (mine2[i].GetLeft() == 0 && mine2[i].GetTop() == 0) {
				mine2[i].SetTopLeft(location2[i][0], location2[i][1]);
			}
			if (exist2[i] == 1) {
				if (mine2[i].IsOverlap(hitbox, mine2[i])) {
					exist2[i] = 0;
					mine2[i].SetTopLeft(-100, -100);
					hit = true;


					money = money + 50;
					weight = weight_of_mine[0];
				}
				mine2[i].ShowBitmap();
			}
		}

		for (int i = 0; i < mine_num_L1_1[1]; i++) {
			if (mine3[i].GetLeft() == 0 && mine3[i].GetTop() == 0) {
				mine3[i].SetTopLeft(location3[i][0], location3[i][1]);
			}
			if (exist3[i] == 1) {
				if (mine3[i].IsOverlap(hitbox, mine3[i])) {
					exist3[i] = 0;
					mine3[i].SetTopLeft(-100, -100);
					hit = true;


					money = money + 150;
					weight = weight_of_mine[1];
				}
				mine3[i].ShowBitmap();
			}
		}

		for (int i = 0; i < mine_num_L1_1[3]; i++) {
			if (mine5[i].GetLeft() == 0 && mine5[i].GetTop() == 0) {
				mine5[i].SetTopLeft(location5[i][0], location5[i][1]);
			}
			if (exist5[i] == 1) {
				if (mine5[i].IsOverlap(hitbox, mine5[i])) {
					exist5[i] = 0;
					mine5[i].SetTopLeft(-100, -100);
					hit = true;


					money = money + 500;
					weight = weight_of_mine[3];
				}
				mine5[i].ShowBitmap();
			}
		}

		for (int i = 0; i < mine_num_L1_1[6]; i++) {
			if (mine8[i].GetLeft() == 0 && mine8[i].GetTop() == 0) {
				mine8[i].SetTopLeft(location8[i][0], location8[i][1]);
			}
			if (exist8[i] == 1) {
				if (mine8[i].IsOverlap(hitbox, mine8[i])) {
					exist8[i] = 0;
					mine8[i].SetTopLeft(-100, -100);
					hit = true;


					money = money + 20;
					weight = weight_of_mine[6];
				}
				mine8[i].ShowBitmap();
			}
		}

		for (int i = 0; i < mine_num_L1_1[10]; i++) {
			if (mine12[i].GetLeft() == 0 && mine12[i].GetTop() == 0) {
				mine12[i].SetTopLeft(location12[i][0], location12[i][1]);
			}
			if (exist12[i] == 1) {
				if (mine12[i].IsOverlap(hitbox, mine12[i])) {
					exist12[i] = 0;
					mine12[i].SetTopLeft(-100, -100);
					hit = true;


					money = money + 99;
					weight = weight_of_mine[10];
				}
				mine12[i].ShowBitmap();
			}
		}

		for (int i = 0; i < mine_num_L1_1[12]; i++) {
			if (mine14[i].GetLeft() == 0 && mine14[i].GetTop() == 0) {
				mine14[i].SetTopLeft(location14[i][0], location14[i][1]);
			}
			if (exist14[i] == 1) {
				if (mine14[i].IsOverlap(hitbox, mine14[i])) {
					exist14[i] = 0;
					mine14[i].SetTopLeft(-100, -100);
					hit = true;


					money = money + 10;
					weight = weight_of_mine[12];
				}
				mine14[i].ShowBitmap();
			}
		}
	}

}