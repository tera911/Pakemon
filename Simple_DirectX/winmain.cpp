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


// �O���[�o���ϐ�:
HINSTANCE hInst;		// ���݂̃C���^�[�t�F�C�X

LPDIRECT3D9			g_pD3D			= NULL; // Direct3D �I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pd3dDevice	= NULL; // Device�I�u�W�F�N�g�i�`��ɕK�v�ƂȂ�j

int					TimerID;				// �}���`���f�B�A�^�C�}�[�̂h�c
int					Timer16ms;				// �^�C�}�[���P�U�����o�߂������Ƃ�m�点��ϐ�

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT				InitD3D( HWND );
void				Render(void);
void				Cleanup(void);
void	CALLBACK	TimerProc(UINT uID, UINT uMsg, DWORD dwUser,DWORD dw1, DWORD dw2);	// (�^�C�}�[ID, �\��, ���[�U�[��`, �\��, �\��)


LPD3DXFONT g_pFont = NULL; //����

//FPS ����
static DWORD backTickCount, nowTickCount; //���Ԑ���p
int fps = 0;

//�v���g�^�C�v�錾
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
int getMap(char map[46][18]);
void drawFPS();
void setFPS();


// ���_�t�H�[�}�b�g
#define	FVF_TLVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1)

typedef struct _tlvertex{	// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
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
�v���C���[�̃N���X
Nyancat���\�������
*/
class Nyancat{
public:
	Nyancat(LPDIRECT3DDEVICE9 g_pd3dDev, int x, int y){
		D3DXCreateTextureFromFileA(g_pd3dDev, "Nyan_s.png",&nyan);
		nyan_x = x;
		nyan_y = y;
		jump = false;
		vertex[0].rhw = vertex[1].rhw = vertex[2].rhw = vertex[3].rhw = 1.0f;
		vertex[0].diffuse = D3DCOLOR_RGBA(255,255,255,255); //�e���_�i����j�̐F
		vertex[1].diffuse = D3DCOLOR_RGBA(255,255,255,255); //�e���_�i�E��j�̐F
		vertex[2].diffuse = D3DCOLOR_RGBA(255,255,255,255); 
		vertex[3].diffuse = D3DCOLOR_RGBA(255,255,255,255); 
		vertex[0].specular = vertex[1].specular = vertex[2].specular = vertex[3].specular = D3DCOLOR_XRGB(0,0,0); //Specular �X�|�b�g���C�g

		vertex[0].tu = 0.0f;		vertex[0].tv = 0.0f;
		vertex[1].tu = 0.167f;		vertex[1].tv = 0.0f;
		vertex[2].tu = 0.0f;		vertex[2].tv = 1.0f;
		vertex[3].tu = 0.167f;		vertex[3].tv = 1.0f;
	}

	void render(LPDIRECT3DDEVICE9 g_pd3dDev){
		g_pd3dDev->SetFVF(FVF_TLVERTEX);
		g_pd3dDev->SetTexture(0,nyan);

		vertex[0].x = 0.0f  + nyan_x;		vertex[0].y = 0.0f  + nyan_y;	vertex[0].z = 0.0f;		// �P���_�̃X�N���[�����W
		vertex[1].x = 32.0f + nyan_x;		vertex[1].y = 0.0f  + nyan_y;	vertex[1].z = 0.0f;		// �Q���_�̃X�N���[�����W
		vertex[2].x = 0.0f  + nyan_x;		vertex[2].y = 32.0f + nyan_y;	vertex[2].z = 0.0f;		// �R���_�̃X�N���[�����W
		vertex[3].x = 32.0f + nyan_x;		vertex[3].y = 32.0f + nyan_y;	vertex[3].z = 0.0f;
		
		//�v���C���[�̕`��
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
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	
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
	
	RegisterClassEx(&wcex);		// �E�B���h�E�N���X�̓o�^
	hWnd = CreateWindow(	"AppClass",
							"javac Oic2c",
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,		// �E�B���h�E�̍����W
							CW_USEDEFAULT,		// �E�B���h�E�̏���W
							800+GetSystemMetrics(SM_CXDLGFRAME)*2,									// �E�B���h�E����
							600+GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
							NULL,
							NULL,
							hInstance,
							NULL);
	
	if( FAILED( InitD3D( hWnd ) ) )		return -1;	// D3D�̏������̓E�B���h�E���쐬���Ă���s��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);			// InitD3D�̌�ɌĂ΂Ȃ��Ƒʖ�
	
	timeBeginPeriod(1);			// �}���`���f�B�A�^�C�}�[�̕���\�� 1ms �ɐݒ�
	TimerID = timeSetEvent(16, 1, TimerProc, 0, TIME_PERIODIC);	// 16ms(1/60s) ���� TimerFunc ���Ăяo���B
	if( !TimerID )	return -1;	// �^�C�}�[�������Ȃ���΃Q�[���𓮂����Ȃ��̂ŁA�G���[�I�����܂��B
	
	backTickCount = 0; //FPS����̏����ݒ�
	//�p�P�b�g���[�h
	

	ZeroMemory( &msg, sizeof(msg) );	// MSG �\���̂����������܂�
	while( msg.message!=WM_QUIT ){
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ){
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		Render();
	}
	
	timeKillEvent(TimerID);		// �}���`���f�B�A�^�C�}�[�ɃZ�b�g���Ă�����������������B
	timeEndPeriod(1);			// �ȑO�ɃZ�b�g�����^�C�}�[�̍ŏ�����\�����ɖ߂��BtimeBeginPeriod�Ƒ΂ɂȂ��Ă��邱�ƁI
	Cleanup();
	UnregisterClass( "AppClass", wcex.hInstance );	// �E�B���h�E�N���X�̓o�^������
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


LPDIRECT3DTEXTURE9	sys_tex;		// �A�X�L�[�t�H���g�ǂݍ��ݏꏊ


HRESULT InitD3D( HWND hWnd )
{
	D3DPRESENT_PARAMETERS	d3dpp;
	
	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )	return E_FAIL;	// Direct3D�I�u�W�F�N�g�̍쐬
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed					= TRUE;						// �E�B���h�E���[�h
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.EnableAutoDepthStencil	= TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	
	if( FAILED( g_pD3D->CreateDevice(	D3DADAPTER_DEFAULT,						// �v���C�}���A�_�v�^��I��
										D3DDEVTYPE_HAL,							// �n�[�h�E�F�A�ɂ��`�揈����I��
										hWnd,									// �E�B���h�E�n���h��
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// �\�t�g�E�F�A�ɂ�钸�_�v�Z��I��
										&d3dpp,									// D3D object
										&g_pd3dDevice ) ) )		return E_FAIL;	// ��������΃f�o�C�X���쐬�����
	
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );					// Z�o�b�t�@���g�p
	g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );			// ���u�����h���s��
	g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );		// ���\�[�X�J���[�̎w��
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );	// ���f�X�e�B�l�[�V�����J���[�̎w��
	g_pd3dDevice->LightEnable( 0, FALSE );									// DirectX�ɂ�郉�C�g�v�Z�͍s��Ȃ�
	
	D3DXCreateTextureFromFileA(	g_pd3dDevice,
								"sysfont.tga",		// .tga�t�@�C���̖��O
								&(sys_tex)	);		// �ǂݍ��ރ������[
	nyan1 = new Nyancat(g_pd3dDevice,10,30);		//�v���C���[ Nyancat����
	gameMap = new GameMap(g_pd3dDevice);
	getMap(gameMap->map);
	//Font�e�X�g
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
		Timer16ms = 0;		// ���̃^�C�~���O�܂�
		setFPS();
	
		// �`��f�[�^�̏��� E

		// ���o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
		g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
		if( SUCCEEDED( g_pd3dDevice->BeginScene() ) ){		// Direct3D�ɂ��`��̊J�n
			
			g_pFont->DrawTextA(NULL, "Linux",-1, &rc, NULL, 0xFF88FF88); //�����̕\���e�X�g
			nyan1->render(g_pd3dDevice);	//�v���C���[�̕`��

			gameMap->render(g_pd3dDevice); //�}�b�v�̕`��

			drawFPS();

			g_pd3dDevice->EndScene();						// Direct3D�ɂ��`��̏I��
		}
		g_pd3dDevice->Present( NULL, NULL, NULL, NULL );	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�

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
	Timer16ms = 1;		// 16ms�o�߂������Ƃ������t���O
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


	packet.addPacket(ih);//�p�P�b�g��ۑ�

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
	g_pFont->DrawTextA(NULL, text ,-1, &rc, NULL, 0xFF88FF88); //�����̕\���e�X�g
	g_pFont->Release();
}