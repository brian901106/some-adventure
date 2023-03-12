#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

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
	if (goal.IsAnimationDone() && sub_phase == 1)
	{
		sub_phase += 1;
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

	exit.LoadBitmapByString({ "resources/exit/1.bmp", "resources/exit/2.bmp" }, RGB(0, 0, 0));
	exit.SetTopLeft(800, 12);

	fail.LoadBitmapByString({ "resources/fail_page/140.bmp","resources/fail_page/141.bmp","resources/fail_page/142.bmp","resources/fail_page/143.bmp","resources/fail_page/144.bmp","resources/fail_page/145.bmp","resources/fail_page/146.bmp","resources/fail_page/147.bmp","resources/fail_page/148.bmp","resources/fail_page/149.bmp","resources/fail_page/150.bmp","resources/fail_page/151.bmp","resources/fail_page/152.bmp","resources/fail_page/153.bmp","resources/fail_page/154.bmp","resources/fail_page/155.bmp","resources/fail_page/156.bmp","resources/fail_page/157.bmp","resources/fail_page/158.bmp","resources/fail_page/159.bmp","resources/fail_page/160.bmp","resources/fail_page/161.bmp","resources/fail_page/162.bmp","resources/fail_page/163.bmp","resources/fail_page/164.bmp","resources/fail_page/165.bmp","resources/fail_page/166.bmp","resources/fail_page/167.bmp","resources/fail_page/168.bmp" });
	fail.SetTopLeft(0, 0);
	fail.SetAnimation(50, true);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN) {
		miner.ToggleAnimation();
	}
	if (nChar == VK_UP) {
		action_state = 2;
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
		if (gameover == true) {
			gameover_and_restart();
		}
		
	}
	if (phase == 1 && sub_phase == 2 && action_state == 2)
	{
		miner.UnshowBitmap();
		background.ShowBitmap();
		miner_t.ShowBitmap();
		exit.ShowBitmap();
		claw.ShowBitmap();
		if (gameover == true) {
			gameover_and_restart();
		}
		
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
		sub_phase = 1;
	}
}
