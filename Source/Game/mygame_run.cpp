#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

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
	set_goal_money();
	if (goal.IsAnimationDone() && sub_phase == 1)
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

	

	goal.LoadBitmapByString({ "resources/goal_page/600/15.bmp","resources/goal_page/600/16.bmp","resources/goal_page/600/17.bmp","resources/goal_page/600/18.bmp","resources/goal_page/600/19.bmp","resources/goal_page/600/20.bmp","resources/goal_page/600/21.bmp","resources/goal_page/600/22.bmp","resources/goal_page/600/23.bmp","resources/goal_page/600/24.bmp","resources/goal_page/600/25.bmp","resources/goal_page/600/26.bmp","resources/goal_page/600/27.bmp","resources/goal_page/600/28.bmp","resources/goal_page/600/29.bmp","resources/goal_page/600/30.bmp","resources/goal_page/600/31.bmp","resources/goal_page/600/32.bmp","resources/goal_page/600/33.bmp","resources/goal_page/600/34.bmp","resources/goal_page/600/35.bmp","resources/goal_page/600/36.bmp","resources/goal_page/600/37.bmp","resources/goal_page/600/38.bmp","resources/goal_page/600/39.bmp","resources/goal_page/600/40.bmp","resources/goal_page/600/41.bmp","resources/goal_page/600/42.bmp","resources/goal_page/600/43.bmp","resources/goal_page/600/44.bmp","resources/goal_page/600/45.bmp","resources/goal_page/600/46.bmp","resources/goal_page/600/47.bmp","resources/goal_page/600/48.bmp","resources/goal_page/600/49.bmp","resources/goal_page/600/50.bmp","resources/goal_page/600/51.bmp" });
	goal.SetAnimation(50, true);
	goal.SetTopLeft(0, 0);
	//goal_audio.Load(0, "sound/goal.midi");
	//goal_audio.Play(0, false);
	background.LoadBitmapByString({ "resources/stage/1_1.bmp" });
	background.SetTopLeft(0, 0);

	miner.LoadBitmapByString({ "resources/miner/normal/1.bmp","resources/miner/normal/2.bmp","resources/miner/normal/3.bmp","resources/miner/normal/4.bmp","resources/miner/normal/5.bmp" }, RGB(0, 0, 0));
	miner.SetTopLeft(529, 33);
	miner.SetAnimation(200, true);
	miner_t.LoadBitmapByString({ "resources/miner/throw/1.bmp","resources/miner/throw/2.bmp","resources/miner/throw/3.bmp","resources/miner/throw/4.bmp","resources/miner/throw/5.bmp","resources/miner/throw/6.bmp","resources/miner/throw/7.bmp","resources/miner/throw/8.bmp","resources/miner/throw/9.bmp","resources/miner/throw/10.bmp","resources/miner/throw/11.bmp","resources/miner/throw/12.bmp","resources/miner/throw/13.bmp","resources/miner/throw/14.bmp","resources/miner/throw/15.bmp","resources/miner/throw/16.bmp","resources/miner/throw/17.bmp","resources/miner/throw/18.bmp","resources/miner/throw/19.bmp","resources/miner/throw/20.bmp","resources/miner/throw/21.bmp","resources/miner/throw/22.bmp","resources/miner/throw/23.bmp","resources/miner/throw/24.bmp","resources/miner/throw/25.bmp","resources/miner/throw/26.bmp","resources/miner/throw/27.bmp","resources/miner/throw/28.bmp","resources/miner/throw/29.bmp","resources/miner/throw/30.bmp","resources/miner/throw/31.bmp","resources/miner/throw/32.bmp","resources/miner/throw/33.bmp","resources/miner/throw/34.bmp","resources/miner/throw/35.bmp","resources/miner/throw/36.bmp","resources/miner/throw/37.bmp" }, RGB(0, 0, 0));
	miner_t.SetTopLeft(529, 23);
	miner_t.SetAnimation(20, true);
	miner_s.LoadBitmapByString({ "resources/miner/strength/1.bmp","resources/miner/strength/2.bmp","resources/miner/strength/3.bmp","resources/miner/strength/4.bmp","resources/miner/strength/5.bmp","resources/miner/strength/6.bmp","resources/miner/strength/7.bmp","resources/miner/strength/8.bmp","resources/miner/strength/9.bmp","resources/miner/strength/10.bmp","resources/miner/strength/11.bmp","resources/miner/strength/12.bmp","resources/miner/strength/13.bmp","resources/miner/strength/14.bmp","resources/miner/strength/15.bmp","resources/miner/strength/16.bmp" }, RGB(0, 0, 0));
	miner_s.SetTopLeft(529, 33);
	miner_s.SetAnimation(200, true);

	claw.LoadBitmapByString({ "resources/claw/0/rotate/1.bmp","resources/claw/0/rotate/2.bmp","resources/claw/0/rotate/3.bmp","resources/claw/0/rotate/4.bmp","resources/claw/0/rotate/5.bmp","resources/claw/0/rotate/6.bmp","resources/claw/0/rotate/7.bmp","resources/claw/0/rotate/8.bmp","resources/claw/0/rotate/9.bmp","resources/claw/0/rotate/10.bmp","resources/claw/0/rotate/11.bmp","resources/claw/0/rotate/12.bmp","resources/claw/0/rotate/13.bmp","resources/claw/0/rotate/14.bmp","resources/claw/0/rotate/15.bmp","resources/claw/0/rotate/16.bmp","resources/claw/0/rotate/17.bmp","resources/claw/0/rotate/18.bmp","resources/claw/0/rotate/19.bmp","resources/claw/0/rotate/20.bmp","resources/claw/0/rotate/21.bmp","resources/claw/0/rotate/22.bmp","resources/claw/0/rotate/23.bmp","resources/claw/0/rotate/24.bmp","resources/claw/0/rotate/25.bmp","resources/claw/0/rotate/26.bmp","resources/claw/0/rotate/27.bmp","resources/claw/0/rotate/28.bmp","resources/claw/0/rotate/29.bmp","resources/claw/0/rotate/30.bmp","resources/claw/0/rotate/31.bmp","resources/claw/0/rotate/32.bmp","resources/claw/0/rotate/33.bmp","resources/claw/0/rotate/34.bmp","resources/claw/0/rotate/35.bmp","resources/claw/0/rotate/36.bmp","resources/claw/0/rotate/37.bmp","resources/claw/0/rotate/38.bmp","resources/claw/0/rotate/39.bmp","resources/claw/0/rotate/40.bmp","resources/claw/0/rotate/41.bmp","resources/claw/0/rotate/42.bmp","resources/claw/0/rotate/43.bmp","resources/claw/0/rotate/44.bmp","resources/claw/0/rotate/45.bmp","resources/claw/0/rotate/46.bmp","resources/claw/0/rotate/47.bmp","resources/claw/0/rotate/48.bmp","resources/claw/0/rotate/49.bmp","resources/claw/0/rotate/50.bmp","resources/claw/0/rotate/51.bmp","resources/claw/0/rotate/52.bmp","resources/claw/0/rotate/53.bmp","resources/claw/0/rotate/54.bmp" }, RGB(0, 0, 0));
	claw.SetTopLeft(0, 20);
	claw.SetAnimation(50, false);

	LoadClaws();

	exit.LoadBitmapByString({ "resources/exit/1.bmp", "resources/exit/2.bmp" }, RGB(0, 0, 0));
	exit.SetTopLeft(800, 12);

	fail.LoadBitmapByString({ "resources/fail_page/140.bmp","resources/fail_page/141.bmp","resources/fail_page/142.bmp","resources/fail_page/143.bmp","resources/fail_page/144.bmp","resources/fail_page/145.bmp","resources/fail_page/146.bmp","resources/fail_page/147.bmp","resources/fail_page/148.bmp","resources/fail_page/149.bmp","resources/fail_page/150.bmp","resources/fail_page/151.bmp","resources/fail_page/152.bmp","resources/fail_page/153.bmp","resources/fail_page/154.bmp","resources/fail_page/155.bmp","resources/fail_page/156.bmp","resources/fail_page/157.bmp","resources/fail_page/158.bmp","resources/fail_page/159.bmp","resources/fail_page/160.bmp","resources/fail_page/161.bmp","resources/fail_page/162.bmp","resources/fail_page/163.bmp","resources/fail_page/164.bmp","resources/fail_page/165.bmp","resources/fail_page/166.bmp","resources/fail_page/167.bmp","resources/fail_page/168.bmp" });
	fail.SetTopLeft(0, 0);
	fail.SetAnimation(50, true);

	success.LoadBitmapByString({ "resources/success_page/94.bmp","resources/success_page/95.bmp","resources/success_page/96.bmp","resources/success_page/97.bmp","resources/success_page/98.bmp","resources/success_page/99.bmp","resources/success_page/100.bmp","resources/success_page/101.bmp","resources/success_page/102.bmp","resources/success_page/103.bmp","resources/success_page/104.bmp","resources/success_page/105.bmp","resources/success_page/106.bmp","resources/success_page/107.bmp","resources/success_page/108.bmp","resources/success_page/109.bmp","resources/success_page/110.bmp","resources/success_page/111.bmp","resources/success_page/112.bmp","resources/success_page/113.bmp","resources/success_page/114.bmp","resources/success_page/115.bmp","resources/success_page/116.bmp","resources/success_page/117.bmp","resources/success_page/118.bmp","resources/success_page/119.bmp","resources/success_page/120.bmp","resources/success_page/121.bmp","resources/success_page/122.bmp","resources/success_page/123.bmp","resources/success_page/124.bmp","resources/success_page/125.bmp","resources/success_page/126.bmp","resources/success_page/127.bmp","resources/success_page/128.bmp","resources/success_page/129.bmp" });
	success.SetTopLeft(0, 0);
	success.SetAnimation(50, true);


	shop_bg.LoadBitmapByString({ "resources/shop_page/shop_bg.bmp" });
	shop_bg.SetTopLeft(0, 0);

	//shop_table.LoadBitmapByString({ "resources/shop_page/shop_table.bmp" }, RGB(0, 0, 0));
	//shop_table.SetTopLeft(2, 108);

	//next_level_button.LoadBitmapByString({ "resources/shop_page/next_level_button.bmp" }, RGB(0, 0, 0));
	//next_level_button.SetTopLeft(0, 0);

	owner_talk.LoadBitmapByString({"resources/shop_page/owner/talk/1.bmp","resources/shop_page/owner/talk/2.bmp","resources/shop_page/owner/talk/3.bmp","resources/shop_page/owner/talk/4.bmp","resources/shop_page/owner/talk/5.bmp","resources/shop_page/owner/talk/6.bmp","resources/shop_page/owner/talk/7.bmp","resources/shop_page/owner/talk/8.bmp","resources/shop_page/owner/talk/9.bmp","resources/shop_page/owner/talk/10.bmp","resources/shop_page/owner/talk/11.bmp","resources/shop_page/owner/talk/12.bmp","resources/shop_page/owner/talk/13.bmp","resources/shop_page/owner/talk/14.bmp","resources/shop_page/owner/talk/15.bmp","resources/shop_page/owner/talk/16.bmp","resources/shop_page/owner/talk/17.bmp","resources/shop_page/owner/talk/18.bmp"}, RGB(0, 0, 0));
	owner_talk.SetTopLeft(-4, 186);
	owner_talk.SetAnimation(50, true);

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
			key_down_angle = claw.GetAngleOfClaw();
			ToggleClaws();
		}
	}
	if (nChar == VK_UP) {
		action_state = 2;
	}
	if (nChar == VK_RIGHT) {
		sub_phase = 3;
	}
	if (nChar == VK_LEFT) {
		money = money + 100;
		timer = timer - 5;
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
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	if (point.x >= exit.GetLeft() && point.x <= exit.GetLeft() + exit.GetWidth() && point.y >= exit.GetTop() && point.y <= exit.GetTop() + exit.GetHeight() && position_correct == 1)
	{
		exit.SetFrameIndexOfBitmap(1);
	}
	
	else 
	{
		exit.SetFrameIndexOfBitmap(0);
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
	show_claw_by_angle();
	if (sub_phase == 2){
		show_text_by_phase();
	}
	if (gameover == true) {
		gameover_and_restart();
	}
}

void CGameStateRun::show_image_by_phase() {

	if (phase == 1 && sub_phase == 1) 
	{
		gameover = false;
		goal.ShowBitmap();
		if (goal.GetFrameIndexOfBitmap() == 0 && goal.IsAnimation() == false)
		{
			goal.ToggleAnimation();
		}
	}
	if (phase == 1 && sub_phase == 2 && action_state == 1) 
	{
		goal.UnshowBitmap();
		background.ShowBitmap();
		miner.ShowBitmap();
		exit.ShowBitmap();
		claw.ShowBitmap();
		
	}
	if (phase == 1 && sub_phase == 2 && action_state == 2)
	{
		miner.UnshowBitmap();
		background.ShowBitmap();
		miner_t.ShowBitmap();
		exit.ShowBitmap();
		claw.ShowBitmap();
		
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
	if (phase == 1 && sub_phase == 3)
	{
		if (success.GetFrameIndexOfBitmap() == 0 && success.IsAnimation() == false)
		{
			success.ToggleAnimation();
		}
		if (success.IsAnimation() == true)
		{
			success.ShowBitmap();
		}
		if (success.IsAnimation() == false && success.GetFrameIndexOfBitmap() != 0)
		{
			shop_bg.ShowBitmap();
			//shop_table.ShowBitmap();
			//next_level_button.ShowBitmap();

			owner_talk.ShowBitmap();
			if (owner_talk.GetFrameIndexOfBitmap() == 0 && owner_talk.IsAnimation() == false) 
			{
				owner_talk.ToggleAnimation();
			}

			item_1.ShowBitmap();
			item_2.ShowBitmap();
			item_3.ShowBitmap();
			item_4.ShowBitmap();
			item_5.ShowBitmap();
		}
		
	}


}

void CGameStateRun::set_goal_money()
{
	for (int i = 1 ; i < 10 ; i++) 
	{
		if (phase == i) {
			goal_money = goal_money_of_level[i-1];
		}
	}
}

void CGameStateRun::gameover_and_restart()
{
	fail.ShowBitmap();

	if (fail.GetFrameIndexOfBitmap() == 0 && fail.IsAnimation() == false) {
		fail.ToggleAnimation();
	}
	if (fail.IsAnimation() == false && fail.GetFrameIndexOfBitmap() != 0) {
		GotoGameState(GAME_STATE_INIT);
		fail.SetFrameIndexOfBitmap(0);
		goal.SetFrameIndexOfBitmap(0);
		money = 0;
		sub_phase = 1;
		timer = 61;
	}
}

void CGameStateRun::LoadClaws()
{
	claw1_2.LoadBitmapByString({ "resources/claw/1/rotate/2/3.bmp","resources/claw/1/rotate/2/4.bmp","resources/claw/1/rotate/2/5.bmp","resources/claw/1/rotate/2/6.bmp","resources/claw/1/rotate/2/7.bmp","resources/claw/1/rotate/2/8.bmp","resources/claw/1/rotate/2/9.bmp","resources/claw/1/rotate/2/10.bmp","resources/claw/1/rotate/2/11.bmp","resources/claw/1/rotate/2/12.bmp","resources/claw/1/rotate/2/13.bmp","resources/claw/1/rotate/2/14.bmp","resources/claw/1/rotate/2/15.bmp","resources/claw/1/rotate/2/16.bmp","resources/claw/1/rotate/2/17.bmp","resources/claw/1/rotate/2/18.bmp","resources/claw/1/rotate/2/19.bmp","resources/claw/1/rotate/2/20.bmp","resources/claw/1/rotate/2/21.bmp","resources/claw/1/rotate/2/22.bmp","resources/claw/1/rotate/2/23.bmp","resources/claw/1/rotate/2/24.bmp","resources/claw/1/rotate/2/25.bmp","resources/claw/1/rotate/2/26.bmp","resources/claw/1/rotate/2/27.bmp","resources/claw/1/rotate/2/28.bmp","resources/claw/1/rotate/2/29.bmp","resources/claw/1/rotate/2/30.bmp","resources/claw/1/rotate/2/31.bmp","resources/claw/1/rotate/2/32.bmp","resources/claw/1/rotate/2/33.bmp","resources/claw/1/rotate/2/34.bmp","resources/claw/1/rotate/2/35.bmp","resources/claw/1/rotate/2/36.bmp","resources/claw/1/rotate/2/37.bmp","resources/claw/1/rotate/2/38.bmp","resources/claw/1/rotate/2/39.bmp","resources/claw/1/rotate/2/40.bmp","resources/claw/1/rotate/2/41.bmp","resources/claw/1/rotate/2/42.bmp" }, RGB(0, 0, 0));
	claw1_2.SetTopLeft(0, 20);
	claw1_2.SetAnimation(50, true);

	claw1_n5.LoadBitmapByString({ "resources/claw/1/rotate/-5/3.bmp","resources/claw/1/rotate/-5/4.bmp","resources/claw/1/rotate/-5/5.bmp","resources/claw/1/rotate/-5/6.bmp","resources/claw/1/rotate/-5/7.bmp","resources/claw/1/rotate/-5/8.bmp","resources/claw/1/rotate/-5/9.bmp","resources/claw/1/rotate/-5/10.bmp","resources/claw/1/rotate/-5/11.bmp","resources/claw/1/rotate/-5/12.bmp","resources/claw/1/rotate/-5/13.bmp","resources/claw/1/rotate/-5/14.bmp","resources/claw/1/rotate/-5/15.bmp","resources/claw/1/rotate/-5/16.bmp","resources/claw/1/rotate/-5/17.bmp","resources/claw/1/rotate/-5/18.bmp","resources/claw/1/rotate/-5/19.bmp","resources/claw/1/rotate/-5/20.bmp","resources/claw/1/rotate/-5/21.bmp","resources/claw/1/rotate/-5/22.bmp","resources/claw/1/rotate/-5/23.bmp","resources/claw/1/rotate/-5/24.bmp","resources/claw/1/rotate/-5/25.bmp","resources/claw/1/rotate/-5/26.bmp","resources/claw/1/rotate/-5/27.bmp","resources/claw/1/rotate/-5/28.bmp","resources/claw/1/rotate/-5/29.bmp","resources/claw/1/rotate/-5/30.bmp","resources/claw/1/rotate/-5/31.bmp","resources/claw/1/rotate/-5/32.bmp","resources/claw/1/rotate/-5/33.bmp","resources/claw/1/rotate/-5/34.bmp","resources/claw/1/rotate/-5/35.bmp","resources/claw/1/rotate/-5/36.bmp","resources/claw/1/rotate/-5/37.bmp","resources/claw/1/rotate/-5/38.bmp","resources/claw/1/rotate/-5/39.bmp","resources/claw/1/rotate/-5/40.bmp","resources/claw/1/rotate/-5/41.bmp","resources/claw/1/rotate/-5/42.bmp" }, RGB(0, 0, 0));
	claw1_n5.SetTopLeft(0, 20);
	claw1_n5.SetAnimation(50, true);
}

void CGameStateRun::ToggleClaws()
{
	if (key_down_angle == 1)
	{
		claw1_2.ToggleAnimation();
	}
	if (key_down_angle == 0)
	{
		claw1_n5.ToggleAnimation();
	}

}
void CGameStateRun::show_claw_by_angle()
{
	claw_is_ready = true;
	if ((miner.IsAnimation() && key_down_angle == 1) || claw1_2.IsAnimation()) {
		claw1_2.ShowBitmap();
		claw_is_ready = false;
	}
	if ((miner.IsAnimation() && key_down_angle == 0) || claw1_n5.IsAnimation()) {
		claw1_n5.ShowBitmap();
		claw_is_ready = false;
	}
}

void CGameStateRun::show_text_by_phase() {
	
	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 25, "新細明體", RGB(255, 102, 0), 15000);
	
	if (phase == 1 && sub_phase == 2 && timer > 0) {
		CTextDraw::Print(pDC, 1033, 10, std::to_string(timer));

		if (clock() - last_time > 1000)
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