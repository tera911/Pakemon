// ここにサンプルプログラムをペーストしてください
// 初期状態では ﾎｳｾｲ...ﾏｲ.....ﾌﾚ..ﾝ.ﾄﾞ....... のサンプルプログラムが入力されています。
#define WIN32
#define WPCAP
#define HAVE_REMOTE


#include <WinSock2.h>
#include "Nyancat.h"
#include <DxLib.h>
#include "Fps.h"
#include <stdlib.h>
#include "ParentWindow.h"
#include "TitleWindow.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Packet.lib")
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "ws2_32.lib")

#define CHIP_SIZE		(32)	//一つのチップのサイズ



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				LPSTR lpCmdLine, int nCmdShow ){
	SetGraphMode(800, 600, 32, 60);	//
	ChangeWindowMode(true);			//ウウィンドウモード
	SetMainWindowText("Pakemon");	//タイトル？
	if( DxLib_Init() == -1 ){	// ＤＸライブラリ初期化処理
		 return -1;				// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);	//ダブルスバッファリングの設定
	SetBackgroundColor(15,77,143);	//Nyancatの世界観を感じさせるWindowsチックな背景色
	Fps fpsCounter;
	ParentWindow window;
	
	while(ProcessMessage()==0 && ClearDrawScreen()==0){
		fpsCounter.Update();
		/////////////////////////////////////////////////////////////////
		//							描画開始						   //
		/////////////////////////////////////////////////////////////////
		
		fpsCounter.Draw();
		// ＢＭＰ画像の表示
		
		if(window.update()){
			break;
		}
		/////////////////////////////////////////////////////////////////
		//							描画おしり						   //
		//							キー入力待ち開始				   //
		/////////////////////////////////////////////////////////////////
		ScreenFlip();	//ダブルバッファ（裏画面を表示）
		if(ProcessMessage() == -1) break; //異常が発生したらループから抜ける
		if(CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;//エスケープキーが押されたらループから抜ける
	}
	DxLib_End() ;	// ＤＸライブラリ使用の終了処理
	return 0;
}

/*
ﾎｳｾｲ...ﾏｲ、ﾌﾚﾝﾄﾞ...
http://www.nicovideo.jp/watch/sm22587419
*/