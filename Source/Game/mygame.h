/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		

	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo;								// csie的logo
		CMovingBitmap start_button;
		CMovingBitmap background;
		CMovingBitmap instructions;
		CMovingBitmap gold;
		CMovingBitmap light;
		CMovingBitmap oldman;
		CMovingBitmap instructions_text;
		CMovingBitmap close;
		bool instructions_clicked = false;
		void load_Background();
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void LoadClaws();
		void OnKeyDown(UINT, UINT, UINT);
		void ToggleClaws();
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int phase = 1;					//phase = 1 為第一關， = 2 為第二關，以此類推
		int sub_phase = 1;				//sub_phase = 1 為goal_page， = 2 為掏金關卡， = 3 為shop_page
		int action_state = 1;			//action_state = 1 為正常動作??????
		int key_down_angle = -100;      //紀錄按下(down key)時的角度(Index)，預設為-100度
		bool claw_is_ready = true;		//當claw_is_ready = true時才可以出爪子
		int last_time;					//用來記錄clock()上次的取樣時間

		/*這四個參數是用來控制goal page的淡出效果*/
		int last_time_fade;				//用來記錄clock()上次的取樣時間of fade
		int fade_rate = 1;				//淡出速率
		int color_now1[3];				//記錄RGB(黃色)
		int color_now2[3];				//記錄RGB(綠色)

		int timer  = 61;				//每關的預設時間為timer-1
		bool item_is_bought_1 = false;		//這啥 許君豪看到請解釋，沈志謙這是確認做愛位置是否正確，然後鈞打錯了，我有點忘記當初打什麼鬼，但好像可以刪掉??，我試過沒有什麼差
		bool item_is_bought_2 = false;
		bool item_is_bought_3 = false;
		bool item_is_bought_4 = false;
		bool item_is_bought_5 = false;
		bool next_level_button_clicked = false;
		bool return_game = false;
		int item_in_stock_in_level[5] = { 0, 0, 0 ,0, 0 };
		

		int money = 0;
		int goal_money = 650;
		//int goal_money_of_level[10] = { 600,1000 };
		bool gameover = false;			// = true 時播放結束動畫並返回主頁面
		CMovingBitmap goal;
		CMovingBitmap background;
	
		CMovingBitmap miner;
		CMovingBitmap miner_t;
		CMovingBitmap miner_s;
		CMovingBitmap timer_bling;
		CMovingBitmap claw;
		CMovingBitmap claw1_2;
		CMovingBitmap claw1_n5;
		CMovingBitmap exit;
		CMovingBitmap exit_background;
		CMovingBitmap playagain_button;
		CMovingBitmap fail;
		CMovingBitmap success;
		CMovingBitmap shop_bg;
		CMovingBitmap next_level_button;
		CMovingBitmap owner_talk;
		CMovingBitmap owner_buy;
		CMovingBitmap owner_angry;
	
		CMovingBitmap item_1;			//商店商品:炸藥
		CMovingBitmap item_2;			//商店商品:力量增強藥
		CMovingBitmap item_3;			//商店商品:幸運草
		CMovingBitmap item_4;			//商店商品:石頭書
		CMovingBitmap item_5;			//商店商品:咖啡

		/*
		CMovingBitmap goal_650;
		CMovingBitmap goal_1195;
		CMovingBitmap goal_2010;
		CMovingBitmap goal_3095;
		CMovingBitmap goal_4450;
		*/

		//CAudio goal_audio;
		void show_image_by_phase();
		void show_claw_by_angle();
		void gameover_and_restart();
		void show_text_by_phase();
		void show_text_of_goals();
		void set_goal_money();
		void goto_next_stage();
		void show_items();
		void set_stock();

		
		
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
		
	};

}
