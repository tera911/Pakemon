// �����ɃT���v���v���O�������y�[�X�g���Ă�������
// ������Ԃł� LoadGraphScreen �̃T���v���v���O���������͂���Ă��܂��B
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

#define SCREEN_WIDTH	(800)	//�X�N���[���̉���
#define SCREEN_HEIGHT	(600)	//�X�N���[���̏c��
#define CHIP_SIZE		(32)	//��̃`�b�v�̃T�C�Y
#define MAP_WIDTH		(46)
#define	MAP_HEIGHT		(18)



////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
////////////////////////////////////////////////////////////////////////


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				 LPSTR lpCmdLine, int nCmdShow ){



	SetGraphMode(800, 600, 32, 60);
	ChangeWindowMode(true);
	SetMainWindowText("Pakemon");
	if( DxLib_Init() == -1 )	// �c�w���C�u��������������
	{
		 return -1;				// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂɂ���
	SetBackgroundColor(15,77,143);
	Nyancat player;
	Fps fpsCounter;

	//ClearDrawScreen();	//��ʂɕ`����Ă�����̂�S������
	//ScreenFlip();			//����ʂ̓��e��\��ʂɔ��f������
	int limittime=60;
	int start_time=GetNowCount();
	char nowtime[256];
	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0){
		fpsCounter.Update();
		limittime-=1;
		itoa(limittime,nowtime,10);
		DrawString(500,0,nowtime,GetColor(255,255,255));
		
		
		/////////////////////////////////////////////////////////////////
		//							�`��J�n						   //
		/////////////////////////////////////////////////////////////////
		
		fpsCounter.Draw();
		// �a�l�o�摜�̕\��
		
		player.render();
		/////////////////////////////////////////////////////////////////
		//							�`�您����						   //
		//							�L�[���͑҂��J�n				   //
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
		//							�L�[���͑҂�������				   //
		/////////////////////////////////////////////////////////////////

		fpsCounter.Wait();		//�ҋ@
		//Sleep(300);
		//Windows �R�[���o�b�N����������
		if(ProcessMessage() == -1) break; //�ُ킪���������烋�[�v���甲����
		if(CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;//�G�X�P�[�v�L�[�������ꂽ�烋�[�v���甲����
		if( GetNowCount()-start_time>=60000 ) break;//60�b�o�߂����烋�[�v���甲����
	
	}
	DxLib_End() ;	// �c�w���C�u�����g�p�̏I������
	//WaitKey() ;					// �L�[�̓��͑҂�((7-3)�wWaitKey�x���g�p)
		
	return 0 ;	
					// �\�t�g�̏I��
}


/*
γ��...ϲ�A�����...
http://www.nicovideo.jp/watch/sm22587419
*/