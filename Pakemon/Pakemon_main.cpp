// �����ɃT���v���v���O�������y�[�X�g���Ă�������
// ������Ԃł� γ��...ϲ.....��..�.��....... �̃T���v���v���O���������͂���Ă��܂��B
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

#define CHIP_SIZE		(32)	//��̃`�b�v�̃T�C�Y



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				LPSTR lpCmdLine, int nCmdShow ){
	SetGraphMode(800, 600, 32, 60);	//
	ChangeWindowMode(true);			//�E�E�B���h�E���[�h
	SetMainWindowText("Pakemon");	//�^�C�g���H
	if( DxLib_Init() == -1 ){	// �c�w���C�u��������������
		 return -1;				// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);	//�_�u���X�o�b�t�@�����O�̐ݒ�
	SetBackgroundColor(15,77,143);	//Nyancat�̐��E�ς�����������Windows�`�b�N�Ȕw�i�F
	Fps fpsCounter;
	ParentWindow window;
	
	while(ProcessMessage()==0 && ClearDrawScreen()==0){
		fpsCounter.Update();
		/////////////////////////////////////////////////////////////////
		//							�`��J�n						   //
		/////////////////////////////////////////////////////////////////
		
		fpsCounter.Draw();
		// �a�l�o�摜�̕\��
		
		if(window.update()){
			break;
		}
		/////////////////////////////////////////////////////////////////
		//							�`�您����						   //
		//							�L�[���͑҂��J�n				   //
		/////////////////////////////////////////////////////////////////
		ScreenFlip();	//�_�u���o�b�t�@�i����ʂ�\���j
		if(ProcessMessage() == -1) break; //�ُ킪���������烋�[�v���甲����
		if(CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;//�G�X�P�[�v�L�[�������ꂽ�烋�[�v���甲����
	}
	DxLib_End() ;	// �c�w���C�u�����g�p�̏I������
	return 0;
}

/*
γ��...ϲ�A�����...
http://www.nicovideo.jp/watch/sm22587419
*/