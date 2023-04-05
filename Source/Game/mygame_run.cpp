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
	//set_goal_money();
	//set_stock();
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
	goal.LoadBitmapByString({ "resources/goal_page/600/15.bmp","resources/goal_page/600/16.bmp","resources/goal_page/600/17.bmp","resources/goal_page/600/18.bmp","resources/goal_page/600/19.bmp","resources/goal_page/600/20.bmp","resources/goal_page/600/21.bmp","resources/goal_page/600/22.bmp","resources/goal_page/600/23.bmp","resources/goal_page/600/24.bmp","resources/goal_page/600/25.bmp","resources/goal_page/600/26.bmp","resources/goal_page/600/27.bmp","resources/goal_page/600/28.bmp","resources/goal_page/600/29.bmp","resources/goal_page/600/30.bmp","resources/goal_page/600/31.bmp","resources/goal_page/600/32.bmp","resources/goal_page/600/33.bmp","resources/goal_page/600/34.bmp","resources/goal_page/600/35.bmp","resources/goal_page/600/36.bmp","resources/goal_page/600/37.bmp","resources/goal_page/600/38.bmp","resources/goal_page/600/39.bmp","resources/goal_page/600/40.bmp","resources/goal_page/600/41.bmp","resources/goal_page/600/42.bmp","resources/goal_page/600/43.bmp","resources/goal_page/600/44.bmp","resources/goal_page/600/45.bmp","resources/goal_page/600/46.bmp","resources/goal_page/600/47.bmp","resources/goal_page/600/48.bmp","resources/goal_page/600/49.bmp","resources/goal_page/600/50.bmp","resources/goal_page/600/51.bmp" });
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
	next_level_button.SetTopLeft(0, 0);

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

	/*goal*/
	goal_650.LoadBitmapByString({"Resources/goal_page/650/15.bmp","Resources/goal_page/650/16.bmp","Resources/goal_page/650/17.bmp","Resources/goal_page/650/18.bmp","Resources/goal_page/650/19.bmp","Resources/goal_page/650/20.bmp","Resources/goal_page/650/21.bmp","Resources/goal_page/650/22.bmp","Resources/goal_page/650/23.bmp","Resources/goal_page/650/24.bmp","Resources/goal_page/650/25.bmp","Resources/goal_page/650/26.bmp","Resources/goal_page/650/27.bmp","Resources/goal_page/650/28.bmp","Resources/goal_page/650/29.bmp","Resources/goal_page/650/30.bmp","Resources/goal_page/650/31.bmp","Resources/goal_page/650/32.bmp","Resources/goal_page/650/33.bmp","Resources/goal_page/650/34.bmp","Resources/goal_page/650/35.bmp","Resources/goal_page/650/36.bmp","Resources/goal_page/650/37.bmp","Resources/goal_page/650/38.bmp","Resources/goal_page/650/39.bmp","Resources/goal_page/650/40.bmp","Resources/goal_page/650/41.bmp","Resources/goal_page/650/42.bmp","Resources/goal_page/650/43.bmp","Resources/goal_page/650/44.bmp","Resources/goal_page/650/45.bmp","Resources/goal_page/650/46.bmp","Resources/goal_page/650/47.bmp","Resources/goal_page/650/48.bmp","Resources/goal_page/650/49.bmp","Resources/goal_page/650/50.bmp","Resources/goal_page/650/51.bmp"}, RGB(0, 0, 0));
	goal_650.SetAnimation(50, true);
	goal_650.SetTopLeft(0, 0);

	goal_1195.LoadBitmapByString({ "resources/goal_page/1195/52.bmp","resources/goal_page/1195/53.bmp","resources/goal_page/1195/54.bmp","resources/goal_page/1195/55.bmp","resources/goal_page/1195/56.bmp","resources/goal_page/1195/57.bmp","resources/goal_page/1195/58.bmp","resources/goal_page/1195/59.bmp","resources/goal_page/1195/60.bmp","resources/goal_page/1195/61.bmp","resources/goal_page/1195/62.bmp","resources/goal_page/1195/63.bmp","resources/goal_page/1195/64.bmp","resources/goal_page/1195/65.bmp","resources/goal_page/1195/66.bmp","resources/goal_page/1195/67.bmp","resources/goal_page/1195/68.bmp","resources/goal_page/1195/69.bmp","resources/goal_page/1195/70.bmp","resources/goal_page/1195/71.bmp","resources/goal_page/1195/72.bmp","resources/goal_page/1195/73.bmp","resources/goal_page/1195/74.bmp","resources/goal_page/1195/75.bmp","resources/goal_page/1195/76.bmp","resources/goal_page/1195/77.bmp","resources/goal_page/1195/78.bmp","resources/goal_page/1195/79.bmp","resources/goal_page/1195/80.bmp","resources/goal_page/1195/81.bmp","resources/goal_page/1195/82.bmp","resources/goal_page/1195/83.bmp","resources/goal_page/1195/84.bmp","resources/goal_page/1195/85.bmp","resources/goal_page/1195/86.bmp","resources/goal_page/1195/87.bmp","resources/goal_page/1195/88.bmp","resources/goal_page/1195/89.bmp","resources/goal_page/1195/90.bmp","resources/goal_page/1195/91.bmp","resources/goal_page/1195/92.bmp","resources/goal_page/1195/93.bmp"}, RGB(0, 0, 0));
	goal_1195.SetAnimation(50, true);
	goal_1195.SetTopLeft(0, 0);

	goal_2010.LoadBitmapByString({"resources/goal_page/2010/52.bmp","resources/goal_page/2010/53.bmp","resources/goal_page/2010/54.bmp","resources/goal_page/2010/55.bmp","resources/goal_page/2010/56.bmp","resources/goal_page/2010/57.bmp","resources/goal_page/2010/58.bmp","resources/goal_page/2010/59.bmp","resources/goal_page/2010/60.bmp","resources/goal_page/2010/61.bmp","resources/goal_page/2010/62.bmp","resources/goal_page/2010/63.bmp","resources/goal_page/2010/64.bmp","resources/goal_page/2010/65.bmp","resources/goal_page/2010/66.bmp","resources/goal_page/2010/67.bmp","resources/goal_page/2010/68.bmp","resources/goal_page/2010/69.bmp","resources/goal_page/2010/70.bmp","resources/goal_page/2010/71.bmp","resources/goal_page/2010/72.bmp","resources/goal_page/2010/73.bmp","resources/goal_page/2010/74.bmp","resources/goal_page/2010/75.bmp","resources/goal_page/2010/76.bmp","resources/goal_page/2010/77.bmp","resources/goal_page/2010/78.bmp","resources/goal_page/2010/79.bmp","resources/goal_page/2010/80.bmp","resources/goal_page/2010/81.bmp","resources/goal_page/2010/82.bmp","resources/goal_page/2010/83.bmp","resources/goal_page/2010/84.bmp","resources/goal_page/2010/85.bmp","resources/goal_page/2010/86.bmp","resources/goal_page/2010/87.bmp","resources/goal_page/2010/88.bmp","resources/goal_page/2010/89.bmp","resources/goal_page/2010/90.bmp","resources/goal_page/2010/91.bmp","resources/goal_page/2010/92.bmp","resources/goal_page/2010/93.bmp"}, RGB(0, 0, 0));
	goal_2010.SetAnimation(50, true);
	goal_2010.SetTopLeft(0, 0);
	
	goal_3095.LoadBitmapByString({ "resources/goal_page/3095/52.bmp","resources/goal_page/3095/53.bmp","resources/goal_page/3095/54.bmp","resources/goal_page/3095/55.bmp","resources/goal_page/3095/56.bmp","resources/goal_page/3095/57.bmp","resources/goal_page/3095/58.bmp","resources/goal_page/3095/59.bmp","resources/goal_page/3095/60.bmp","resources/goal_page/3095/61.bmp","resources/goal_page/3095/62.bmp","resources/goal_page/3095/63.bmp","resources/goal_page/3095/64.bmp","resources/goal_page/3095/65.bmp","resources/goal_page/3095/66.bmp","resources/goal_page/3095/67.bmp","resources/goal_page/3095/68.bmp","resources/goal_page/3095/69.bmp","resources/goal_page/3095/70.bmp","resources/goal_page/3095/71.bmp","resources/goal_page/3095/72.bmp","resources/goal_page/3095/73.bmp","resources/goal_page/3095/74.bmp","resources/goal_page/3095/75.bmp","resources/goal_page/3095/76.bmp","resources/goal_page/3095/77.bmp","resources/goal_page/3095/78.bmp","resources/goal_page/3095/79.bmp","resources/goal_page/3095/80.bmp","resources/goal_page/3095/81.bmp","resources/goal_page/3095/82.bmp","resources/goal_page/3095/83.bmp","resources/goal_page/3095/84.bmp","resources/goal_page/3095/85.bmp","resources/goal_page/3095/86.bmp","resources/goal_page/3095/87.bmp","resources/goal_page/3095/88.bmp","resources/goal_page/3095/89.bmp","resources/goal_page/3095/90.bmp","resources/goal_page/3095/91.bmp","resources/goal_page/3095/92.bmp","resources/goal_page/3095/93.bmp"}, RGB(0, 0, 0));
	goal_3095.SetAnimation(50, true);
	goal_3095.SetTopLeft(0, 0);
	/*
	goal_4450.LoadBitmapByString({"resources/goal_page/4450/52.bmp","resources/goal_page/4450/53.bmp","resources/goal_page/4450/54.bmp","resources/goal_page/4450/55.bmp","resources/goal_page/4450/56.bmp","resources/goal_page/4450/57.bmp","resources/goal_page/4450/58.bmp","resources/goal_page/4450/59.bmp","resources/goal_page/4450/60.bmp","resources/goal_page/4450/61.bmp","resources/goal_page/4450/62.bmp","resources/goal_page/4450/63.bmp","resources/goal_page/4450/64.bmp","resources/goal_page/4450/65.bmp","resources/goal_page/4450/66.bmp","resources/goal_page/4450/67.bmp","resources/goal_page/4450/68.bmp","resources/goal_page/4450/69.bmp","resources/goal_page/4450/70.bmp","resources/goal_page/4450/71.bmp","resources/goal_page/4450/72.bmp","resources/goal_page/4450/73.bmp","resources/goal_page/4450/74.bmp","resources/goal_page/4450/75.bmp","resources/goal_page/4450/76.bmp","resources/goal_page/4450/77.bmp","resources/goal_page/4450/78.bmp","resources/goal_page/4450/79.bmp","resources/goal_page/4450/80.bmp","resources/goal_page/4450/81.bmp","resources/goal_page/4450/82.bmp","resources/goal_page/4450/83.bmp","resources/goal_page/4450/84.bmp","resources/goal_page/4450/85.bmp","resources/goal_page/4450/86.bmp","resources/goal_page/4450/87.bmp","resources/goal_page/4450/88.bmp","resources/goal_page/4450/89.bmp","resources/goal_page/4450/90.bmp","resources/goal_page/4450/91.bmp","resources/goal_page/4450/92.bmp","resources/goal_page/4450/93.bmp"});
	goal_4450.SetAnimation(50, true);
	goal_4450.SetTopLeft(0, 0);
	*/
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
	if (point.x >= exit.GetLeft() && point.x <= exit.GetLeft() + exit.GetWidth() && point.y >= exit.GetTop() && point.y <= exit.GetTop() + exit.GetHeight())
	{
		exit.SetFrameIndexOfBitmap(1);
	}
	else 
	{
		exit.SetFrameIndexOfBitmap(0);
	}
	
	if (point.x >= next_level_button.GetLeft() && point.x <= next_level_button.GetLeft() + next_level_button.GetWidth() && point.y >= next_level_button.GetTop() && point.y <= next_level_button.GetTop() + next_level_button.GetHeight())
	{
		next_level_button.SetFrameIndexOfBitmap(1);
	}
	else
	{
		next_level_button.SetFrameIndexOfBitmap(0);
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
	if ((clock() % 1000) > 700 && timer <= 10 && timer > 0) {
		timer_bling.ShowBitmap();
	}

	if (sub_phase == 2){
		show_text_by_phase();
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
		if (goal.GetFrameIndexOfBitmap() == 0 && goal.IsAnimation() == false)
		{
			goal.ToggleAnimation();
		}
	}
	if (sub_phase == 2 && action_state == 1) 
	{
		goal.UnshowBitmap();
		background.ShowBitmap();
		miner.ShowBitmap();
		exit.ShowBitmap();
		if (claw_is_ready == true) 
		{
			claw.ShowBitmap();
		}
		
	}
	if (sub_phase == 2 && action_state == 2)
	{
		miner.UnshowBitmap();
		background.ShowBitmap();
		miner_t.ShowBitmap();
		exit.ShowBitmap();
		if (claw_is_ready == true) 
		{
			claw.ShowBitmap();
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

	/*
	for (int i = 1 ; i < 10 ; i++) 
	{
		if (phase == i) {
			goal_money = goal_money_of_level[i-1];
		}
	}
	*/
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
		phase = 1;
		goal_money = 650;
	}
}
void CGameStateRun::goto_next_stage()
{
	timer = 61;
	goal.SetFrameIndexOfBitmap(0);
	success.SetFrameIndexOfBitmap(0);
	sub_phase = 1;
	phase = phase + 1;
	background.SetFrameIndexOfBitmap(phase-1);
	owner_buy.SetFrameIndexOfBitmap(0);
	owner_angry.SetFrameIndexOfBitmap(0);
	next_level_button_clicked = false;
	set_goal_money();
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
	if (sub_phase == 2) {
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
}

void CGameStateRun::show_text_by_phase() {
	
	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 25, "新細明體", RGB(255, 102, 0), 15000);
	
	if (sub_phase == 2 && timer > 0) {
		
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