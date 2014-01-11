// ここにサンプルプログラムをペーストしてください
// 初期状態では LoadGraphScreen のサンプルプログラムが入力されています。
#define WIN32
#define WPCAP
#define HAVE_REMOTE


#include <WinSock2.h>
#include "Nyancat.h"
#include <DxLib.h>
#include "Fps.h"
#include <stdlib.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Packet.lib")
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "ws2_32.lib")

#define SCREEN_WIDTH	(800)	//スクリーンの横幅
#define SCREEN_HEIGHT	(600)	//スクリーンの縦幅
#define CHIP_SIZE		(32)	//一つのチップのサイズ
#define MAP_WIDTH		(46)
#define	MAP_HEIGHT		(18)



////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////


int WINAPI Game( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				 LPSTR lpCmdLine, int nCmdShow ){



	SetGraphMode(800, 600, 32, 60);
	ChangeWindowMode(true);
	SetMainWindowText("Pakemon");
	if( DxLib_Init() == -1 )	// ＤＸライブラリ初期化処理
	{
		 return -1;				// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面にする
	SetBackgroundColor(15,77,143);
	Nyancat player;
	Fps fpsCounter;

	//ClearDrawScreen();	//画面に描かれているものを全部消す
	//ScreenFlip();			//裏画面の内容を表画面に反映させる
	int start_time=GetNowCount();
	while(ProcessMessage()==0 && ClearDrawScreen()==0){
		fpsCounter.Update();
		DrawFormatString(500,0,GetColor(255,255,255),"%d",((GetNowCount()- start_time))/1000); 
		
		
		/////////////////////////////////////////////////////////////////
		//							描画開始						   //
		/////////////////////////////////////////////////////////////////
		
		fpsCounter.Draw();
		// ＢＭＰ画像の表示
		
		player.render();
		/////////////////////////////////////////////////////////////////
		//							描画おしり						   //
		//							キー入力待ち開始				   //
		/////////////////////////////////////////////////////////////////
		


		if(CheckHitKey(KEY_INPUT_LEFT) > 0){
			player.moveLeft();
		}
		if(CheckHitKey(KEY_INPUT_RIGHT) > 0){
			player.moveRight();
		}
		if(CheckHitKey(KEY_INPUT_DOWN) > 0){
			player.moveDown();
		}

		if(CheckHitKey(KEY_INPUT_C) > 0){
			player.jump();
		}
		if(CheckHitKey(KEY_INPUT_R) > 0){
			player.reset();
		}
		/////////////////////////////////////////////////////////////////
		//							キー入力待ちおしり				   //
		/////////////////////////////////////////////////////////////////
		ScreenFlip();
		//fpsCounter.Wait();		//待機
		//Sleep(300);
		//Windows コールバックを処理する
		if(ProcessMessage() == -1) break; //異常が発生したらループから抜ける
		if(CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;//エスケープキーが押されたらループから抜ける
		if( GetNowCount()-start_time>=1200000 ) break;//60秒経過したらループから抜ける
	
	}
	DxLib_End() ;	// ＤＸライブラリ使用の終了処理
	//WaitKey() ;					// キーの入力待ち((7-3)『WaitKey』を使用)
		
	return 0 ;	
					// ソフトの終了
}


/*
ﾎｳｾｲ...ﾏｲ、ﾌﾚﾝﾄﾞ...
http://www.nicovideo.jp/watch/sm22587419
*/