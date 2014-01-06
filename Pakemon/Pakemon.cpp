// ここにサンプルプログラムをペーストしてください
// 初期状態では LoadGraphScreen のサンプルプログラムが入力されています。
#define WIN32
#define WPCAP
#define HAVE_REMOTE

#include "packet/Map.h"
#include <DxLib.h>
#include <pcap.h>
#include "Nyancat.h"
#include "Fps.h"
#include "packet/PacketICMP.h"
#include "GameMap.h"


#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Packet.lib")
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "ws2_32.lib")

#define SCREEN_WIDTH	(800)	//スクリーンの横幅
#define SCREEN_HEIGHT	(600)	//スクリーンの縦幅
#define CHIP_SIZE		(32)	//一つのチップのサイズ
#define MAP_WIDTH		(46)
#define	MAP_HEIGHT		(18)

#define LINE_LEN 16
#define PACKET_FILE "icmpPacket.pcap"

////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////

PacketICMP packet;
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
int getMap(char map[46][18]);

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				 LPSTR lpCmdLine, int nCmdShow ){


	SetGraphMode(800, 600, 32, 60);
	ChangeWindowMode(true);
	if( DxLib_Init() == -1 )	// ＤＸライブラリ初期化処理
	{
		 return -1;				// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面にする
	SetBackgroundColor(15,77,143);
	Nyancat player;
	Fps fpsCounter;
	GameMap gameMap;
	getMap(gameMap.map);

	//ClearDrawScreen();	//画面に描かれているものを全部消す
	//ScreenFlip();			//裏画面の内容を表画面に反映させる
		
	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0){
		fpsCounter.Update();
		/////////////////////////////////////////////////////////////////
		//							描画開始						   //
		/////////////////////////////////////////////////////////////////
		
		fpsCounter.Draw();
		// ＢＭＰ画像の表示
		
		gameMap.render();
		gameMap.checkMapHit(&player);
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
		/////////////////////////////////////////////////////////////////
		//							キー入力待ちおしり				   //
		/////////////////////////////////////////////////////////////////

		fpsCounter.Wait();		//待機
		//Windows コールバックを処理する
		if(ProcessMessage() == -1) break; //異常が発生したらループから抜ける

		//エスケープキーが押されたらループから抜ける
		if(CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	//WaitKey() ;					// キーの入力待ち((7-3)『WaitKey』を使用)

	DxLib_End() ;				// ＤＸライブラリ使用の終了処理

	return 0 ;					// ソフトの終了
}

int getMap(char map[46][18]){
	pcap_t * fp;
	char errbuf[PCAP_ERRBUF_SIZE];
	Map packetMap;

	if((fp = pcap_open_offline(PACKET_FILE, errbuf)) == NULL){
		return 0;
	}

	pcap_loop(fp, 0, packet_handler, NULL);
	
	
	packetMap.buildMap(packet.getPacket(), 1000);

	for(int y = 0; y < 18; y++){
		for(int x = 0; x < 46; x++){
			map[x][y] = packetMap.map[x][y];
		}
	}

	return 1;
}
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data){
	ip_header *ih;
	tcp_header *th;
	u_int ip_len;
	u_short sport,dport;
	ih = (ip_header *)(pkt_data + 14);
	
	ip_len = (ih->ver_ihl & 0xf) * 4;
	th = (tcp_header *)((u_char *)ih + ip_len);


	packet.addPacket(ih);//パケットを保存

	/*sport = ntohs( th->sport);
	dport = ntohs( th->dport);

	 printf("%d.%d.%d.%d.%d -> %d.%d.%d.%d.%d\n",
        ih->saddr.byte1,
        ih->saddr.byte2,
        ih->saddr.byte3,
        ih->saddr.byte4,
        sport,
        ih->daddr.byte1,
        ih->daddr.byte2,
        ih->daddr.byte3,
        ih->daddr.byte4,
        dport);*/
}

/*
ﾎｳｾｲ...ﾏｲ、ﾌﾚﾝﾄﾞ...
http://www.nicovideo.jp/watch/sm22587419
*/