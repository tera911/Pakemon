// �����ɃT���v���v���O�������y�[�X�g���Ă�������
// ������Ԃł� LoadGraphScreen �̃T���v���v���O���������͂���Ă��܂��B
#include <DxLib.h>
#include <mmsystem.h>
#include "Nyancat.h"
#include "Fps.h"

#pragma comment(lib, "winmm.lib")

#define SCREEN_WIDTH	(800)	//�X�N���[���̉���
#define SCREEN_HEIGHT	(600)	//�X�N���[���̏c��
#define CHIP_SIZE		(32)	//��̃`�b�v�̃T�C�Y
#define MAP_WIDTH		(46)
#define	MAP_HEIGHT		(18)



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				 LPSTR lpCmdLine, int nCmdShow ){
	int GraphHandle;

	SetGraphMode(800, 600, 32, 60);
	ChangeWindowMode(true);
	if( DxLib_Init() == -1 )	// �c�w���C�u��������������
	{
		 return -1;				// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂɂ���
	Nyancat player;
	Fps fpsCounter;

	GraphHandle = LoadGraph("test1.bmp");
	while(1){
		ClearDrawScreen();	//��ʂɕ`����Ă�����̂�S������
		fpsCounter.Update();
		/////////////////////////////////////////////////////////////////
		//							�`��J�n						   //
		/////////////////////////////////////////////////////////////////
		
		fpsCounter.Draw();
		// �a�l�o�摜�̕\��
		DrawGraph(0, 0, GraphHandle, false);
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
			player.moveUp();
		}
		/////////////////////////////////////////////////////////////////
		//							�L�[���͑҂�������				   //
		/////////////////////////////////////////////////////////////////

		ScreenFlip();			//����ʂ̓��e��\��ʂɔ��f������
		fpsCounter.Wait();		//�ҋ@
		//Windows �R�[���o�b�N����������
		if(ProcessMessage() == -1) break; //�ُ킪���������烋�[�v���甲����

		//�G�X�P�[�v�L�[�������ꂽ�烋�[�v���甲����
		if(CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	//WaitKey() ;					// �L�[�̓��͑҂�((7-3)�wWaitKey�x���g�p)

	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������

	return 0 ;					// �\�t�g�̏I��
}


/*
γ��...ϲ�A�����...
*/