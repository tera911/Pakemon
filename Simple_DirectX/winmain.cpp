#include "headall.h"

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


// ���_�t�H�[�}�b�g
#define	FVF_TLVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1)

typedef struct _tlvertex{	// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
	float x,y,z;
	float rhw;
	D3DCOLOR diffuse;
	D3DCOLOR specular;
	float tu,tv;
}TLVERTEX;

class Nyancat{
public:
	Nyancat(LPDIRECT3DDEVICE9 g_pd3dDev, int x, int y){
		D3DXCreateTextureFromFileA(g_pd3dDev, "Nyan_s.png",&nyan);
		nyan_x = x;
		nyan_y = y;
		jump = false;
	}
	void render(LPDIRECT3DDEVICE9 g_pd3dDev){
		TLVERTEX vertex[4];
		
		g_pd3dDev->SetFVF(FVF_TLVERTEX);
		g_pd3dDev->SetTexture(0,nyan);
		vertex[0].rhw = vertex[1].rhw = vertex[2].rhw = vertex[3].rhw = 1.0f;
		vertex[0].diffuse = D3DCOLOR_RGBA(255,255,255,255); //�e���_�i����j�̐F
		vertex[1].diffuse = D3DCOLOR_RGBA(255,255,255,255); //�e���_�i�E��j�̐F
		vertex[2].diffuse = D3DCOLOR_RGBA(255,255,255,255); 
		vertex[3].diffuse = D3DCOLOR_RGBA(255,255,255,255); 
		vertex[0].specular = vertex[1].specular = vertex[2].specular = vertex[3].specular = D3DCOLOR_XRGB(0,0,0); //Specular �X�|�b�g���C�g

		vertex[0].x = 0.0f  + nyan_x;		vertex[0].y = 0.0f  + nyan_y;	vertex[0].z = 0.0f;		// �P���_�̃X�N���[�����W
		vertex[1].x = 32.0f + nyan_x;		vertex[1].y = 0.0f  + nyan_y;	vertex[1].z = 0.0f;		// �Q���_�̃X�N���[�����W
		vertex[2].x = 0.0f  + nyan_x;		vertex[2].y = 32.0f + nyan_y;	vertex[2].z = 0.0f;		// �R���_�̃X�N���[�����W
		vertex[3].x = 32.0f + nyan_x;		vertex[3].y = 32.0f + nyan_y;	vertex[3].z = 0.0f;
		
		vertex[0].tu = 0.0f;		vertex[0].tv = 0.0f;
		vertex[1].tu = 0.167f;		vertex[1].tv = 0.0f;
		vertex[2].tu = 0.0f;		vertex[2].tv = 1.0f;
		vertex[3].tu = 0.167f;		vertex[3].tv = 1.0f;

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
			nyan_y -= 20.0f;
		}else if(nyan_y < 450){
			nyan_y += 5.5f;
		}
	}
private:
	LPDIRECT3DTEXTURE9 nyan;
	float nyan_x;
	float nyan_y;
	bool jump;
};

Nyancat * nyan1;

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
							"DirectX",
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
			break;
			case VK_LEFT:
				nyan1->moveLeft();
			break;
		}
		break;
	case WM_KEYUP:
		switch(wParam){
		case 67:
			
		break;
		}
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
	
	return S_OK;
}




float	g_radian;	// ���_�̉�]�v�Z�̂��߂̊p�x�J�E���^�i�O�ɏ���������邱�Ƃ����҂��Ă��܂��j
LPD3DXFONT g_pFont = NULL;
RECT rc;
void Render(void)
{
	TLVERTEX	vertex[4];	// �����`�ɂȂ�悤�ɂS�_���t�@���ŕ`�悵�܂�
	float		x[4] = {-100.0f, 100.0f, 100.0f, -100.0f};	// ���_�̉�]�v�Z�̂��߂̃��[�N
	float		y[4] = {-100.0f, -100.0f, 100.0f, 100.0f};	// ���_���S�ɎO�p�`��p�ӂ��Ă��܂��i�`�͓K���A�A�j
	
	if( Timer16ms ){
		Timer16ms = 0;		// ���̃^�C�~���O�܂�
		
		// �`��f�[�^�̏��� S
		g_radian += 1.0f / 180.0f * 3.1415926535f;
		if( g_radian > (2.0f * 3.1415926535f) )		g_radian = 0.0f;
		
		vertex[0].x = x[0] * cos(g_radian) - y[0] * sin(g_radian)  +  320.0f;
		vertex[0].y = x[0] * sin(g_radian) + y[0] * cos(g_radian)  +  240.0f;
		vertex[1].x = x[1] * cos(g_radian) - y[1] * sin(g_radian)  +  320.0f;
		vertex[1].y = x[1] * sin(g_radian) + y[1] * cos(g_radian)  +  240.0f;
		vertex[2].x = x[2] * cos(g_radian) - y[2] * sin(g_radian)  +  320.0f;
		vertex[2].y = x[2] * sin(g_radian) + y[2] * cos(g_radian)  +  240.0f;
		vertex[3].x = x[3] * cos(g_radian) - y[3] * sin(g_radian)  +  320.0f;
		vertex[3].y = x[3] * sin(g_radian) + y[3] * cos(g_radian)  +  240.0f;
		vertex[0].z = vertex[1].z = vertex[2].z = vertex[3].z = 0.0f;
		
		vertex[0].rhw = vertex[1].rhw = vertex[2].rhw = vertex[3].rhw = 1.0f;	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		
		vertex[0].diffuse = D3DCOLOR_RGBA(255,0,0,255);		// �P���_�ڂ̐F
		vertex[1].diffuse = D3DCOLOR_RGBA(0,255,0,255);		// �Q���_�ڂ̐F
		vertex[2].diffuse = D3DCOLOR_RGBA(0,0,255,255); 	// �R���_�ڂ̐F
		vertex[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);	// �S���_�ڂ̐F
		
		vertex[0].specular = vertex[1].specular = vertex[2].specular = vertex[3].specular = D3DCOLOR_XRGB(0,0,0);	// Specular�͉����Ȃ�
		
		vertex[0].tu = 0.0f;	vertex[0].tv = 0.0f;	// �e�N�X�`���[�𒣂�̂ō��W���w��
		vertex[1].tu = 1.0f;	vertex[1].tv = 0.0f;
		vertex[2].tu = 1.0f;	vertex[2].tv = 1.0f;
		vertex[3].tu = 0.0f;	vertex[3].tv = 1.0f;
		// �`��f�[�^�̏��� E
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

		rc.left = 0;
		rc.top	= 0;
		rc.right= 800;
		rc.bottom= 600;
		
		// ���o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
		g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
		if( SUCCEEDED( g_pd3dDevice->BeginScene() ) ){		// Direct3D�ɂ��`��̊J�n
			
			g_pd3dDevice->SetFVF(FVF_TLVERTEX);				// ���_�t�H�[�}�b�g�̐ݒ�
			g_pd3dDevice->SetTexture(0,sys_tex);			// �A�X�L�[�t�H���g���Z�b�g
			
			g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,vertex,sizeof(TLVERTEX));	// �|���S���̕`��i�t�@���ŎO�p�`�Q���j


			
			g_pFont->DrawTextA(NULL, "Linux",-1, &rc, NULL, 0xFF88FF88);
			nyan1->render(g_pd3dDevice);


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
