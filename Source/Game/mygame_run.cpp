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
	background.LoadBitmapByString({"resources/stage/1_1.bmp"});
	background.SetTopLeft(0, 0);
	miner.LoadBitmapByString({"resources/miner/normal/1.bmp","resources/miner/normal/2.bmp","resources/miner/normal/3.bmp","resources/miner/normal/4.bmp","resources/miner/normal/5.bmp"}, RGB(0, 0, 0));
	miner.SetTopLeft(529, 33);
	miner.SetAnimation(200, true);
	miner_t.LoadBitmapByString({ "resources/miner/throw/1.bmp","resources/miner/throw/2.bmp","resources/miner/throw/3.bmp","resources/miner/throw/4.bmp","resources/miner/throw/5.bmp","resources/miner/throw/6.bmp","resources/miner/throw/7.bmp","resources/miner/throw/8.bmp","resources/miner/throw/9.bmp","resources/miner/throw/10.bmp","resources/miner/throw/11.bmp","resources/miner/throw/12.bmp","resources/miner/throw/13.bmp","resources/miner/throw/14.bmp","resources/miner/throw/15.bmp","resources/miner/throw/16.bmp","resources/miner/throw/17.bmp","resources/miner/throw/18.bmp","resources/miner/throw/19.bmp","resources/miner/throw/20.bmp","resources/miner/throw/21.bmp","resources/miner/throw/22.bmp","resources/miner/throw/23.bmp","resources/miner/throw/24.bmp","resources/miner/throw/25.bmp","resources/miner/throw/26.bmp","resources/miner/throw/27.bmp","resources/miner/throw/28.bmp","resources/miner/throw/29.bmp","resources/miner/throw/30.bmp","resources/miner/throw/31.bmp","resources/miner/throw/32.bmp","resources/miner/throw/33.bmp","resources/miner/throw/34.bmp","resources/miner/throw/35.bmp","resources/miner/throw/36.bmp","resources/miner/throw/37.bmp"}, RGB(0, 0, 0));
	miner_t.SetTopLeft(529, 23);
	miner_t.SetAnimation(20, true);
	miner_s.LoadBitmapByString({ "resources/miner/strength/1.bmp","resources/miner/strength/2.bmp","resources/miner/strength/3.bmp","resources/miner/strength/4.bmp","resources/miner/strength/5.bmp","resources/miner/strength/6.bmp","resources/miner/strength/7.bmp","resources/miner/strength/8.bmp","resources/miner/strength/9.bmp","resources/miner/strength/10.bmp","resources/miner/strength/11.bmp","resources/miner/strength/12.bmp","resources/miner/strength/13.bmp","resources/miner/strength/14.bmp","resources/miner/strength/15.bmp","resources/miner/strength/16.bmp" }, RGB(0, 0, 0));
	miner_s.SetTopLeft(529, 33);
	miner_s.SetAnimation(200, true);
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
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
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
		goal.ShowBitmap();
		if (goal.GetFrameIndexOfBitmap() == 0 && goal.IsAnimation() == false)
		{
			goal.ToggleAnimation();
		}
	}
	if (phase == 1 && sub_phase == 2) 
	{
		goal.UnshowBitmap();
		background.ShowBitmap();
		miner.ShowBitmap();
	}
	if (phase == 1 && sub_phase == 2 && action_state == 2)
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
