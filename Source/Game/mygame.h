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
		void OnKeyDown(UINT, UINT, UINT);
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
		int key_down_index = -100;      //紀錄按下(down key)時的Index，預設為-100
		bool claw_is_ready = true;		//當claw_is_ready = true時才可以出爪子
		int last_time_claw;				//紀錄上次更新爪子位置的時間
		int claw_x = 507;				//紀錄爪子的Left，節省運算時間
		int claw_y = 90;				//紀錄爪子的Top，節省運算時間
		int bomb_x = 507;
		int bomb_y = 90;
		int claw_xway[90];				//紀錄爪子shoot出去時，每桢所在的Left，回程收爪時可以call出來
		int claw_yway[90];				//紀錄爪子shoot出去時，每桢所在的Top，回程收爪時可以call出來
		int claw_length = 0;			//紀錄爪子目前長度
		bool hit = false;				//爪子是否有抓到東西
		int weight = 1;					//用來表示抓到礦的重量，越重爪子速度越慢 ,預設為1
		int weight_of_mine[13] = { 100,150,200,400,50,50,400,0,80,50,50,50,300};
		//金礦(小)/金礦(中)/金礦(大)/金礦(巨大)/豬/骨頭/石頭(大)/爆炸桶/鑽石豬/鑽石/道具袋/骷顱頭/石頭(中)

		int last_time_bomb;
		int bomb_num = 2;
		bool bomb_is_throw = false;

		/*這四個參數是用來控制goal page的淡出效果*/
		int last_time_fade;				//用來記錄clock()上次的取樣時間of fade
		int fade_rate = 1;				//淡出速率
		int color_now1[3];				//記錄RGB(黃色)
		int color_now2[3];				//記錄RGB(綠色)
		int last_time;					//用來記錄clock()上次的取樣時間
		int timer  = 61;				//每關的預設時間為timer-1
										//這啥 許君豪看到請解釋，沈志謙這是確認做愛位置是否正確，然後鈞打錯了，我有點忘記當初打什麼鬼，但好像可以刪掉??，我試過沒有什麼差
		
		/*以下參數是用來控制商店商品*/
		bool item_is_bought_1 = false;		//炸藥
		bool item_is_bought_2 = false;		//力量藥水
		bool item_is_bought_3 = false;		//幸運草
		bool item_is_bought_4 = false;		//石頭書
		bool item_is_bought_5 = false;		//鑽石打磨
		bool next_level_button_clicked = false;
		bool return_game = false;
		int item_in_stock_in_level[5] = { 0, 0, 0 ,0, 0 };

		bool item_2_effect = false;			//力量藥水
		bool item_3_effect = false;			//幸運草
		bool item_4_effect = false;			//石頭書
		bool item_5_effect = false;			//鑽石打磨

		int mine_max_num[13] = { 4,3,10,2,10,10,2,10,10,10,2,10,2};	//各種礦在遊戲中的最大值(用來控制loadbitmap數量)

		//第一關的參數
		int mine_num_L1_1[13] = { 4,3,0,2,0,0,2,0,0,0,2,0,2 };
		int location2[4][2] = { {50,200},{100,300},{150,400},{200,500} };	//金礦(小)
		int exist2[4] = { 1,1,1,1 };
		int location3[3][2] = { {150,200},{200,300},{250,400} };	//金礦(中)
		int exist3[3] = { 1,1,1};
		int location5[2][2] = { {250,300},{300,400}};	//金礦(巨大)
		int exist5[2] = { 1,1 };
		int location8[3][2] = { {350,350},{400,450} };	//石頭(大)
		int exist8[2] = { 1,1 };
		int location12[3][2] = { {450,400},{500,450} }; //道具袋
		int exist12[2] = { 1,1 };
		int location14[3][2] = { {550,300},{600,400} };	//石頭(中)
		int exist14[2] = { 1,1 };
		int exist4[1] = { 0 }, exist6[1] = { 0 }, exist7[1] = { 0 }, exist9[1] = { 0 }, exist10[1] = { 0 }, exist11[1] = { 0 }, exist13[1] = { 0 };
		
		int money = 0;
		int goal_money = 650;

		bool gameover = false;			// = true 時播放結束動畫並返回主頁面

		CMovingBitmap goal;
		CMovingBitmap background;
	
		CMovingBitmap miner;
		CMovingBitmap miner_t;
		CMovingBitmap miner_s;

		CMovingBitmap claw;
		CMovingBitmap clawhead;
		CMovingBitmap hitbox;
		CMovingBitmap bomb;

		CMovingBitmap mine2[4];			//金礦(小)
		CMovingBitmap mine3[3];			//金礦(中)
		CMovingBitmap mine4[10];			//金礦(大)
		CMovingBitmap mine5[2];			//金礦(巨大)
		CMovingBitmap mine6[10];			//豬
		CMovingBitmap mine7[10];			//骨頭
		CMovingBitmap mine8[2];			//石頭(大)
		CMovingBitmap mine9[10];			//爆炸桶
		CMovingBitmap mine10[10];			//鑽石豬
		CMovingBitmap mine11[10];			//鑽石
		CMovingBitmap mine12[2];			//道具袋
		CMovingBitmap mine13[10];			//骷顱頭
		CMovingBitmap mine14[2];			//石頭(中)

		CMovingBitmap timer_bling;
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


		//CAudio goal_audio;
		void show_image_by_phase();
		void shoot_claw_by_angle();
		void pull_claw();
		void reset_claw();
		void throw_bomb();
		void reset_bomb();
		void gameover_and_restart();
		void show_text_by_phase();
		void show_text_of_goals();
		void set_goal_money();
		void goto_next_stage();
		void reset_mines();
		void show_items();
		void set_stock();
		void load_mines();
		void show_mines();
		
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
