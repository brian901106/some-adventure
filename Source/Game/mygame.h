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
		int angles[72] = { 70, 70, 69, 68, 66, 64, 62, 59, 55, 51, 47, 42, 37, 32, 27, 21, 15, 9, 3, -2, -8, -15, -20, -26, -32, -37, -42, -46, -50, -54, -57, -60, -63, -65, -67, -68, -68, -68, -68, -67, -66, -65, -63, -60, -57, -53, -50, -45, -40, -35, -29, -24, -18, -12, -6, 0, 5, 11, 17, 23, 29, 34, 39, 44, 49, 53, 57, 60, 63, 65, 67, 69 };
		int claw_x = 507;				//紀錄爪子的Left
		int claw_y = 90;				//紀錄爪子的Top
		int bomb_x = 507;
		int bomb_y = 90;
		int claw_xway[90];				//紀錄爪子shoot出去時，每桢所在的Left，回程收爪時可以call出來
		int claw_yway[90];				//紀錄爪子shoot出去時，每桢所在的Top，回程收爪時可以call出來
		int claw_length = 0;			//紀錄爪子目前長度
		bool hit = false;				//爪子是否有抓到東西
		bool miss = false;				//爪子是否空抓
		int weight = 1;					//用來表示抓到礦的重量，越重爪子速度越慢 ,預設為1
		int weight_of_mine[13] = { 50,100,150,300,50,50,300,0,80,50,50,50,100};
		int money_gain = 0;				//用來表示現在抓到的金礦的價值
		int money_of_mine[13] = { 50,100,250,500,2,7,20,1,602,600,-1,20,11 };
		//金礦(小)/金礦(中)/金礦(大)/金礦(巨大)/豬/骨頭/石頭(大)/爆炸桶/鑽石豬/鑽石/道具袋/骷顱頭/石頭(中)
		//道具袋價值為-1，因此在pull_claw()會進入其他運算，以計算價值

		/*這些參數是用來控制獲得金錢的文字*/
		bool money_gain_flag = false;			//當flag==true顯示money_gain_text
		int last_time_money_gain;				//紀錄上次顯示money_gain_text的時間
		int timer_of_money_gain_text = 50;		//顯示money_gain_text的時間長短
		int font[3];							//x,y,size
		int new_money = 0;						//顯示的金錢
		int money = 0;							//實際的金錢
		int goal_money = 650;					//過關要求
		
		/*這三個參數是用來控制炸藥飛出去的時間位置和炸藥數量*/
		int last_time_bomb;						//紀錄上次bomb更新的時間
		int bomb_num = 2;						//bomb數量
		bool bomb_is_throw = false;				//當flag==true時丟炸藥

		/*這幾個參數是用來控制goal page的淡出效果*/
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
		int item_price[5] = { 241, 0, 48, 45, 290 };
		int item_mouse_on = -1;
		bool next_level_button_clicked = false;
		bool return_game = false;
		int item_in_stock_in_level[5] = { 0, 0, 0 ,0, 0 };

		bool item_2_effect = false;			//力量藥水
		bool item_3_effect = false;			//幸運草	道具袋掉更好
		bool item_4_effect = false;			//石頭書	石頭3倍價值
		bool item_5_effect = false;			//鑽石打磨 鑽石*1.5價值


		int mine_max_num[13] = { 10,10,10,10,10,10,10,10,10,10,10,10,10 };	
		//各種礦在遊戲中的最大值(用來控制loadbitmap數量)
		//記得一開始宣告的數量也要一併更動

		//每關的礦數量
		//金礦(小)/金礦(中)/金礦(大)/金礦(巨大)/豬/骨頭/石頭(大)/爆炸桶/鑽石豬/鑽石/道具袋/骷顱頭/石頭(中)
		int mine_num_now[13] = { 4,3,0,2,0,0,2,1,0,0,2,0,2 };			//目前關卡讀取哪行參數
		int mine_num_1[10][13] = {  { 4,3,0,2,0,0,2,3,0,0,2,0,2 },		//第1關
									{ 7,2,0,2,0,0,4,1,0,1,1,0,3 },		//第2關
									{ 4,3,0,1,0,0,4,0,0,1,1,0,3 },		//第3關
									{ 4,1,2,0,1,0,3,0,0,0,4,0,1 },		//第4關
									{ 4,3,1,2,3,0,3,0,0,4,1,0,1 },		//第5關
									{ 7,3,0,1,0,0,3,0,2,0,1,0,3 },		//第6關
									{ 2,0,2,3,6,2,0,2,0,0,1,2,0 },		//第7關
									{ 0,0,0,0,0,0,0,5,3,8,2,0,0 },		//第8關
									{ 1,0,0,2,0,1,0,7,4,7,3,1,0 },		//第9關
									{ 6,5,5,5,0,0,5,0,0,0,0,0,0 } };	//第10關

		int exist2[10], exist3[10], exist4[10], exist5[10], exist6[10], exist7[10], exist8[10], exist9[10], exist10[10], exist11[10], exist12[10], exist13[10], exist14[10];
		


		bool gameover = false;			// = true 時播放結束動畫並返回主頁面

		CMovingBitmap goal;
		CMovingBitmap background;
	
		CMovingBitmap miner;
		CMovingBitmap miner_t;
		CMovingBitmap miner_s;
		CMovingBitmap wood;

		CMovingBitmap claw;
		CMovingBitmap clawhead;
		CMovingBitmap line[90];
		CMovingBitmap hitbox;
		CMovingBitmap bomb;
		CMovingBitmap number_of_bombs;

		CMovingBitmap mine2[10];			//金礦(小)
		CMovingBitmap mine3[10];			//金礦(中)
		CMovingBitmap mine4[10];			//金礦(大)
		CMovingBitmap mine5[10];			//金礦(巨大)
		CMovingBitmap mine6[10];			//豬
		CMovingBitmap mine7[10];			//骨頭
		CMovingBitmap mine8[10];			//石頭(大)
		CMovingBitmap mine9[10];			//爆炸桶
		CMovingBitmap mine10[10];			//鑽石豬
		CMovingBitmap mine11[10];			//鑽石
		CMovingBitmap mine12[10];			//道具袋
		CMovingBitmap mine13[10];			//骷顱頭
		CMovingBitmap mine14[10];			//石頭(中)
		CMovingBitmap explosion[10];

		

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
		void show_line();
		void throw_bomb();
		void reset_bomb();
		void set_location_of_explosion(int index, int left, int top);
		void gameover_and_restart();
		void show_text_by_phase();
		void show_text_of_goals();
		void show_text_of_money_gain();
		void set_goal_money();
		void goto_next_stage();
		void set_mines();
		void set_item_price();
		void show_items();
		void show_description_of_item();
		void set_stock();
		void load_mines();
		void show_mines();
		bool is_blew_up(int mine, int index);


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
