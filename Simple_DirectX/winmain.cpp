#define WIN32
#define WPCAP
#define HAVE_REMOTE

#pragma comment(lib, "Packet.lib")
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <pcap.h>
#include <WinSock2.h>
#include "headall.h"
#include "GameMap.h"
#include "packet/Map.h"

#define LINE_LEN 16
#define PACKET_FILE "icmpPacket.pcap"


// グローバル変数:
HINSTANCE hInst;		// 現在のインターフェイス

LPDIRECT3D9			g_pD3D			= NULL; // Direct3D オブジェクト
LPDIRECT3DDEVICE9	g_pd3dDevice	= NULL; // Deviceオブジェクト（描画に必要となる）

int					TimerID;				// マルチメディアタイマーのＩＤ
int					Timer16ms;				// タイマーが１６ｍｓ経過したことを知らせる変数

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT				InitD3D( HWND );
void				Render(void);
void				Cleanup(void);
void	CALLBACK	TimerProc(UINT uID, UINT uMsg, DWORD dwUser,DWORD dw1, DWORD dw2);	// (タイマーID, 予約, ユーザー定義, 予約, 予約)


LPD3DXFONT g_pFont = NULL; //文字

//FPS 測定
static DWORD backTickCount, nowTickCount; //時間制御用
int fps = 0;

//プロトタイプ宣言
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
int getMap(char map[46][18]);
void drawFPS();
void setFPS();


// 頂点フォーマット
#define	FVF_TLVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1)

typedef struct _tlvertex{	// 上記頂点フォーマットに合わせた構造体を定義
	float x,y,z;
	float rhw;
	D3DCOLOR diffuse;
	D3DCOLOR specular;
	float tu,tv;
}TLVERTEX;

class PacketCapcure{
private:
	struct ip_header icmpPacket[1020];
public:
	int addPacket(ip_header * packet){
		static int i = 0;
		if(i < 1000){
			memcpy(&icmpPacket[i],packet,sizeof(ip_header));
			i++;
			return 0;
		}else{
			return -1;
		}
	};
	ip_header* getPacket(){
		return &icmpPacket[200];
	};
};

/**
プレイヤーのクラス
Nyancatが表示される
*/
class Nyancat{
public:
	Nyancat(LPDIRECT3DDEVICE9 g_pd3dDev, int x, int y){
		D3DXCreateTextureFromFileA(g_pd3dDev, "Nyan_s.png",&nyan);
		nyan_x = x;
		nyan_y = y;
		jump = false;
		vertex[0].rhw = vertex[1].rhw = vertex[2].rhw = vertex[3].rhw = 1.0f;
		vertex[0].diffuse = D3DCOLOR_RGBA(255,255,255,255); //各頂点（左上）の色
		vertex[1].diffuse = D3DCOLOR_RGBA(255,255,255,255); //各頂点（右上）の色
		vertex[2].diffuse = D3DCOLOR_RGBA(255,255,255,255); 
		vertex[3].diffuse = D3DCOLOR_RGBA(255,255,255,255); 
		vertex[0].specular = vertex[1].specular = vertex[2].specular = vertex[3].specular = D3DCOLOR_XRGB(0,0,0); //Specular スポットライト

		vertex[0].tu = 0.0f;		vertex[0].tv = 0.0f;
		vertex[1].tu = 0.167f;		vertex[1].tv = 0.0f;
		vertex[2].tu = 0.0f;		vertex[2].tv = 1.0f;
		vertex[3].tu = 0.167f;		vertex[3].tv = 1.0f;
	}

	void render(LPDIRECT3DDEVICE9 g_pd3dDev){
		g_pd3dDev->SetFVF(FVF_TLVERTEX);
		g_pd3dDev->SetTexture(0,nyan);

		vertex[0].x = 0.0f  + nyan_x;		vertex[0].y = 0.0f  + nyan_y;	vertex[0].z = 0.0f;		// １頂点のスクリーン座標
		vertex[1].x = 32.0f + nyan_x;		vertex[1].y = 0.0f  + nyan_y;	vertex[1].z = 0.0f;		// ２頂点のスクリーン座標
		vertex[2].x = 0.0f  + nyan_x;		vertex[2].y = 32.0f + nyan_y;	vertex[2].z = 0.0f;		// ３頂点のスクリーン座標
		vertex[3].x = 32.0f + nyan_x;		vertex[3].y = 32.0f + nyan_y;	vertex[3].z = 0.0f;
		
		//プレイヤーの描画
		g_pd3dDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,vertex, sizeof(TLVERTEX));

		grabity();
	}
	void moveUp(){
		jump = true;
	}
	void moveDown(){
		nyan_y = nyan_y +  7;
	}
	void moveLeft(){
		nyan_x = nyan_x -  5;
	}
	void moveRight(){
		nyan_x = nyan_x +  5;
	}
	void grabity(){
		if(jump){
			nyan_y -= 40.0f;
			jump=false;
		}else if(nyan_y < 450){
			nyan_y += 5.5f;
		}
	}
private:
	LPDIRECT3DTEXTURE9 nyan;
	float nyan_x;
	float nyan_y;
	bool jump;
	TLVERTEX vertex[4];
};


PacketCapcure packet;
Nyancat * nyan1;
GameMap * gameMap;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）
	
	WNDCLASSEX	wcex = {	sizeof(WNDCLASSEX),
							CS_CLASSDC,
							WndProc,
							0,
							0,
							hInstance,
							NULL,
							LoadCursor(NULL, IDC_ARROW),
							(HBRUSH)(COLOR_WINDOW+1),
							NULL,
							"AppClass",
							NULL	};
	HWND		hWnd;
	MSG			msg;
	
	RegisterClassEx(&wcex);		// ウィンドウクラスの登録
	hWnd = CreateWindow(	"AppClass",
							"javac Oic2c",
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,		// ウィンドウの左座標
							CW_USEDEFAULT,		// ウィンドウの上座標
							800+GetSystemMetrics(SM_CXDLGFRAME)*2,									// ウィンドウ横幅
							600+GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
							NULL,
							NULL,
							hInstance,
							NULL);
	
	if( FAILED( InitD3D( hWnd ) ) )		return -1;	// D3Dの初期化はウィンドウを作成してから行う
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);			// InitD3Dの後に呼ばないと駄目
	
	timeBeginPeriod(1);			// マルチメディアタイマーの分解能を 1ms に設定
	TimerID = timeSetEvent(16, 1, TimerProc, 0, TIME_PERIODIC);	// 16ms(1/60s) 毎に TimerFunc を呼び出す。
	if( !TimerID )	return -1;	// タイマーが働かなければゲームを動かせないので、エラー終了します。
	
	backTickCount = 0; //FPS測定の初期設定
	//パケットロード
	

	ZeroMemory( &msg, sizeof(msg) );	// MSG 構造体を初期化します
	while( msg.message!=WM_QUIT ){
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ){
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		Render();
	}
	
	timeKillEvent(TimerID);		// マルチメディアタイマーにセットしていた処理を解除する。
	timeEndPeriod(1);			// 以前にセットしたタイマーの最小分解能を元に戻す。timeBeginPeriodと対になっていること！
	Cleanup();
	UnregisterClass( "AppClass", wcex.hInstance );	// ウィンドウクラスの登録を解除
	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message ){
	case WM_PAINT:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch(wParam){
			case 67:
				nyan1->moveUp();
			break;
			case VK_DOWN:
				nyan1->moveDown();
			break;
			case VK_RIGHT:
				nyan1->moveRight();
				gameMap->screenScroll_x(2);
			break;
			case VK_LEFT:
				nyan1->moveLeft();
			break;
		}
		break;
	case WM_KEYUP:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


LPDIRECT3DTEXTURE9	sys_tex;		// アスキーフォント読み込み場所


HRESULT InitD3D( HWND hWnd )
{
	D3DPRESENT_PARAMETERS	d3dpp;
	
	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )	return E_FAIL;	// Direct3Dオブジェクトの作成
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed					= TRUE;						// ウィンドウモード
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.EnableAutoDepthStencil	= TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// デプスバッファとして16bitを使う
	
	if( FAILED( g_pD3D->CreateDevice(	D3DADAPTER_DEFAULT,						// プライマリアダプタを選択
										D3DDEVTYPE_HAL,							// ハードウェアによる描画処理を選択
										hWnd,									// ウィンドウハンドル
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// ソフトウェアによる頂点計算を選択
										&d3dpp,									// D3D object
										&g_pd3dDevice ) ) )		return E_FAIL;	// 成功すればデバイスが作成される
	
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );					// Zバッファを使用
	g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );			// αブレンドを行う
	g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );		// αソースカラーの指定
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );	// αデスティネーションカラーの指定
	g_pd3dDevice->LightEnable( 0, FALSE );									// DirectXによるライト計算は行わない
	
	D3DXCreateTextureFromFileA(	g_pd3dDevice,
								"sysfont.tga",		// .tgaファイルの名前
								&(sys_tex)	);		// 読み込むメモリー
	nyan1 = new Nyancat(g_pd3dDevice,10,30);		//プレイヤー Nyancat生成
	gameMap = new GameMap(g_pd3dDevice);
	getMap(gameMap->map);
	//Fontテスト
	D3DXCreateFont(g_pd3dDevice,
			50,
			50,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			"Linux",
			&g_pFont);
	return S_OK;
}





RECT rc = {0, 0, 800, 600};
void Render(void){
	if( Timer16ms ){
		Timer16ms = 0;		// 次のタイミングまで
		setFPS();
	
		// 描画データの準備 E

		// ↓バックバッファ＆Ｚバッファのクリア
		g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
		if( SUCCEEDED( g_pd3dDevice->BeginScene() ) ){		// Direct3Dによる描画の開始
			
			g_pFont->DrawTextA(NULL, "Linux",-1, &rc, NULL, 0xFF88FF88); //文字の表示テスト
			nyan1->render(g_pd3dDevice);	//プレイヤーの描画

			gameMap->render(g_pd3dDevice); //マップの描画

			drawFPS();

			g_pd3dDevice->EndScene();						// Direct3Dによる描画の終了
		}
		g_pd3dDevice->Present( NULL, NULL, NULL, NULL );	// バックバッファとフロントバッファの入れ替え

	}
}



void Cleanup(void)
{
	if( sys_tex )				sys_tex->Release();
	if( g_pd3dDevice != NULL )	g_pd3dDevice->Release();
	if( g_pD3D != NULL )		g_pD3D->Release();
}

void CALLBACK TimerProc(UINT uID, UINT uMsg, DWORD dwUser,DWORD dw1, DWORD dw2)
{
	Timer16ms = 1;		// 16ms経過したことを示すフラグ
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

void setFPS(){
	static int nowfps = 0;
	nowTickCount = timeGetTime();
	nowfps++;
	if(nowTickCount - backTickCount >= 1000){
		backTickCount = nowTickCount;
		fps = nowfps;
		nowfps = 0;
	}
}
void drawFPS(){
	static char text[40];
	RECT rc;
	rc.left =	200;
	rc.top	=	100;
	rc.right= 800;
	rc.bottom= 600;
	static LPD3DXFONT g_pFont;
	D3DXCreateFont(g_pd3dDevice,
			32,
			32,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			"Linux",
			&g_pFont);
	wsprintf(text, "%04d FPS\n", fps);
	OutputDebugString(text);
	g_pFont->DrawTextA(NULL, text ,-1, &rc, NULL, 0xFF88FF88); //文字の表示テスト
	g_pFont->Release();
}