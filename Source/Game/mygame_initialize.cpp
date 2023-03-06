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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%
	load_Background();
	//
	// 開始載入資料
	//
	//Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//

}

void CGameStateInit::OnBeginState()
{

}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);			// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	background.ShowBitmap();

	//light.ShowBitmap();
	gold.ShowBitmap();
	start_button.ShowBitmap();
	instructions.ShowBitmap();

}

void CGameStateInit::load_Background() 
{
	background.LoadBitmapByString({ "resources/start_page/start_background.bmp" });
	background.SetTopLeft(0, 0);
	start_button.LoadBitmapByString({ "resources/start_page/start.bmp" }, RGB(0, 0, 0));
	start_button.SetTopLeft(58, 53);
	instructions.LoadBitmapByString({ "resources/start_page/instructions.bmp" }, RGB(0, 0, 0));
	instructions.SetTopLeft(175, 548);
	gold.LoadBitmapByString({ "resources/start_page/gold.bmp" }, RGB(0, 0, 0));
	gold.SetTopLeft(58, 53);

	light.LoadBitmapByString({ "resources/start_page/light/1.bmp","resources/start_page/light/2.bmp","resources/start_page/light/3.bmp","resources/start_page/light/4.bmp","resources/start_page/light/5.bmp","resources/start_page/light/6.bmp","resources/start_page/light/7.bmp","resources/start_page/light/8.bmp","resources/start_page/light/9.bmp","resources/start_page/light/10.bmp","resources/start_page/light/11.bmp","resources/start_page/light/12.bmp","resources/start_page/light/13.bmp","resources/start_page/light/14.bmp","resources/start_page/light/15.bmp","resources/start_page/light/16.bmp","resources/start_page/light/17.bmp","resources/start_page/light/18.bmp","resources/start_page/light/19.bmp","resources/start_page/light/20.bmp","resources/start_page/light/21.bmp","resources/start_page/light/22.bmp","resources/start_page/light/23.bmp","resources/start_page/light/24.bmp","resources/start_page/light/25.bmp","resources/start_page/light/26.bmp","resources/start_page/light/27.bmp","resources/start_page/light/28.bmp","resources/start_page/light/29.bmp","resources/start_page/light/30.bmp","resources/start_page/light/31.bmp","resources/start_page/light/32.bmp","resources/start_page/light/33.bmp","resources/start_page/light/34.bmp","resources/start_page/light/35.bmp","resources/start_page/light/36.bmp","resources/start_page/light/37.bmp","resources/start_page/light/38.bmp","resources/start_page/light/39.bmp","resources/start_page/light/40.bmp","resources/start_page/light/41.bmp","resources/start_page/light/42.bmp","resources/start_page/light/43.bmp","resources/start_page/light/44.bmp","resources/start_page/light/45.bmp","resources/start_page/light/46.bmp","resources/start_page/light/47.bmp","resources/start_page/light/48.bmp","resources/start_page/light/49.bmp","resources/start_page/light/50.bmp","resources/start_page/light/51.bmp","resources/start_page/light/52.bmp","resources/start_page/light/53.bmp","resources/start_page/light/54.bmp","resources/start_page/light/55.bmp","resources/start_page/light/56.bmp","resources/start_page/light/57.bmp","resources/start_page/light/58.bmp","resources/start_page/light/59.bmp" }, RGB(0, 0, 0));
	light.SetTopLeft(-90, -85);
	light.SetAnimation(100, false);




}